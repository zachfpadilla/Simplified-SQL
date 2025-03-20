//
// Created by Zachary Padilla on 4/24/2023.
//
#include "logical.h"

Logical::Logical()
{}

Logical::Logical(const string& tk)
: _tk(tk)
{}

TOKEN_TYPES Logical::type() {
    return LOGICAL;
}

string Logical::get_tk() {
    return _tk;
}

int Logical::get_prec() {
    switch(_tk[0]) {
    case 'a': return 1;
    case 'o': return 0;
    } exit(70);
}

ResultSet* Logical::eval(Token *left, Token* right, vector<mmap_sl>&, map_sl&) {
    ResultSet* recnos;
    ResultSet* eval_left = static_cast<ResultSet*>(left);
    ResultSet* eval_right = static_cast<ResultSet*>(right);

    switch(_tk[0]) {
        case 'a':
        recnos = new ResultSet();
        for (const auto &i : eval_left->recnos())
            for (const auto &j : eval_right->recnos())
                if (i == j)
                    *recnos += i;
        break;
        case 'o':
        recnos = new ResultSet(eval_left->recnos());
        for (const auto &i : eval_right->recnos()) {
            bool not_found = true;
            for (const auto &j : recnos->recnos())
                if (i == j) {
                    not_found = false;
                    break;
                }
            if (not_found)
                *recnos += i;
        }
    } return recnos;
}

void Logical::insert_op(ostream& outs) const {
    outs << _tk;
}