//
// Created by Zachary on 4/4/2023.
//

#ifndef INC_11_90_B_PLUS_TREE_RZ187_BPLUSTREE_CPP
#define INC_11_90_B_PLUS_TREE_RZ187_BPLUSTREE_CPP
#include "bplustree.h"

template<class T>
BPlusTree<T>::BPlusTree(bool dups)
: data_count(0), child_count(0), dups_ok(dups), next(nullptr) {
    for (auto & i : subset)
        i = nullptr;
}

template<class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups)
: data_count(0), child_count(0), dups_ok(dups), next(nullptr) {
    for (auto &i: subset)
        i = nullptr;
    for (int i = 0; i < size; ++i)
        insert(a[i]);
}

template<class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other)
: data_count(0), child_count(0), dups_ok(other.dups_ok), next(nullptr) {
    copy_tree(other);
}

template<class T>
BPlusTree<T>::~BPlusTree() {
    clear_tree();
}

template<class T>
BPlusTree<T> &BPlusTree<T>::operator=(const BPlusTree<T> &RHS) {
    if (this == &RHS)
        return *this;
    clear_tree();
    this->dups_ok = RHS.dups_ok;
    copy_tree(RHS);
    return *this;
}

template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other) {
    BPlusTree<T>* last = nullptr;
    copy_tree(other, last);
}

template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node) {
    copy_array(data, other.data, data_count, other.data_count);
    for (int i = 0; i < other.child_count; ++i) {
        attach_item(subset, child_count, new BPlusTree<T>(dups_ok));
        subset[i]->copy_tree(*other.subset[i], last_node);
    } if (other.is_leaf()) {
        if (last_node)
            last_node->next = this;
        last_node = this;
    }
}

template<class T>
void BPlusTree<T>::insert(const T &entry) {
    loose_insert(entry);
    if (data_count > MAXIMUM) {
        BPlusTree<T>* new_root = new BPlusTree<T>(dups_ok);
        copy_array(new_root->data, data, new_root->data_count, data_count);
        copy_array(new_root->subset, subset, new_root->child_count, child_count);
        data_count = 0;
        child_count = 1;
        subset[0] = new_root;
        fix_excess(0);
    }
}

template<class T>
void BPlusTree<T>::remove(const T &entry) {
    loose_remove(entry);
    if (!data_count && child_count) {
        BPlusTree<T>* shrink_tree = subset[0];
        copy_array(data, shrink_tree->data, data_count, shrink_tree->data_count);
        copy_array(subset, shrink_tree->subset, child_count, shrink_tree->child_count);
        next = shrink_tree->next;
        shrink_tree->data_count = shrink_tree->child_count = 0;
        delete shrink_tree;
    }
}

template<class T>
void BPlusTree<T>::clear_tree() {
    for (int i = 0; i < child_count; ++i) {
        subset[i]->clear_tree();
        delete subset[i];
    } data_count = child_count = 0;
    next = nullptr;
}

template<class T>
bool BPlusTree<T>::contains(const T &entry) const {
    int i = first_ge(data, data_count, entry);
    if (i < data_count && data[i] == entry)
        return true;
    if (!is_leaf()) {
        return subset[i]->contains(entry);
    } return false;
}

template<class T>
T &BPlusTree<T>::get(const T &entry) {
    if (!contains(entry))
        insert(entry);
    return get_existing(entry);
}

template<class T>
const T &BPlusTree<T>::get(const T &entry) const {
    if (!contains(entry))
        insert(entry);
    return get_existing(entry);
}

template<class T>
T &BPlusTree<T>::get_existing(const T &entry) {
    assert(contains(entry));
    int i = first_ge(data, data_count, entry);
    if (is_leaf())
        return data[i];
    else {
        if (i < data_count && data[i] == entry)
            return subset[i + 1]->get_existing(entry);
        return subset[i]->get_existing(entry);
    }
}

template<class T>
int BPlusTree<T>::size() const {
    int total_items = 0;
    for (int i = 0; i < data_count; ++i) {
        ++total_items;
        if (!is_leaf())
            total_items += subset[i]->size();
    } if (!is_leaf())
        total_items += subset[child_count - 1]->size();
    return total_items;
}

template<class T>
bool BPlusTree<T>::empty() const {
    return !data_count;
}

template<class T>
void BPlusTree<T>::print_tree(int level, std::ostream &outs) const {
    if (!is_leaf())
        subset[child_count - 1]->print_tree(level + 1, outs);
    else if (next)
        outs << std::setw(4*level) << "" << "^\n";
    outs << std::setw(4*level) << "" << "_\n";
    for (int i = data_count - 1; i >= 0; --i) {
        outs << std::setw(4*level) << "" << data[i] << "\n";
        if (!i)
            outs << std::setw(4*level) << "" << static_cast<char>(257) << '\n';
        if (!is_leaf())
            subset[i]->print_tree(level + 1, outs);
    }
}

