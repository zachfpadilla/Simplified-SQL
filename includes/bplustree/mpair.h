//
// Created by Zachary Padilla on 4/6/2023.
//

#ifndef BARKESHLI_S22_MPAIR_H
#define BARKESHLI_S22_MPAIR_H
#include <iostream>
#include <vector>

template <typename K, typename V>
struct MPair{
    K key;
    std::vector<V> value_list;

    MPair(const K& k=K()) : key(k) {};
    MPair(const K& k, const V& v) : key(k) {value_list.push_back(v);};
    MPair(const K& k, const std::vector<V>& vlist) : key(k), value_list(vlist) {};

    friend std::ostream& operator <<(std::ostream& outs, const MPair<K, V>& print_me) {
        outs << print_me.key << ": [";
        for (auto &i : print_me.value_list)
            outs << i << '|';
        outs << ']';
        return outs;
    }
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key <= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        return lhs.key >= rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs) {
        std::vector<V> new_list(lhs.value_list);
        for (auto &i : rhs.value_list)
            new_list.push_back(i);
        return {lhs.key, new_list};
    }
};

#endif //BARKESHLI_S22_MPAIR_H
