//
// Created by Zachary Padilla on 4/19/2023.
//

#ifndef BARKESHLI_S22_RPAREN_H
#define BARKESHLI_S22_RPAREN_H
#include "token.h"

class RParen : public Token {
public:
    RParen() {};

    TOKEN_TYPES type() override {return RPAREN;};
    void insert_op(ostream& outs) const override {outs << ')';}
};

#endif //BARKESHLI_S22_RPAREN_H
