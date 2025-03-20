//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_MYSTACK_CPP
#define BARKESHLI_S22_MYSTACK_CPP
#include "MyStack.h"

template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack()
: _top(nullptr), _size(0)
{}

template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE> &copyMe)
: _size(copyMe._size)
{
    _top = _copy_list(copyMe._top);
}

template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack()
{
    _clear_list(_top);
    _top = nullptr;
    _size = 0;
}

template<typename ITEM_TYPE>
Stack<ITEM_TYPE> &Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE> &RHS)
{
    if (this == &RHS)
        return *this;
    _top = copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}

template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    assert(_top != nullptr);
    return _top->_item;
}

template<typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty()
{
    return _top == nullptr;
}

template<typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    _top = _insert_before(_top, _top, item);
    ++_size;
}

template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    assert(_top != nullptr);
    node<ITEM_TYPE>* topNode = _top;
    _top = _top->_next;
    --_size;
    return _delete_node(topNode, topNode);
}

template<typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const
{
    return {_top};
}

template<typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const
{
    return nullptr;
}

template<typename ITEM_TYPE>
int Stack<ITEM_TYPE>::size() const
{
    return _size;
}

template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Iterator::Iterator()
: _ptr(nullptr)
{}

template<typename ITEM_TYPE>
Stack<ITEM_TYPE>::Iterator::Iterator(node<ITEM_TYPE> *p)
: _ptr(p)
{}

template<typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::Iterator::operator*()
{
    return _ptr->_item;
}

template<typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::Iterator::is_null()
{
    return _ptr == nullptr;
}

template<typename T>
std::ostream &operator<<(std::ostream &outs, const Stack<T> &printMe)
{
    for (node<T>* walker = printMe._top; walker != nullptr; walker = walker->_next)
        outs << *walker;
    return outs;
}

#endif //BARKESHLI_S22_MYSTACK_CPP