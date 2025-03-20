//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_BTREE_ARRAY_FUNCS_H
#define INC_11_90_B_PLUS_TREE_RZ187_BTREE_ARRAY_FUNCS_H
#include <iostream>
#include <vector>
#include <cassert>

template <class T>
T maximal(const T& a, const T& b);

template <class T>
void swap(T& a, T& b);

template <class T>
int index_of_maximal(T data[ ], int n);

template <class T>
void ordered_insert(T data[ ], int& n, T entry);

template <class T>
int first_ge(const T data[ ], int n, const T& entry);

template <class T>
void attach_item(T data[ ], int& n, const T& entry);

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);

template <class T>
void detach_item(T data[ ], int& n, T& entry);

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);

template <class T>
void print_array(const T data[], int n, int pos = -1);

template <typename T>
std::ostream& operator <<(std::ostream& outs, const std::vector<T>& list);

template <typename T>
std::vector<T>& operator +=(std::vector<T>& list, const T& addme);

#include "btree_array_funcs.cpp"
#endif //INC_11_90_B_PLUS_TREE_RZ187_BTREE_ARRAY_FUNCS_H
