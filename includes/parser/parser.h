//
// Created by Zachary on 4/25/2023.
//

#ifndef BARKESHLI_S22_PARSER_H
#define BARKESHLI_S22_PARSER_H
#include "../tokenizer/stokenize.h"
#include "../table/typedefs.h"

class Parser {
public:
    Parser();
    Parser(char* s);
    Parser(const string& s);

    void set_string(char* s);
    void set_string(const string& s);

    mmap_ss parse_tree();
    bool fail() const;
    enum {
        MAKE, TABLE, SELECT, FIELDS, STAR, FROM, INSERT, INTO, VALUES, WHERE, SYM, DROP, BATCH, LIST, EXIT, HELP
    };

private:
    void get_parse_tree();

    void init_map();
    void init_matrix();

    mmap_ss _parse_tree;
    map_sl _keywords;
    bool _fail;
    string input_q[MAX_BUFFER];
    int input_size;
    int adj_matrix[MAX_ROWS][MAX_COLUMNS];
};


#endif //BARKESHLI_S22_PARSER_H
