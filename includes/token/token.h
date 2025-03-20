//
// Created by Zachary on 4/17/2023.
//

#ifndef BARKESHLI_S22_TOKEN_H
#define BARKESHLI_S22_TOKEN_H
#include "../table/typedefs.h"
#include "TOKEN_TYPES.h"

class Token {
public:
    Token();
    Token(const string& tk, int type = TOKEN);

    virtual TOKEN_TYPES type();
    virtual string get_tk();

    virtual void insert_op(ostream& outs) const;
    friend ostream& operator << (ostream& outs, const Token& t);

private:
    string _tk;
    TOKEN_TYPES _type;
};


#endif //BARKESHLI_S22_TOKEN_H
