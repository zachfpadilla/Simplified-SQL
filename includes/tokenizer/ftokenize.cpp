//
// Created by Zachary on 1/18/2023.
//

#include "ftokenize.h"

FTokenizer::FTokenizer(char *fname)
: _pos(0), _blockPos(0) {
    _f.open(fname);
    if (_f.fail())
    {
        std::cout << "Invalid file!\n";
        exit(69);
    }
    _more = get_new_block();
}

Token FTokenizer::next_token() {
    Token t;
    if (_stk.more() || get_new_block())
        _stk >> t;
    else
        _more = false;
    return t;
}

bool FTokenizer::more() {
    return _more;
}

int FTokenizer::pos() {
    return _pos;
}

int FTokenizer::block_pos() {
    return _blockPos;
}

bool FTokenizer::get_new_block() {
    char block[MAX_BLOCK];
    if (_f.eof())
        return false;
    _f.read(block, MAX_BLOCK - 1);
    block[_f.gcount()] = 0;
    _pos += MAX_BLOCK - 1;
    _blockPos = 0;
    _stk.set_string(block);
    return true;
}

FTokenizer &operator>>(FTokenizer &f, Token &t) {
//    if (!f.more())
//        int wow = 5/0;
    assert(f.more());

    do {
        t = f.next_token();
        ++f._blockPos;
//        std::cout << "Token type: " << t.type() << std::endl;
    } while (f._more && t.type() == TOKEN_END);
    return f;
}
