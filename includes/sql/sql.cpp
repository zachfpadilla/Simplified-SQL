//
// Created by Zachary Padilla on 4/29/2023.
//

#include "sql.h"

SQL::SQL() {
    read_info(managed_tables_file.c_str(), managed_tables);
    case_list();
}

SQL::SQL(char *file_name)
: SQL::SQL() {
    batch(file_name);
}

Table SQL::command(const string &input) {
    parser.set_string(input);
    if (parser.fail()) {
        cout << "SQL::error: invalid command.\n\n";
        return {};
    } mmap_ss ptree = parser.parse_tree();
    string command = ptree["command"][0];

    switch(command[0]) {
        case 'm': //MAKE
        case 'c': //CREATE
            return case_make(ptree);
        case 's': //SELECT
            return case_select(ptree);
        case 'i': //INSERT
            return case_insert(ptree);
        case 'b': { //BATCH
            string temp = ptree["file_name"][0];
            batch(&temp[0]);
            return {};
        } case 'd': //DROP
            case_drop(ptree);
            return {};
        case 'h': //HELP
            case_help();
            return {};
        case 'l': //LIST
            case_list();
            cout << "SQL: DONE.\n";
            return {};
        default: //EXIT
            cout << "SQL::run: ending program...\n\n";
            exit(0);
    }
}

vectorlong SQL::select_recnos() {
    return recnos;
}

void SQL::batch(char *file_name) {
    fstream f(file_name);
    if (f.fail()) {
        cout << "SQL::error: file \"" << file_name << "\" does not exist!\n\n";
        return;
    } string input;
    int query_num = 0;

    cout << "> " << file_name << endl;
    while (!f.eof()) {
        getline(f, input);
        if (input.empty() || input.substr(0, 2) == "//")
            cout << input << endl;
        else {
            cout << '[' << query_num++ << "] " << input << "\n";
            Table t = command(input);
            mmap_ss ptree = parser.parse_tree();
            if (!ptree.empty() && ptree["command"][0] == "select") {
                cout << t;
                cout << "SQL: DONE.\n";
            }
        }
    } f.close();
    cout << "------- END OF BATCH PROCESS -------\n";
}

bool SQL::get_input() {
    cout << "> ";
    string input;
    getline(cin, input);
    Table t = command(input);
    mmap_ss ptree = parser.parse_tree();
    if (!ptree.empty() && ptree["command"][0] == "select") {
        cout << t;
        cout << "SQL: DONE.\n";
    } return true;
}

Table SQL::case_make(mmap_ss& ptree) {
    string table_name = ptree["table_name"][0];
    Table t(table_name, ptree["fields"]);

    cout << "SQL::run: table \"" << table_name << "\" created successfully.\n\n";
    recnos = t.select_recnos();

    int found = binary_search(table_name);
    if (found == -1) {
        //could be simplified with a B+Tree, in which case read/write_info overloads should be implemented
        managed_tables.push_back(table_name);
        sort(managed_tables.begin(), managed_tables.end());
        write_info(managed_tables_file.c_str(), managed_tables);
    } return t;
}

Table SQL::case_select(mmap_ss& ptree) {
    string table_name = ptree["table_name"][0];
    if (binary_search(table_name) == -1) {
        cout << "SQL::error: table \"" << table_name << "\" does not exist!\n\n";
        return {};
    } Table t(table_name), return_this;

    if (ptree["fields"][0] == "*")
        if (ptree["where"][0] == "yes") //SELECT ALL w/ CONDITION
            return_this = t.select(t.get_fields(), ptree["condition"]);
        else return_this = t.select_all(); //SELECT ALL
    else
        if (ptree["where"][0] == "yes") //SELECT FIELDS w/ CONDITION
            return_this = t.select(ptree["fields"], ptree["condition"]);
        else return_this = t.select(ptree["fields"]); //SELECT FIELDS

    recnos = t.select_recnos();
    return return_this;
}

Table SQL::case_insert(mmap_ss& ptree) {
    string table_name = ptree["table_name"][0];
    if (binary_search(table_name) == -1) {
        cout << "SQL::error: table \"" << table_name << "\" does not exist!\n\n";
        return {};
    } vectorstr values = ptree["values"];

    Table t(table_name);
    int t_size = t.get_fields().size();
    if (values.size() != t_size) {
        cout << "SQL::error: incorrect number of values (expected " << t_size << " but received " << values.size()
             << ")!\n\n";
        return {};
    } t.insert_into(values);

    cout << "SQL::run: successfully inserted into \"" << table_name <<"\".\n\n";
    recnos = t.select_recnos();
    return t;
}

void SQL::case_drop(mmap_ss& ptree) {
    string table_name = ptree["table_name"][0];
    int to_remove = binary_search(table_name);
    if (to_remove > -1) {
        managed_tables.erase(managed_tables.begin() + to_remove);
        write_info(managed_tables_file.c_str(), managed_tables);
        cout << "SQL::run: table dropped.\n\n";
    } else cout << "SQL::error: table \"" << table_name << "\" does not exist!\n\n";
}

void SQL::case_help() {
    cout << "------- available commands -------\n"
            "\"create\" | \"make\": creates a new table with the specified field(s).\n"
            "syntax: { <create | make> <table> <TABLE_NAME> <fields> <FIELD_NAME> [, <FIELD_NAME>...] }\n\n"
            "\"insert\": inserts a record with the specified values into the selected table.\n"
            "syntax: { <insert> <into> <TABLE_NAME> <values> <value> [, <VALUE>...] }\n\n"
            "\"select\": prints a copy of the selected table with the specified field(s) and parameter(s).\n"
            "syntax: { <select> <* | FIELD_NAME> [, FIELD_NAME>...] <from> <TABLE_NAME> <where> [<CONDITION>...] }\n\n"
            "\"list\": lists all tables managed by the program.\n"
            "syntax: { <list> }\n\n"
            "\"exit\" | \"quit\": exits the program.\n"
            "syntax: { <exit | quit> }\n\n"
            "\"help\": reprints this menu.\n"
            "syntax: { <help> }\n\n";
}

void SQL::case_list() {
    cout << "------ SQL Tables I Manage: --------\n";
    if (managed_tables.empty())
        cout << "No tables yet created!" << '\n';
    for (const auto &i : managed_tables) {
        cout << i << '\n';
    } cout << "------------------------------------\n\n";
}

int SQL::binary_search(const string &table_name) {
    if (managed_tables.empty())
        return -1;
    int start = 0; int end = managed_tables.size();
    while (start <= end) {
        int index = start + (end - start) / 2;
        if (index < 0 || index >= managed_tables.size())
            break;
        if (managed_tables[index] == table_name)
            return index;
        if (managed_tables[index] < table_name)
            start = index + 1;
        else end = index - 1;
    } return -1;
}