template<class T>
bool BPlusTree<T>::is_valid() {
    T entry = data[data_count - 1];
    if (!is_leaf())
        subset[data_count]->get_smallest(entry);

    return data[data_count - 1] == entry;
}

template<class T>
std::string BPlusTree<T>::in_order() {
    std::string in_order;
    if (!is_leaf())
        in_order += subset[0]->in_order();
    for (int i = 0; i < data_count; ++i) {
        in_order += std::to_string(data[i]) + '|';
        if (!is_leaf())
            in_order += subset[i + 1]->in_order();
    } return in_order;
}

template<class T>
std::string BPlusTree<T>::pre_order() {
    std::string pre_order;
    for (int i = 0; i < data_count; ++i) {
        pre_order += std::to_string(data[i]) + '|';
        if (!is_leaf())
            pre_order += subset[i]->pre_order();
    } if (!is_leaf())
        pre_order += subset[data_count]->pre_order();
    return pre_order;
}

template<class T>
std::string BPlusTree<T>::post_order() {
    std::string post_order;
    if (!is_leaf())
        post_order += subset[0]->post_order();
    for (int i = 0; i < data_count; ++i) {
        if (!is_leaf())
            post_order += subset[i + 1]->post_order();
        post_order += std::to_string(data[i]) + '|';
    } return post_order;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin() {
    return {get_smallest_node()};
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end() {
    return {};
}

template<class T>
T *BPlusTree<T>::find_ptr(const T &entry) {
    int i = first_ge(data, data_count, entry);
    if (is_leaf()) {
        if (i < data_count && data[i] == entry)
            return &this->data[i];
        else
            return nullptr;
    } else {
        if (i < data_count && data[i] == entry)
            return subset[i + 1]->find_ptr(entry);
        else
            return subset[i]->find_ptr(entry);
    }
}

template<class T>
void BPlusTree<T>::loose_insert(const T &entry) {
    int i = first_ge(data, data_count, entry);
    if (is_leaf()) {
        if (i < data_count && data[i] == entry) {
            if (dups_ok)
                insert_item(data, i, data_count, entry);
            else data[i] = data[i] + entry;
        } else insert_item(data, i, data_count, entry);
    } else {
        if (i < data_count && data[i] == entry) {
            subset[i + 1]->loose_insert(entry);
            if (subset[i + 1]->data_count > MAXIMUM)
                fix_excess(i + 1);
        } else {
            subset[i]->loose_insert(entry);
            if (subset[i]->data_count > MAXIMUM)
                fix_excess(i);
        }
    }
}

template<class T>
void BPlusTree<T>::fix_excess(int i) {
    insert_item(data, i, data_count, subset[i]->data[MAXIMUM / 2]);
    insert_item(subset, i + 1, child_count, new BPlusTree<T>(dups_ok));
    split(subset[i]->data, subset[i]->data_count,
          subset[i + 1]->data, subset[i + 1]->data_count);
    split(subset[i]->subset, subset[i]->child_count,
          subset[i + 1]->subset, subset[i + 1]->child_count);
    // code from BTree

    if (subset[i]->is_leaf()) {
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, data[i]);
        subset[i + 1]->next = subset[i]->next;
        subset[i]->next = subset[i + 1];
    }
}

template<class T>
void BPlusTree<T>::loose_remove(const T &entry) {
    T temp_entry;
    int i = first_ge(data, data_count, entry);
    if (is_leaf()) {
        if (i < data_count && data[i] == entry)
            delete_item(data, i, data_count, temp_entry);
    } else {
        if (i < data_count && data[i] == entry) {
            subset[i + 1]->loose_remove(entry);
            if (subset[i + 1]->data_count < MINIMUM) {
                temp_entry = fix_shortage(i + 1)->data[0];

                //replace breadcrumbs
                int j = first_ge(data, data_count, entry);
                if (j < data_count && data[j] == entry) {
                    data[j] = temp_entry;
                    return;
                } j = first_ge(subset[i]->data, subset[i]->data_count, entry);
                if (j < subset[i]->data_count && subset[i]->data[j] == entry) {
                    subset[i]->data[j] = temp_entry;
                }
            } else {
                subset[i + 1]->get_smallest(temp_entry);
                data[i] = temp_entry;
            }
        } else {
            subset[i]->loose_remove(entry);
            if (subset[i]->data_count < MINIMUM) {
                fix_shortage(i);
            }
        }
    }
}

template<class T>
BPlusTree<T> *BPlusTree<T>::fix_shortage(int i) {
    if (i > 0 && subset[i - 1]->data_count > MINIMUM)
        transfer_right(i);
    else if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM)
        transfer_left(i);
    else if (i > 0 && subset[i - 1]->data_count == MINIMUM)
        return merge_with_next_subset(i - 1);
    else
        return merge_with_next_subset(i);
    return subset[i]->get_smallest_node();
}

