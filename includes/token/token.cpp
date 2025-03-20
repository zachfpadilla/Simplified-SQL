//
// Created by Zachary Padilla on 4/29/2023.
//
#include "token.h"

Token::Token()
{}

Token::Token(const string& tk, int type)
: _tk(tk), _type(static_cast<TOKEN_TYPES>(type))
{}

TOKEN_TYPES Token::type() {
    return _type;
}

string Token::get_tk() {
    return _tk;
}

void Token::insert_op(ostream& outs) const {
    outs << _tk;
}

ostream& operator << (ostream& outs, const Token& t) {
    t.insert_op(outs);
    return outs;
}