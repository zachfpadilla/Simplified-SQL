//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_MAP_CPP
#define INC_11_90_B_PLUS_TREE_RZ187_MAP_CPP
#include "map.h"

template<typename K, typename V>
Map<K, V>::Map()
: key_count(0) {}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin() {
    return map.begin();
}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end() {
    return map.end();
}

template<typename K, typename V>
int Map<K, V>::size() const {
    return map.size();
}

template<typename K, typename V>
bool Map<K, V>::empty() const {
    return map.empty();
}

template<typename K, typename V>
V &Map<K, V>::operator[](const K &key) {
    return map.get(key).value;
}

template<typename K, typename V>
const V &Map<K, V>::operator[](const K &key) const {
    return map.get(key).value;
}

template<typename K, typename V>
V &Map<K, V>::at(const K &key) {
    return map.get(key).value;
}

template<typename K, typename V>
const V &Map<K, V>::at(const K &key) const {
    return map.get(key).value;
}

template<typename K, typename V>
void Map<K, V>::insert(const K &k, const V &v) {
    map.insert({k, v});
}

template<typename K, typename V>
void Map<K, V>::erase(const K &key) {
    map.remove(key);
}

template<typename K, typename V>
void Map<K, V>::clear() {
    map.clear_tree();
}

template<typename K, typename V>
V Map<K, V>::get(const K &key) {
    return map.get(key).value;
}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K &key) {
    return {map.find(key)};
}

template<typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V> &target) const {
    return map.contains(target);
}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K &key) {
    return {map.lower_bound(key)};
}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K &key) {
    return {map.upper_bound(key)};
}

template<typename K, typename V>
Map<K, V>::Iterator::Iterator(typename BPlusTree<Pair<K, V>>::Iterator it)
: _it(it) {}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::Iterator::operator++(int unused) {
    return _it++;
}

template<typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::Iterator::operator++() {
    return ++_it;
}

template<typename K, typename V>
Pair<K, V> Map<K, V>::Iterator::operator*() {
    return *_it;
}

#endif //INC_11_90_B_PLUS_TREE_RZ187_MAP_CPP