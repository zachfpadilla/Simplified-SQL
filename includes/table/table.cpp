//
// Created by Zachary on 4/12/2023.
//

#include "table.h"

int Table::serial = 0;

Table::Table()
{}

Table::Table(const string& table_name, const vectorstr& field_names)
: _table_name(table_name), table_file_name(table_name + ".bin"), table_field_names(_table_name + "_fields.txt") {
//    cout<<"new table. Creating new file!"<<endl;

    fstream bin_file;
    open_fileW(bin_file, table_file_name.c_str());

    ++serial;
    _field_names = field_names;
    write_info(table_field_names.c_str(), field_names);
    init_field_map();
    bin_file.close();
}

Table::Table(const string& table_name)
: _table_name(table_name), table_file_name(table_name + ".bin"), table_field_names(table_name + "_fields.txt") {
//    cout << "existing table. Opening file." << endl;
    read_info(table_field_names.c_str(), _field_names);
    init_field_map();
    re_index();
}

ostream& operator<<(ostream& outs, const Table& t) {
    if (t._field_names.empty()) return outs;

    outs << "Table name: " << t._table_name << ", records: " << t.last_record << endl;
    FileRecord rec(t._field_names);
    outs << setw(20) << "record" << setw(20) << rec;
    outs << "\n\n";

    if (t.empty) return outs;

    fstream bin_file;
    open_fileRW(bin_file, t.table_file_name.c_str());
    int recno = 0;

    while (recno < t.last_record) {
        rec.read(bin_file, recno);
        outs << setw(20) << recno++ << setw(20) << rec << '\n';
    } bin_file.close();
    cout << endl;
//    cout <<endl<<endl<< t.index << endl;
//    cout << "\n\n\n----- DONE -------------\n\n"
//         << endl;
    return outs;
}

void Table::insert_into(const vectorstr &record) {
    FileRecord rec(record);
    fstream bin_file;
    open_fileRW(bin_file, table_file_name.c_str());

    bin_file.seekg(0, fstream::end);
    long recno = rec.write(bin_file);
    ++last_record;
    empty = false;

    //i == field_num
    for (int i = 0; i < _field_names.size(); ++i) {
        index[i][record[i]] += recno;
    } bin_file.close();
//    cout << "record was written in file. Record number: " << recno << endl;
}

Table Table::select_all() {
    Table temp("_select_table_" + to_string(serial), _field_names);

    long recno = 0;
    FileRecord rec(_field_names.size());
    fstream file;
    open_fileRW(file, table_file_name.c_str());
//    rec.read(file, recno++);

    while (recno < last_record) {
        rec.read(file, recno++);
        temp.insert_into(rec.get_record());
    } file.close();

    for (int i = 0; i < last_record; ++i)
        _recnos.push_back(i);
    return temp;
}

vectorlong Table::select_recnos() {
    return _recnos;
}

Table Table::select(const vectorstr &fields, const string &field, const string &op, const string &value) {
    return select(fields, {field, op, value});
}

Table Table::select(const vectorstr &fields, const vectorstr &infix) {
    Queue<Token*> postfix = ShuntingYard::sy(infix);
    return select(fields, postfix);
}

Table Table::select(const vectorstr &fields, Queue<Token *> &postfix) {
    Stack<Token*> to_eval;

    while (!postfix.empty()) {
        Token *curr_tk = postfix.pop();

        switch (curr_tk->type()) {
        case TOKENSTR:
            to_eval.push(curr_tk);
            break;
        default:
            Token *right_val = to_eval.pop();
            Token *left_val = to_eval.pop();

            Operator *op = static_cast<Operator *>(curr_tk);
            to_eval.push(op->eval(left_val, right_val, index, field_map));

            delete left_val; delete right_val; delete curr_tk;
        }
    } ResultSet* final_set = static_cast<ResultSet*>(to_eval.pop());
    assert(to_eval.empty());
    _recnos = final_set->recnos();
    delete final_set;
    sort(_recnos.begin(), _recnos.end());
    return vector_to_table(fields, _recnos);
}

Table Table::select(const vectorstr &fields) {
    Table temp("_select_table_" + to_string(serial), fields);

    FileRecord rec(_field_names.size());
    long recno = 0;
    fstream file;
    open_fileRW(file, table_file_name.c_str());

    while (recno < last_record) {
        rec.read(file, recno++);
        vectorstr filtered_records;
        for (const auto &j : fields)
            filtered_records.push_back(rec.get_record()[field_map[j]]);
        temp.insert_into(filtered_records);
    } file.close();

    for (int i = 0; i < last_record; ++i)
        _recnos.push_back(i);
    return temp;
}

Table Table::vector_to_table(const vectorstr &fields, const vectorlong &recnos) {
    Table temp("_select_table_" + to_string(serial), fields);

    FileRecord rec(_field_names.size());
    fstream file;
    open_fileRW(file, table_file_name.c_str());

    for (const auto &i : recnos) {
        rec.read(file, i);
        vectorstr filtered_records;
        for (const auto &j : fields)
            filtered_records.push_back(rec.get_record()[field_map[j]]);
        temp.insert_into(filtered_records);
    } file.close();
    return temp;
}

void Table::init_field_map() {
    for (int i = 0; i < _field_names.size(); ++i)
        field_map.insert(_field_names[i], i);
    index.resize(_field_names.size());
}

void Table::re_index() {
    FileRecord rec(_field_names.size());
    fstream file;
    open_fileRW(file, table_file_name.c_str());
    long recno = 0;
    rec.read(file, recno);

    while (!file.eof()) {
        vectorstr record = rec.get_record();
        for (int i = 0; i < _field_names.size(); ++i) {
            index[i][record[i]] += recno;
        } ++last_record;
        rec.read(file, ++recno);
        empty = false;
    } file.close();
}

vectorstr Table::get_fields() {
    return _field_names;
}
