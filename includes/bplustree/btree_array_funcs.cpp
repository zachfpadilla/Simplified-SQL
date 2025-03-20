//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_BTREE_ARRAY_FUNCS_CPP
#define INC_11_90_B_PLUS_TREE_RZ187_BTREE_ARRAY_FUNCS_CPP

#include "btree_array_funcs.h"
template<class T>
T maximal(const T &a, const T &b) {
    if (a >= b)
        return a;
    return b;
}

template<class T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
int index_of_maximal(T *data, int n) {
    return n - 1;

//    int max_index = 0;
//    for (int i = 1; i < n; ++i) {
//        if (data[i] > data[max_index])
//            max_index = i;
//    } return max_index;
}

template<class T>
void ordered_insert(T *data, int &n, T entry) {
    int i = first_ge(data, n, entry);
    insert_item(data, i, n, entry);
}

template<class T>
int first_ge(const T *data, int n, const T &entry) {
    for (int i = 0; i < n; ++i)
        if (entry <= data[i])
            return i;
    return n;
}

template<class T>
void attach_item(T *data, int &n, const T &entry) {
    data[n++] = entry;
}

template<class T>
void insert_item(T *data, int i, int &n, T entry) {
    for (int j = n; j > i; --j) {
        data[j] = data[j - 1];
    } data[i] = entry;
    ++n;
}

template<class T>
void detach_item(T *data, int &n, T &entry) {
    if (n)
        entry = data[--n];
}

template<class T>
void delete_item(T *data, int i, int &n, T &entry) {
    if (!n) {
        entry = data[n];
        return;
    } --n;
    entry = data[i];
    for (int j = i; j < n; ++j)
        data[j] = data[j + 1];
}

template<class T>
void merge(T *data1, int &n1, T *data2, int &n2) {
    for (int i = 0; i < n2; ++i)
        data1[n1 + i] = data2[i];
    n1 += n2;
    n2 = 0;
}

template<class T>
void split(T *data1, int &n1, T *data2, int &n2) {
    int offset = 0;
    if (n1 % 2)
        offset = 1;
    n1 /= 2;
    for (int i = 0; i < n1; ++i)
        insert_item(data2, i, n2, data1[n1 + i + offset]);
    n2 = n1;
}

template<class T>
void copy_array(T *dest, const T *src, int &dest_size, int src_size) {
    for (int i = 0; i < src_size; ++i)
        dest[i] = src[i];
    dest_size = src_size;
}

template<class T>
void print_array(const T *data, int n, int pos) {
    std::cout << "[\n";
    for (int i = 0; i < n; ++i)
        std::cout << data[i] << '\n';
    std::cout << ']';
}

//template<class T>
//bool is_gt(const T *data, int n, const T &item) {
//    return item > data[n - 1];
//}
//
//template<class T>
//bool is_le(const T *data, int n, const T &item) {
//    return item < data[0];
//}

template<typename T>
std::ostream &operator<<(std::ostream &outs, const std::vector<T> &list) {;
    for (const T& i : list)
        outs << i << ' ';
    return outs;
}

template<typename T>
std::vector<T> &operator+=(std::vector<T> &list, const T &addme) {
    list.push_back(addme);
    return list;
}

#endif //INC_11_90_B_PLUS_TREE_RZ187_BTREE_ARRAY_FUNCS_CPP