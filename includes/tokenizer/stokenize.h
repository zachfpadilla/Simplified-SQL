//
// Created by Zachary on 1/18/2023.
//

#ifndef BARKESHLI_S22_STOKENIZE_H
#define BARKESHLI_S22_STOKENIZE_H
#include "../token/Token.h"
#include "constants.h"
#include "adjacencyMatrixFunctions.h"
#include <cassert>

class STokenizer {
public:
    STokenizer();
    STokenizer(char str[]);
    bool done();
    bool more();

    friend STokenizer& operator >> (STokenizer& s, Token& t);

    void set_string(char str[]);

private:
    static void make_table();

    bool get_token(int &state, std::string& token);

    char _buffer[MAX_BUFFER];
    int _pos;
    static int _table[MAX_ROWS][MAX_COLUMNS];
};


#endif //BARKESHLI_S22_STOKENIZE_H
