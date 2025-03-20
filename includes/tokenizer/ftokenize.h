//
// Created by Zachary on 1/18/2023.
//

#ifndef BARKESHLI_S22_FTOKENIZE_H
#define BARKESHLI_S22_FTOKENIZE_H
#include "stokenize.h"
#include <fstream>

class FTokenizer {
public:
    const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer(char* fname);
    Token next_token();
    bool more();
    int pos();
    int block_pos();
    friend FTokenizer& operator >> (FTokenizer& f, Token& t);
private:
    bool get_new_block();
    std::ifstream _f;
    STokenizer _stk;
    int _pos;
    int _blockPos;
    bool _more;
};


#endif //BARKESHLI_S22_FTOKENIZE_H
