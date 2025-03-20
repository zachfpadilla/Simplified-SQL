//
// Created by Zachary Padilla on 4/20/2023.
//
#include "relational.h"

map_sl Relational::relational_ops;

Relational::Relational()
{}

Relational::Relational(const string& tk)
: _tk(tk)
{}

TOKEN_TYPES Relational::type() {
    return RELATIONAL;
}

string Relational::get_tk() {
    return _tk;
}

int Relational::get_prec() {
    return 2;
}

ResultSet* Relational::eval(Token *left, Token* right, vector<mmap_sl>& table, map_sl& field_map) {
    if (relational_ops.empty())
        init_map();
    ResultSet* recnos = new ResultSet();
    mmap_sl::Iterator it;

    if (!field_map.contains(left->get_tk()))
        return recnos;
    mmap_sl table_index = table[field_map[left->get_tk()]];

    switch(relational_ops[_tk]) {
    case LESSER:
        for (it = table_index.begin(); it != table_index.lower_bound(right->get_tk()); ++it)
            for (const auto &i: (*it).value_list)
                *recnos += i;
        break;
    case LESSER_EQUAL:
        for (it = table_index.begin(); it != table_index.upper_bound(right->get_tk()); ++it)
            for (const auto &i: (*it).value_list)
                *recnos += i;
        break;
    case GREATER:
        for (it = table_index.upper_bound(right->get_tk()); it != table_index.end(); ++it)
            for (const auto &i: (*it).value_list)
                *recnos += i;
        break;
    case GREATER_EQUAL:
        for (it = table_index.lower_bound(right->get_tk()); it != table_index.end(); ++it)
            for (const auto &i: (*it).value_list)
                *recnos += i;
        break;
    case EQUAL:
        it = table_index.find(right->get_tk());
        if (it != table_index.end())
            for (const auto &i: (*it).value_list)
                *recnos += i;
    } return recnos;
}

void Relational::insert_op(ostream& outs) const {
    outs << _tk;
}

//slower than direct string comparisons, but looks nicer
void Relational::init_map() {
    relational_ops.insert("<", LESSER);
    relational_ops.insert("<=", LESSER_EQUAL);
    relational_ops.insert(">", GREATER);
    relational_ops.insert(">=", GREATER_EQUAL);
    relational_ops.insert("=", EQUAL);
}
