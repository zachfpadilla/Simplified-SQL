//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_MULTIMAP_H
#define INC_11_90_B_PLUS_TREE_RZ187_MULTIMAP_H
#include "bplustree.h"
#include "mpair.h"

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it = {});
        Iterator operator ++(int unused);
        Iterator operator ++();
        MPair<K, V> operator *();
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) {
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

    Iterator begin();
    Iterator end();

    int size() const;
    bool empty() const;

    std::vector<V>& operator[](const K& key);
    const std::vector<V>& operator[](const K& key) const;
    std::vector<V>& at(const K& key);
    const std::vector<V>& at(const K& key) const;

    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

    bool contains(const K& key) const ;
    std::vector<V> &get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);

    bool is_valid();

    friend std::ostream& operator<<(std::ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<std::endl;
        return outs;
    }

    //for parser:
    void print_lookup();

private:
    BPlusTree<MPair<K, V> > mmap;
};

#include "multimap.cpp"
#endif //INC_11_90_B_PLUS_TREE_RZ187_MULTIMAP_H
