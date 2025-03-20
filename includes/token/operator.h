//
// Created by Zachary on 4/17/2023.
//

#ifndef BARKESHLI_S22_OPERATOR_H
#define BARKESHLI_S22_OPERATOR_H
#include "token.h"
#include "resultset.h"

class Operator : public Token {
public:
    Operator() {};
    Operator(const string& tk) : _tk(tk) {};

    TOKEN_TYPES type() override {return OPERATOR;};
    string get_tk() override {return _tk;};
    virtual int get_prec() = 0;

    //for aesthetics
    virtual ResultSet* eval(Token *left, Token* right, vector<mmap_sl>& table, map_sl& field_map) = 0;

    void insert_op(ostream& outs) const override {outs << _tk;}
private:
    string _tk;
};


#endif //BARKESHLI_S22_OPERATOR_H
