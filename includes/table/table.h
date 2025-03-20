//
// Created by Zachary on 4/12/2023.
//

#ifndef INC_99_TABLE_RZ187_TABLE_H
#define INC_99_TABLE_RZ187_TABLE_H
#include "typedefs.h"
#include "../binary_files/file_record.h"
#include "../binary_files/utilities.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../shunting_yard/shuntingyard.h"
#include "algorithm"

class Table {
public:
    Table();
    Table(const string& table_name);
    Table(const string& table_name, const vectorstr& field_names);
    void insert_into(const vectorstr& record);
    vectorstr get_fields();

    Table select_all();
    vectorlong select_recnos();
    Table select(const vectorstr& fields, const string& field, const string& op, const string& value);
    Table select(const vectorstr& fields, const vectorstr& infix);
    Table select(const vectorstr& fields, Queue<Token*>& postfix);
    Table select(const vectorstr& fields);

    friend ostream& operator<<(ostream& outs, const Table& t);

private:
    Table vector_to_table(const vectorstr &fields, const vectorlong& recnos);

    void init_field_map();
    void re_index();

    vectorlong _recnos;

    string _table_name, table_file_name, table_field_names;
    vector<mmap_sl> index;
    map_sl field_map;

    vectorstr _field_names;
    bool empty = true;
    int last_record = 0;
    static int serial;
};


#endif //INC_99_TABLE_RZ187_TABLE_H
