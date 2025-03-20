//
// Created by Zachary Padilla on 4/29/2023.
//

#ifndef BARKESHLI_S22_SQL_H
#define BARKESHLI_S22_SQL_H
#include "../table/table.h"
#include "../parser/parser.h"

class SQL {
public:
    SQL();
    SQL(char *file_name);

    Table command(const string& input);
    vectorlong select_recnos();

    void batch(char* file_name);
    bool get_input();
private:
    Table case_make(mmap_ss& ptree);
    Table case_select(mmap_ss& ptree);
    Table case_insert(mmap_ss& ptree);
    void case_drop(mmap_ss& ptree);
    static void case_help();
    void case_list();

    //could've simply used a B+Tree instead, but opted for a vector to take advantage of file functions
    int binary_search(const string& table_name);

    Parser parser;
    vectorstr managed_tables;
    vectorlong recnos;
    string managed_tables_file = "managed_tables.txt";
};


#endif //BARKESHLI_S22_SQL_H
