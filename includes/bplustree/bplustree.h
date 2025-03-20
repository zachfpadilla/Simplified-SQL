//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_BPLUSTREE_H
#define INC_11_90_B_PLUS_TREE_RZ187_BPLUSTREE_H
#include "btree_array_funcs.h"
#include <iomanip>

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=nullptr, int _key_ptr = 0):
                it(_it), key_ptr(_key_ptr){}

        T operator *();

        Iterator operator++(int un_used);
        Iterator operator++();
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.it != rhs.it || lhs.key_ptr != rhs.key_ptr;
        }
        void print_Iterator(){
            if (it){
                std::cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                std::cout<<"iterator: NULL, key_ptr: "<<key_ptr<<std::endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            std::cout<<std::endl<<"Iterator info:"<<std::endl;
            std::cout<<"key_ptr: "<<key_ptr<<std::endl;
            std::cout<<"it: "<<*it<<std::endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);
    void remove(const T& entry);
    void clear_tree();

    bool contains(const T& entry) const;
    T& get(const T& entry);
    const T& get(const T& entry)const;
    T& get_existing(const T& entry);
    Iterator find(const T& key);
    Iterator lower_bound(const T& key);
    Iterator upper_bound(const T& key);

    int size() const;
    bool empty() const;

    void print_tree(int level = 0,
                    std::ostream &outs=std::cout) const;
    friend std::ostream& operator<<(std::ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    std::string in_order();
    std::string pre_order();
    std::string post_order();

    Iterator begin();
    Iterator end();
    std::ostream& list_keys(Iterator from = nullptr, Iterator to = nullptr){
        if (from == nullptr) from = begin();
        if (to == nullptr) to = end();
        for (Iterator it = from; it != to; it++)
            std::cout<<*it<<" ";
        return std::cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;
    int data_count;
    T data[MAXIMUM + 1];
    int child_count;
    BPlusTree* subset[MAXIMUM + 2];
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}

    T* find_ptr(const T& entry);

    void loose_insert(const T& entry);

    void fix_excess(int i);
    void loose_remove(const T& entry);

    BPlusTree<T>* fix_shortage(int i);
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);
    void get_biggest(T& entry);
    void remove_biggest(T& entry);
    void transfer_left(int i);
    void transfer_right(int i);
    BPlusTree<T> *merge_with_next_subset(int i);

};

#include "bplustree.cpp"
#endif //INC_11_90_B_PLUS_TREE_RZ187_BPLUSTREE_H
