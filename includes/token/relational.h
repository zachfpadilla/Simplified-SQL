//
// Created by Zachary on 4/17/2023.
//

#ifndef BARKESHLI_S22_RELATIONAL_H
#define BARKESHLI_S22_RELATIONAL_H
#include "operator.h"
#include "tokenstr.h"
#include "resultset.h"

class Relational : public Operator {
public:
    Relational();
    Relational(const string& tk);

    TOKEN_TYPES type() override;
    string get_tk() override;
    int get_prec() override;
    ResultSet* eval(Token *left, Token* right, vector<mmap_sl>& table, map_sl& field_map) override;

    void insert_op(ostream& outs) const override;
private:
    //for aesthetics
    static void init_map();

    string _tk;
    static map_sl relational_ops;
};


#endif //BARKESHLI_S22_RELATIONAL_H
