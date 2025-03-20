//
// Created by Zachary Padilla on 4/18/2023.
//

#ifndef BARKESHLI_S22_SHUNTINGYARD_H
#define BARKESHLI_S22_SHUNTINGYARD_H
#include "../token/token.h"
#include "../token/tokenstr.h"
#include "../token/operator.h"
#include "../token/relational.h"
#include "../token/logical.h"
#include "../token/lparen.h"
#include "../token/rparen.h"
#include "../stack/MyStack.h"

class ShuntingYard {
public:
    static Queue<Token*> sy(const vectorstr& infix);
    static Queue<Token*> infix_to_tokens(const vectorstr& infix);
private:
    //for aesthetics
    static map_sl token_types;
    static void init_map();
};


#endif //BARKESHLI_S22_SHUNTINGYARD_H
