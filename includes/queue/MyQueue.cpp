//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_MYQUEUE_CPP
#define BARKESHLI_S22_MYQUEUE_CPP
#include "MyQueue.h"

template<typename T>
Queue<T>::Queue()
: _front(nullptr), _rear(nullptr), _size(0)
{}

template<typename T>
Queue<T>::Queue(const Queue<T> &copyMe)
: _front(nullptr), _rear(nullptr), _size(copyMe._size)
{
    _rear = _copy_list(_front, copyMe._front);
    for (node<T>* walker = _rear; walker != nullptr; walker = walker->_prev)
        if (walker->_prev == nullptr)
            _front = walker;
}

template<typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    if (this == &RHS)
        return *this;

    _rear = _copy_list(_front, RHS._front);
    for (node<T>* walker = _rear; walker != nullptr; walker = walker->_prev)
        if (walker->_prev == nullptr)
            _front = walker;

    _size = RHS._size;
    return *this;
}

template<typename T>
bool Queue<T>::empty()
{
    return _front == nullptr;
}

template<typename T>
T Queue<T>::front()
{
    assert(_front != nullptr);
    return _front->_item;
}

template<typename T>
T Queue<T>::back()
{
    assert(_rear != nullptr);
    return _rear->_item;
}

template<typename T>
void Queue<T>::push(T item)
{
    _rear = _insert_after(_front, _rear, item);
    ++_size;
}

template<typename T>
T Queue<T>::pop()
{
    assert(_front != nullptr);
    node<T>* topNode = _front;
    _front = _front->_next;
    --_size;
    return _delete_node(topNode, topNode);
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return {_front};
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return nullptr;
}

template<typename T>
int Queue<T>::size() const
{
    return _size;
}

template<typename T>
void Queue<T>::print_pointers()
{
    _print_list(_front);
}

template<typename T>
Queue<T>::Iterator::Iterator()
: _ptr(nullptr)
{}

template<typename T>
Queue<T>::Iterator::Iterator(node<T> *p)
: _ptr(p)
{}

template<typename T>
T Queue<T>::Iterator::operator*()
{
    return _ptr->_item;
}

template<typename T>
bool Queue<T>::Iterator::is_null()
{
    return _ptr == nullptr;
}

template<typename T>
std::ostream &operator<<(std::ostream &outs, const Queue<T> &printMe)
{
    for (node<T>* walker = printMe._front; walker != nullptr; walker = walker->_next)
        outs << *walker;
    return outs;
}

#endif //BARKESHLI_S22_MYQUEUE_CPP