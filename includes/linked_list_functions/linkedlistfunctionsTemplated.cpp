//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_LINKEDLISTFUNCTIONSTEMPLATED_CPP
#define BARKESHLI_S22_LINKEDLISTFUNCTIONSTEMPLATED_CPP
#include "linkedlistfunctionsTemplated.h"

template<typename T>
void _print_list(node<T> *head)
{
    assert(head != nullptr);
    for (; head != nullptr; head = head->_next)
        std::cout << *head;
}

template<typename T>
void _print_list_backwards(node<T> *head)
{
    assert(head != nullptr);
    for (; head->next != nullptr; head = head->_next);
    for (; head != nullptr; head = head->_prev)
        std::cout << *head;
}

template<typename T>
node<T> *_search_list(node<T> *head, T key)
{
    for (; head != nullptr && head->_item != key; head = head->_next);
    return head;
}

template<typename T>
node<T> *_insert_head(node<T> *&head, T insert_this)
{
    node<T>* newHead = new node<T>(insert_this);
    if (head != nullptr)
        head->_prev = newHead;
    newHead->_next = head;
    head = newHead;
    return head;
}

template<typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this)
{
    if (head == nullptr || after_this == nullptr)
        return _insert_head(head, insert_this);
    node<T>* toInsert = new node<T>(insert_this);
    if (after_this->_next != nullptr)
        after_this->_next->_prev = toInsert;
    toInsert->_prev = after_this;
    toInsert->_next = after_this->_next;
    after_this->_next = toInsert;
    return toInsert;
}

template<typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this)
{
    if (head == nullptr || before_this == nullptr)
        return _insert_head(head, insert_this);
    node<T>* toInsert = new node<T>(insert_this);
    if (before_this->_prev != nullptr)
        before_this->_prev->_next = toInsert;
    toInsert->_next = before_this;
    toInsert->_prev = before_this->_prev;
    before_this->_prev = toInsert;
    return toInsert;
}

template<typename T>
node<T> *_previous_node(node<T> *prev_to_this)
{
    return prev_to_this->_prev;
}

template<typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    assert(head != nullptr);
    assert(delete_this != nullptr);
    T item = delete_this->_item;
    if (delete_this->_next != nullptr)
        delete_this->_next->_prev = delete_this->_prev;
    if (delete_this->_prev != nullptr)
        delete_this->_prev->_next = delete_this->_next;
    delete delete_this;
    return item;
}

template<typename T>
node<T> *_copy_list(node<T> *head)
{
    if (head == nullptr)
        return nullptr;
    node<T>* newList = new node<T>(head->_item);
    node<T>* headPtr = newList;
    while (head->_next != nullptr) {
        head = head->_next;
        newList->_next = new node<T>(head->_item, nullptr, newList);
        newList = newList->_next;
    } return headPtr;
}

template<typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    _clear_list(dest);
    dest = _copy_list(src);
    for (node<T>* walker = dest; walker != nullptr; walker = walker->_next)
        if (walker->_next == nullptr)
            return walker;
    return nullptr;
}

template<typename T>
void _clear_list(node<T> *&head)
{
    if (head == nullptr)
        return;
    for(; head->_next != nullptr; head = head->_next)
        if (head->_prev != nullptr)
            delete head->_prev;
    delete head->_prev;
    delete head;
    head = nullptr;
}

template<typename T>
T &_at(node<T> *head, int pos)
{
    for (int i = 0; i <= pos && head != nullptr; ++i)
        head = head->_next;
    if (head == nullptr)
        return nullptr;
    return head->_item;
}

#endif //BARKESHLI_S22_LINKEDLISTFUNCTIONSTEMPLATED_CPP