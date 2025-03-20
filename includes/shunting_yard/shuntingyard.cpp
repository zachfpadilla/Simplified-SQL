//
// Created by Zachary Padilla on 4/18/2023.
//

#include "shuntingyard.h"

map_sl ShuntingYard::token_types;

Queue<Token *> ShuntingYard::sy(const vectorstr &infix) {
    Queue<Token*> tokens = infix_to_tokens(infix);
    Queue<Token*> postfix;
    Stack<Token*> operators;

    for (const auto &i : tokens)
        switch(i->type()) {
        case TOKENSTR: postfix.push(i); break;
        case LPAREN: operators.push(i); break;
        case RPAREN:
            while (operators.top()->type() != LPAREN)
                postfix.push(operators.pop());
            operators.pop();
            break;
        default:
            while (!operators.empty() && operators.top()->type() != LPAREN &&
                   static_cast<Operator*>(operators.top())->get_prec() >= static_cast<Operator*>(i)->get_prec())
                postfix.push(operators.pop());
            operators.push(i);
        }
    while (!operators.empty())
        postfix.push(operators.pop());
    return postfix;
}

Queue<Token *> ShuntingYard::infix_to_tokens(const vectorstr &infix) {
    if (token_types.empty())
        init_map();
    Queue<Token*> tokens;
    for (const auto &i : infix)
        if (!token_types.contains(i))
            tokens.push(new TokenStr(i));
        else
            switch(token_types[i]) {
            case RELATIONAL: tokens.push(new Relational(i)); break;
            case LOGICAL: tokens.push(new Logical(i)); break;
            case LPAREN: tokens.push(new LParen()); break;
            case RPAREN: tokens.push(new RParen());
            }
    return tokens;
}

//slower than direct string comparisons, but looks nicer
void ShuntingYard::init_map() {
    token_types.insert("<", RELATIONAL);
    token_types.insert("<=", RELATIONAL);
    token_types.insert(">", RELATIONAL);
    token_types.insert(">=", RELATIONAL);
    token_types.insert("=", RELATIONAL);

    token_types.insert("and", LOGICAL);
    token_types.insert("or", LOGICAL);

    token_types.insert("(", LPAREN);
    token_types.insert(")", RPAREN);
}
