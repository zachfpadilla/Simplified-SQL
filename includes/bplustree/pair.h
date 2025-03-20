//
// Created by Zachary on 4/4/2023.
//

#ifndef BARKESHLI_S22_PAIR_H
#define BARKESHLI_S22_PAIR_H
#include <iostream>

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V()) : key(k), value(v) {};

    friend std::ostream &operator<<(std::ostream &outs, const Pair<K, V> &print_me) {
        outs << print_me.key << ':' << print_me.value;
        return outs;
    }
    friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
        return lhs.key == rhs.key;
    }
    friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
        return lhs.key < rhs.key;
    }
    friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
        return lhs.key > rhs.key;
    }
    friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
        return lhs.key <= rhs.key;
    }
    friend Pair<K, V> operator+(const Pair<K, V> &lhs, const Pair<K, V> &rhs) {
        return rhs;
    }
};

#endif //BARKESHLI_S22_PAIR_H
