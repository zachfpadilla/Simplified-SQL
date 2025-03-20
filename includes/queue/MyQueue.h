//
// Created by Zachary on 1/10/2023.
//

#ifndef BARKESHLI_S22_MYQUEUE_H
#define BARKESHLI_S22_MYQUEUE_H
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"


template <typename T>
class Queue
{
public:
    class Iterator
    {
        public:
            friend class Queue;
            Iterator();
            Iterator(node<T>* p);

            T operator *();
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
            node<T>* _ptr;
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;
    Iterator end() const;
    void print_pointers();
    int size() const;
    template<typename TT>
    friend std::ostream& operator << (std::ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};


#include "MyQueue.cpp"
#endif //BARKESHLI_S22_MYQUEUE_H
