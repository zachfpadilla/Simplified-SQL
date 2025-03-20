//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_LINKEDLISTFUNCTIONSTEMPLATED_H
#define BARKESHLI_S22_LINKEDLISTFUNCTIONSTEMPLATED_H
#include "../node/node.h"
#include <cassert>

template <typename T>
void _print_list(node<T>* head);

template <typename T>
void _print_list_backwards(node<T> *head);

template <typename T>
node<T>* _search_list(node<T>* head,
                      T key);

template <typename T>
node<T>* _insert_head(node<T> *&head,
                      T insert_this);

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this);

template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

template <typename T>
node<T>* _copy_list(node<T>* head);

template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

template <typename T>
void _clear_list(node<T>*& head);

template <typename T>
T& _at(node<T>* head, int pos);

#include "linkedlistfunctionsTemplated.cpp"
#endif //BARKESHLI_S22_LINKEDLISTFUNCTIONSTEMPLATED_H