template<class T>
BPlusTree<T> *BPlusTree<T>::get_smallest_node() {
    return is_leaf()? this : subset[0]->get_smallest_node();
}

template<class T>
void BPlusTree<T>::get_smallest(T &entry) {
    if (is_leaf())
        entry = data[0];
    else
        subset[0]->get_smallest(entry);
}

template<class T>
void BPlusTree<T>::get_biggest(T &entry) {
    is_leaf()? entry = data[data_count - 1] : subset[child_count - 1]->get_biggest(entry);
}

template<class T>
void BPlusTree<T>::remove_biggest(T &entry) {
    if (is_leaf()) {
        detach_item(data, data_count, entry);
    } else {
        subset[child_count - 1]->remove_biggest(entry);
        if (subset[child_count - 1]->data_count < MINIMUM)
            fix_shortage(child_count - 1);
    }
}

template<class T>
void BPlusTree<T>::transfer_left(int i) {
    T temp_entry;
    if (!subset[i]->is_leaf()) {
        delete_item(data, i, data_count, temp_entry);
        attach_item(subset[i]->data, subset[i]->data_count, temp_entry);
        delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp_entry);
        insert_item(data, i, data_count, temp_entry);

        BPlusTree<T> *temp_node;
        delete_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, temp_node);
        attach_item(subset[i]->subset, subset[i]->child_count, temp_node);
    } // code from BTree
    else {
        delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp_entry);
        attach_item(subset[i]->data, subset[i]->data_count, temp_entry);
        data[i] = subset[i + 1]->data[0];
    }
}

template<class T>
void BPlusTree<T>::transfer_right(int i) {
    T temp_entry;
    if (!subset[i]->is_leaf()) {
        delete_item(data, i - 1, data_count, temp_entry);
        insert_item(subset[i]->data, 0, subset[i]->data_count, temp_entry);
        detach_item(subset[i - 1]->data, subset[i - 1]->data_count, temp_entry);
        insert_item(data, i - 1, data_count, temp_entry);

        BPlusTree<T> *temp_node;
        detach_item(subset[i - 1]->subset, subset[i - 1]->child_count, temp_node);
        insert_item(subset[i]->subset, 0, subset[i]->child_count, temp_node);
    } // code from BTree
    else {
        detach_item(subset[i - 1]->data, subset[i - 1]->data_count, temp_entry);
        insert_item(subset[i]->data, 0, subset[i]->data_count, temp_entry);
        data[i - 1] = temp_entry;
    }
}

template<class T>
BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i) {
    T temp_entry;
    delete_item(data, i, data_count, temp_entry);
    if (!subset[i]->is_leaf())
        attach_item(subset[i]->data, subset[i]->data_count, temp_entry);

    BPlusTree<T>* temp, *temp_smallest;
    delete_item(subset, i + 1, child_count, temp);
    temp_smallest = temp->get_smallest_node();
    merge(subset[i]->data, subset[i]->data_count, temp->data, temp->data_count);
    merge(subset[i]->subset, subset[i]->child_count, temp->subset, temp->child_count);

    subset[i]->next = temp->next;
    delete temp;
    return temp_smallest;
}

template<class T>
T BPlusTree<T>::Iterator::operator*() {
    assert(it);
    return it->data[key_ptr];
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::Iterator::operator++(int un_used) {
    assert(it);
    BPlusTree<T>::Iterator copy(it, key_ptr++);
    if (key_ptr == it->data_count) {
        it = it->next;
        key_ptr = 0;
    } return copy;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::Iterator::operator++() {
    assert(it);
    if (++key_ptr == it->data_count) {
        it = it->next;
        key_ptr = 0;
    } return *this;
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &key) {
    int i = first_ge(data, data_count, key);
    if (is_leaf()) {
        if (i < data_count && data[i] == key)
            return {this, i};
        return {};
    } else {
        if (i < data_count && data[i] == key)
            return subset[i + 1]->find(key);
        return subset[i]->find(key);
    }
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T &key) {
    int i = first_ge(data, data_count, key);
    if (is_leaf()) {
        if (i < data_count && key <= data[i])
            return {this, i};
        else if (i < data_count - 1)
            return {this, i + 1};
        else return {next};
    } else {
        if (i == data_count || key < data[i])
            return subset[i]->lower_bound(key);
        return subset[i + 1]->lower_bound(key);
    }
}

template<class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T &key) {
    int i = first_ge(data, data_count, key);
    if (is_leaf()) {
        if (i < data_count && key < data[i])
            return {this, i};
        else if (i < data_count - 1)
            return {this, i + 1};
        else return {next};
    } else {
        if (i == data_count || key < data[i])
            return subset[i]->upper_bound(key);
        return subset[i + 1]->upper_bound(key);
    }
}

#endif //INC_11_90_B_PLUS_TREE_RZ187_BPLUSTREE_CPP