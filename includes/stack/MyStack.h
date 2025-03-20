//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_MYSTACK_H
#define BARKESHLI_S22_MYSTACK_H
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"


template <typename ITEM_TYPE>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;
        Iterator();
        Iterator(node<ITEM_TYPE>* p);
        ITEM_TYPE operator *();
        bool is_null();
        friend bool operator !=(const Iterator& left, const Iterator& right)
        {
            return left._ptr != right._ptr;
        }
        friend bool operator ==(const Iterator& left, const Iterator& right)
        {
            return left._ptr == right._ptr;
        }
        Iterator& operator++()
        {
            assert(_ptr != nullptr);
            _ptr = _ptr->_next;
            return *this;
        }
        friend Iterator operator++(Iterator& it, int unused)
        {
            assert(it._ptr != nullptr);
            Iterator copy;
            copy._ptr = it._ptr;
            ++it;
            return copy;
        }

    private:
        node<ITEM_TYPE>* _ptr;
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend std::ostream& operator<<(std::ostream& outs, const Stack<T>& printMe);
    Iterator begin() const;
    Iterator end() const;
    int size() const;

private:
    node<ITEM_TYPE>* _top;
    int _size;
};


#include "MyStack.cpp"
#endif //BARKESHLI_S22_MYSTACK_H
