//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_MAP_H
#define INC_11_90_B_PLUS_TREE_RZ187_MAP_H
#include "bplustree.h"
#include "pair.h"

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it = {});
        Iterator operator ++(int unused);
        Iterator operator ++();
        Pair<K, V> operator *();
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) {
            return lhs._it != rhs._it;
        }
    private:
        typename map_base::Iterator _it;
    };

    Map();
    Iterator begin();
    Iterator end();

    int size() const;
    bool empty() const;

    V& operator[](const K& key);
    const V& operator[](const K& key) const;
    V& at(const K& key);
    const V& at(const K& key) const;

    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);

    bool is_valid(){return map.is_valid();}

    friend std::ostream& operator<<(std::ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<std::endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

#include "map.cpp"
#endif //INC_11_90_B_PLUS_TREE_RZ187_MAP_H
