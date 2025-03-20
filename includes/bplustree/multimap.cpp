//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_MULTIMAP_CPP
#define INC_11_90_B_PLUS_TREE_RZ187_MULTIMAP_CPP
#include "multimap.h"

template<typename K, typename V>
MMap<K, V>::MMap()
{}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin() {
    return mmap.begin();
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end() {
    return mmap.end();
}

template<typename K, typename V>
int MMap<K, V>::size() const {
    return mmap.size();
}

template<typename K, typename V>
bool MMap<K, V>::empty() const {
    return mmap.empty();
}

template<typename K, typename V>
std::vector<V> &MMap<K, V>::operator[](const K &key) {
    return mmap.get(key).value_list;
}

template<typename K, typename V>
const std::vector<V> &MMap<K, V>::operator[](const K &key) const {
    return mmap.get(key).value_list;
}

template<typename K, typename V>
std::vector<V> &MMap<K, V>::at(const K &key) {
    return mmap.get(key).value_list;
}

template<typename K, typename V>
const std::vector<V> &MMap<K, V>::at(const K &key) const {
    return mmap.get(key).value_list;
}

template<typename K, typename V>
void MMap<K, V>::insert(const K &k, const V &v) {
    mmap.insert({k, v});
}

template<typename K, typename V>
void MMap<K, V>::erase(const K &key) {
    mmap.remove(key);
}

template<typename K, typename V>
void MMap<K, V>::clear() {
    mmap.clear_tree();
}

template<typename K, typename V>
bool MMap<K, V>::contains(const K &key) const {
    return mmap.contains(key);
}

template<typename K, typename V>
std::vector<V> &MMap<K, V>::get(const K &key) {
    return mmap.get(key).value_list;
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K &key) {
    return {mmap.find(key)};
}

template<typename K, typename V>
int MMap<K, V>::count(const K &key) {
    return mmap.size();
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K &key) {
    return {mmap.lower_bound(key)};
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K &key) {
    return {mmap.upper_bound(key)};
}

template<typename K, typename V>
bool MMap<K, V>::is_valid() {
    return true;
}

template<typename K, typename V>
MMap<K, V>::Iterator::Iterator(typename BPlusTree<MPair<K, V>>::Iterator it)
: _it(it) {}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::Iterator::operator++(int unused) {
    return _it++;
}

template<typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::Iterator::operator++() {
    return ++_it;
}

template<typename K, typename V>
MPair<K, V> MMap<K, V>::Iterator::operator*() {
    return *_it;
}

template<typename K, typename V>
void MMap<K, V>::print_lookup() {
    for (Iterator i = mmap.begin(); i != mmap.end(); ++i)
        std::cout << *i << '\n';
}

#endif //INC_11_90_B_PLUS_TREE_RZ187_MULTIMAP_CPP