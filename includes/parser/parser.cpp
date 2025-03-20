//
// Created by Zachary on 4/25/2023.
//

#include "parser.h"

Parser::Parser()
: _fail(true) {
    init_map();
    init_matrix();
}

Parser::Parser(char *s) {
    init_map();
    init_matrix();
    set_string(s);
}

Parser::Parser(const string& s) {
    init_map();
    init_matrix();
    set_string(s);
}

void Parser::set_string(char *s) {
    input_size = 0;
    Token t;
    STokenizer tokenizer(s);

    tokenizer >> t;
    while (tokenizer.more()) {
        if (t.type() != TOKEN_SPACE && t.get_tk() != ",")
            input_q[input_size++] = t.get_tk();
        tokenizer >> t;
    } get_parse_tree();
}

void Parser::set_string(const string& s) {
    string temp = s;
    char* p = &temp[0];
    set_string(p);
}

mmap_ss Parser::parse_tree() {
    return _parse_tree;
}

bool Parser::fail() const {
    return _fail;
}

void Parser::get_parse_tree() {
    _parse_tree.clear();
    int state = 0;

    for (int i = 0; i < input_size && state != TOKEN_UNKNOWN; ++i) {
        string token = input_q[i];

        _keywords.contains(token)?
        state = adj_matrix[state][_keywords[token]] : state = adj_matrix[state][SYM];

        switch (state) {
        case STATE_MAKE:
        case STATE_SELECT:
        case STATE_INSERT:
        case STATE_DROP:
        case STATE_BATCH:
        case STATE_EXIT:
        case STATE_HELP:
        case STATE_LIST:
            _parse_tree["command"] += token;
            break;
        case STATE_FIELDS_1:
        case STATE_FIELDS_2:
        case STATE_FIELDS_3:
            _parse_tree["fields"] += token;
            break;
        case STATE_TABLE_1:
        case STATE_TABLE_2:
        case STATE_TABLE_3:
        case STATE_TABLE_4:
            _parse_tree["table_name"] += token;
            break;
        case STATE_WHERE:
            _parse_tree["where"] += {"yes"};
            break;
        case STATE_CONDITIONS:
            _parse_tree["condition"] += token;
            break;
        case STATE_VALUES:
            _parse_tree["values"] += token;
            break;
        case STATE_FILE_NAME:
            _parse_tree["file_name"] += token;
            break;
        default: break;
        }
    } if (is_success(adj_matrix, state)) {
        if (state == STATE_TABLE_2)
            _parse_tree["where"] += {"no"};
        _fail = false;
        return;
    } _parse_tree.clear();
    _fail = true;
}

void Parser::init_map() {
    _keywords.insert("make", MAKE);
    _keywords.insert("create", MAKE);
    _keywords.insert("table", TABLE);
    _keywords.insert("select", SELECT);
    _keywords.insert("fields", FIELDS);
    _keywords.insert("*", STAR);
    _keywords.insert("from", FROM);
    _keywords.insert("insert", INSERT);
    _keywords.insert("into", INTO);
    _keywords.insert("values", VALUES);
    _keywords.insert("where", WHERE);
    _keywords.insert("drop", DROP);
    _keywords.insert("batch", BATCH);
    _keywords.insert("list", LIST);
    _keywords.insert("exit", EXIT);
    _keywords.insert("quit", EXIT);
    _keywords.insert("help", HELP);
}

void Parser::init_matrix() {
    init_table(adj_matrix);
    // MAKE
    mark_fail(adj_matrix, 0);
    mark_cell(0, adj_matrix, MAKE, 1);
    // TABLE
    mark_fail(adj_matrix, 1);
    mark_cell(1, adj_matrix, TABLE, 2);
    // <table_name>
    mark_fail(adj_matrix, 2);
    mark_cell(2, adj_matrix, SYM, 3);
    // FIELDS
    mark_fail(adj_matrix, 3);
    mark_cell(3, adj_matrix, FIELDS, 4);
    // <field_name(s)>
    mark_success(adj_matrix, 4);
    mark_cell(4, adj_matrix, SYM, 5);
    mark_success(adj_matrix, 5);
    mark_cell(5, adj_matrix, SYM, 5);


    // SELECT
    mark_cell(0, adj_matrix, SELECT, 6);
    // * / <field_name(s)>
    mark_fail(adj_matrix, 6);
    mark_cell(6, adj_matrix, STAR, 8);

    mark_cell(6, adj_matrix, SYM, 7);
    mark_fail(adj_matrix, 7);
    mark_cell(7, adj_matrix, SYM, 7);
    // FROM
    mark_fail(adj_matrix, 8);
    mark_cell(8, adj_matrix, FROM, 9);

    mark_cell(7, adj_matrix, FROM, 9);
    // <table_name>
    mark_fail(adj_matrix, 9);
    mark_cell(9, adj_matrix, SYM, 10);
    // WHERE
    mark_success(adj_matrix, 10);
    mark_cell(10, adj_matrix, WHERE, 11);
    // <condition(s)>
    mark_success(adj_matrix, 11);
    mark_cell(11, adj_matrix, SYM, 12);
    mark_success(adj_matrix, 12);
    mark_cell(12, adj_matrix, SYM, 12);


    // INSERT
    mark_cell(0, adj_matrix, INSERT, 13);
    // INTO
    mark_fail(adj_matrix, 13);
    mark_cell(13, adj_matrix, INTO, 14);
    // <table_name>
    mark_fail(adj_matrix, 14);
    mark_cell(14, adj_matrix, SYM, 15);
    // VALUES
    mark_fail(adj_matrix, 15);
    mark_cell(15, adj_matrix, VALUES, 16);
    // <value(s)>
    mark_success(adj_matrix, 16);
    mark_cell(16, adj_matrix, SYM, 17);
    mark_success(adj_matrix, 17);
    mark_cell(17, adj_matrix, SYM, 17);


    // DROP
    mark_cell(0, adj_matrix, DROP, 18);
    // TABLE
    mark_fail(adj_matrix, 18);
    mark_cell(18, adj_matrix, TABLE, 19);
    // <table_name>
    mark_fail(adj_matrix, 19);
    mark_cell(19, adj_matrix, SYM, 20);
    mark_success(adj_matrix, 20);


    // BATCH
    mark_cell(0, adj_matrix, BATCH, 21);
    // <file_name>
    mark_fail(adj_matrix, 21);
    mark_cell(21, adj_matrix, SYM, 22);
    mark_success(adj_matrix, 22);


    // EXIT
    mark_cell(0, adj_matrix, EXIT, 23);
    mark_success(adj_matrix, 23);


    // HELP
    mark_cell(0, adj_matrix, HELP, 24);
    mark_success(adj_matrix, 24);


    // LIST
    mark_success(adj_matrix, 25);
    mark_cell(0, adj_matrix, LIST, 25);
}
