//
// Created by Zachary on 4/17/2023.
//

#ifndef BARKESHLI_S22_LOGICAL_H
#define BARKESHLI_S22_LOGICAL_H
#include "operator.h"
#include "resultset.h"

class Logical : public Operator {
public:
    Logical();
    Logical(const string& tk);

    TOKEN_TYPES type() override;
    string get_tk() override;
    int get_prec() override;
    ResultSet* eval(Token *left, Token* right, vector<mmap_sl>&, map_sl&) override;

    void insert_op(ostream& outs) const override;
private:
    string _tk;
};


#endif //BARKESHLI_S22_LOGICAL_H
