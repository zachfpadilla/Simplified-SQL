//
// Created by Zachary Padilla on 4/19/2023.
//

#ifndef BARKESHLI_S22_LPAREN_H
#define BARKESHLI_S22_LPAREN_H
#include "token.h"

class LParen : public Token {
public:
    LParen() {};

    TOKEN_TYPES type() override {return LPAREN;};
    void insert_op(ostream& outs) const override {outs << '(';}
};


#endif //BARKESHLI_S22_LPAREN_H
