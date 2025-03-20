//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_NODE_H
#define BARKESHLI_S22_NODE_H
#include <iostream>

template <class T>
struct node{
    T _item;
    node<T>* _next;
    node<T>* _prev;
    node(const T& item = T(), node<T>* next = nullptr, node<T>* prev = nullptr):
            _item(item),
            _next(next),
            _prev(prev){}
    friend std::ostream& operator << (std::ostream& outs, const node<T>& print_me){
        outs<<"["<<print_me._item<<"]->";
        return outs;
    }
};

#endif //BARKESHLI_S22_NODE_H
