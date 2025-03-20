//
// Created by Zachary Padilla on 4/18/2023.
//

#ifndef BARKESHLI_S22_TOKENSTR_H
#define BARKESHLI_S22_TOKENSTR_H
#include "token.h"

class TokenStr : public Token {
public:
    TokenStr() {}
    TokenStr(const string& tk) : _tk(tk) {}

    TOKEN_TYPES type() override {return TOKENSTR;}
    string get_tk() override {return _tk;}

    void insert_op(ostream& outs) const override {outs << _tk;}
private:
    string _tk;
};


#endif //BARKESHLI_S22_TOKENSTR_H
