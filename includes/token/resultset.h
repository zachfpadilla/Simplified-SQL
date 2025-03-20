//
// Created by Zachary on 4/27/2023.
//

#ifndef BARKESHLI_S22_RESULTSET_H
#define BARKESHLI_S22_RESULTSET_H
#include "operator.h"

class ResultSet : public Token {
public:
    ResultSet() {};
    ResultSet(const vectorlong& recnos) : _recnos(recnos) {}
    vectorlong recnos() {return _recnos;}

    ResultSet operator+=(long rhs) {
        _recnos.push_back(rhs);
        return *this;
    }
private:
    vectorlong _recnos;
};


#endif //BARKESHLI_S22_RESULTSET_H
