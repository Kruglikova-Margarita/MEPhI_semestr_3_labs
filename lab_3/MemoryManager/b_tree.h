#ifndef LAB_3SEM_3_B_TREE_H
#define LAB_3SEM_3_B_TREE_H

#include "../SmartPtrs/shrd_ptr.h"
#include "../SmartPtrs/weak_ptr.h"
#include "../Sequence/sequence.h"
#include "pair.h"
#include "concept_total_ordering.h"

template <TotalOrdering K, typename V>
class BTree {
private:
    class Node {
    private:
        ShrdPtr<Sequence<Pair<K, V>>> keys_;
        ShrdPtr<Sequence<ShrdPtr<Node>>> children_;
        WeakPtr<Node> parent_;

    public:
        Node() noexcept;
        Node(K key, V value, WeakPtr<Node> parent, int degree) noexcept;
        Node(ShrdPtr<Sequence<Pair<K, V>>> keys, ShrdPtr<Sequence<ShrdPtr<Node>>> children, WeakPtr<Node> parent, int degree) noexcept;

        ShrdPtr<Sequence<Pair<K, V>>> getKeys() const noexcept;
        ShrdPtr<Sequence<ShrdPtr<Node>>> getChildren() const noexcept;
        WeakPtr<Node> getParent() const noexcept;
        int setKey(Pair<K, V> pair, int degree) noexcept;
        void setChild(ShrdPtr<Node> child, int index) noexcept;
        void setParent(WeakPtr<Node> parent) noexcept;
        [[nodiscard]] bool isFull(int degree) const noexcept;
        [[nodiscard]] bool isLeaf() const noexcept;

    };


    int degree_;
    ShrdPtr<Node> root_;

    void appendRecurse(ShrdPtr<Node> node, K key, V value);
    void splitNode(ShrdPtr<Node> node, K key, V value);
    void delegateAppendToChild(ShrdPtr<Node> node, K key, V value);

    void deleteByKeyRecurse(ShrdPtr<Node> node, K key);
    ShrdPtr<Node> makeEnoughKeys(ShrdPtr<Node> node, int index_node);
    ShrdPtr<Node> mergeNodes(ShrdPtr<Node> node, int index_node, int way);
    void redistributeKeys(ShrdPtr<Node> node, int index_node, int way);
    void deleteKey(ShrdPtr<Node> node, int index_key);
    void deleteByRedistribute(ShrdPtr<Node> node, int index_key, int way);
    void deleteByMerge(ShrdPtr<Node> node, int index_key);

    V searchByKeyRecurse(ShrdPtr<Node> node, K key) const;

    Pair<K, V> getMinSuperiorKeyRecurse(ShrdPtr<Node> node, K key) const;

    Pair<K, V> getMaxInferiorKeyRecurse(ShrdPtr<Node> node, K key) const;

    void traversalRootChildrenRecurse(ShrdPtr<Node> node, ShrdPtr<Sequence<Pair<K, V>>> elements) const noexcept;

    void traversalIncreasingOrderRecurse(ShrdPtr<Node> node, ShrdPtr<Sequence<Pair<K, V>>> elements) const noexcept;

    void traversalRecurse(ShrdPtr<Node> node) const noexcept;


public:
    explicit BTree(int degree) noexcept;
    BTree(int degree, K key, V value) noexcept;

    void append(K key, V value);
    void deleteByKey(K key);
    V searchByKey(K key) const;
    Pair<K, V> getMinSuperiorKey(K key) const;
    Pair<K, V> getMaxInferiorKey(K key) const;
    ShrdPtr<Sequence<Pair<K, V>>> traversalRootChildren() const noexcept;
    ShrdPtr<Sequence<Pair<K, V>>> traversalIncreasingOrder() const noexcept;
    void traversal() const noexcept;
};










template <TotalOrdering K, typename V>
BTree<K, V>::Node::Node() noexcept : keys_(new ArraySequence<Pair<K, V>>), children_(new ArraySequence<ShrdPtr<Node>>), parent_(nullptr) {}

template <TotalOrdering K, typename V>
BTree<K, V>::Node::Node(K key, V value, WeakPtr<Node> parent, int degree) noexcept : keys_(new ArraySequence<Pair<K, V>>), children_(new ArraySequence<ShrdPtr<Node>>), parent_(parent) {
        keys_->append(Pair<K, V>(key, value));
        for (int i = 0; i < 2 * degree; i++) {
            children_->append(ShrdPtr<Node>(nullptr));
        }
}

template <TotalOrdering K, typename V>
BTree<K, V>::Node::Node(ShrdPtr<Sequence<Pair<K, V>>> keys, ShrdPtr<Sequence<ShrdPtr<Node>>> children, WeakPtr<Node> parent, int degree) noexcept : keys_(keys), children_(children), parent_(parent) {
    for (int i = children->getLength(); i < 2 * degree; i++) {
        children_->append(ShrdPtr<Node>(nullptr));
    }
}





template <TotalOrdering K, typename V>
ShrdPtr<Sequence<Pair<K, V>>> BTree<K, V>::Node::getKeys() const noexcept {
    return keys_;
}

template <TotalOrdering K, typename V>
ShrdPtr<Sequence<ShrdPtr<typename BTree<K, V>::Node>>> BTree<K, V>::Node::getChildren() const noexcept {
    return children_;
}

template <TotalOrdering K, typename V>
WeakPtr<typename BTree<K, V>::Node> BTree<K, V>::Node::getParent() const noexcept {
    return parent_;
}

template <TotalOrdering K, typename V>
int BTree<K, V>::Node::setKey(Pair<K, V> pair, int degree) noexcept {
    int number_keys = keys_->getLength();
    int index = 0;
    K key = pair.getKey();

    while ((index < number_keys) && (key > (keys_->get(index)).getKey())) {
        index++;
    }

    if (index < number_keys)
        keys_->insertAt(pair, index);
    else
        keys_->append(pair);

    children_->insertAt(ShrdPtr<Node>(nullptr), index);
    children_->deleteElement(2 * degree);

    return index;
}

template <TotalOrdering K, typename V>
void BTree<K, V>::Node::setChild(ShrdPtr<Node> child, int index) noexcept {
    children_->set(index, child);
}

template <TotalOrdering K, typename V>
void BTree<K, V>::Node::setParent(WeakPtr<Node> parent) noexcept {
    parent_ = parent;
}

template <TotalOrdering K, typename V>
bool BTree<K, V>::Node::isFull(int degree) const noexcept {
    if (keys_->getLength() == 2 * degree - 1)
        return true;
    else
        return false;
}

template <TotalOrdering K, typename V>
bool BTree<K, V>::Node::isLeaf() const noexcept {
    for (int i = 0; i < children_->getLength(); i++) {
        if (children_->get(i))
            return false;
    }

    return true;
}










template <TotalOrdering K, typename V>
BTree<K, V>::BTree(int degree) noexcept : degree_(degree), root_(new Node(ShrdPtr<Sequence<Pair<K, V>>>(new ArraySequence<Pair<K, V>>), ShrdPtr<Sequence<ShrdPtr<Node>>>(new ArraySequence<ShrdPtr<Node>>), WeakPtr<Node>(nullptr), degree)) {}

template <TotalOrdering K, typename V>
BTree<K, V>::BTree(int degree, K key, V value) noexcept : degree_(degree), root_(new Node(key, value, WeakPtr<Node>(nullptr), degree)) {}





template <TotalOrdering K, typename V>
void BTree<K, V>::appendRecurse(ShrdPtr<Node> node, K key, V value) {
    for (int i = 0; i < node->getKeys()->getLength(); i++) {
        if (key == node->getKeys()->get(i).getKey())
            throw std::out_of_range("This key is already in the tree\n");
    }

    if (node->isFull(degree_)) {
        try {
            splitNode(node, key, value);
        } catch (...) {
            throw;
        }
    } else {
        if (node->isLeaf()) {
            node->setKey(Pair<K, V>(key, value), degree_);
        } else {
            try {
                delegateAppendToChild(node, key, value);
            } catch (...) {
                throw;
            }
        }
    }
}

template <TotalOrdering K, typename V>
void BTree<K, V>::splitNode(ShrdPtr<Node> node, K key, V value) {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    WeakPtr<Node> parent = node->getParent();

    ShrdPtr<Sequence<Pair<K, V>>> keys_half1 = keys->getSubSequence(0, degree_ - 2);
    ShrdPtr<Sequence<Pair<K, V>>> keys_half2 = keys->getSubSequence(degree_, 2 * degree_ - 2);

    ShrdPtr<Sequence<ShrdPtr<Node>>> children_half1 = children->getSubSequence(0, degree_ - 1);
    ShrdPtr<Sequence<ShrdPtr<Node>>> children_half2 = children->getSubSequence(degree_, 2 * degree_ - 1);

    ShrdPtr<Node> new_node1(new Node(keys_half1, children_half1, parent, degree_));

    for (int i = 0; i < children_half1->getLength(); i++) {
        if (children_half1->get(i))
            (children_half1->get(i))->setParent(WeakPtr<Node>(new_node1));
    }

    ShrdPtr<Node> new_node2(new Node(keys_half2, children_half2, parent, degree_));

    for (int i = 0; i < children_half2->getLength(); i++) {
        if (children_half2->get(i))
            (children_half2->get(i))->setParent(WeakPtr<Node>(new_node2));
    }

    Pair<K, V> key_middle = keys->get(degree_ - 1);

    if (parent) {
        int index_insert = parent->setKey(key_middle, degree_);

        parent->setChild(new_node1, index_insert);
        parent->setChild(new_node2, index_insert + 1);
    } else {
        root_ = ShrdPtr<Node>(new Node(key_middle.getKey(), key_middle.getValue(), WeakPtr<Node>(nullptr), degree_));

        new_node1->setParent(WeakPtr<Node>(root_));
        new_node2->setParent(WeakPtr<Node>(root_));

        root_->setChild(new_node1, 0);
        root_->setChild(new_node2, 1);
    }

    if (key < key_middle.getKey()) {
        try {
            appendRecurse(new_node1, key, value);
        } catch (...) {
            throw;
        }
    }
    else {
        try {
            appendRecurse(new_node2, key, value);
        } catch (...) {
            throw;
        }
    }
}

template <TotalOrdering K, typename V>
void BTree<K, V>::delegateAppendToChild(ShrdPtr<Node> node, K key, V value) {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();

    int number_keys = keys->getLength();
    int index = 0;

    while ((index < number_keys) && (key > (keys->get(index)).getKey())) {
        index++;
    }

    if (children->get(index)) {
        try {
            appendRecurse(children->get(index), key, value);
        } catch (...) {
            throw;
        }
    } else
        node->setChild(ShrdPtr<Node>(new Node(key, value, WeakPtr<Node>(node), degree_)), index);
}

template <TotalOrdering K, typename V>
void BTree<K, V>::append(K key, V value) {
    try {
        appendRecurse(root_, key, value);
    } catch (...) {
        throw;
    }
}





template <TotalOrdering K, typename V>
void BTree<K, V>::deleteByKeyRecurse(ShrdPtr<Node> node, K key) {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    int index = 0;
    int number_keys = keys->getLength();

    while ((index < number_keys) && (key > (keys->get(index)).getKey())) {
        index++;
    }

    if ((index < number_keys) && (keys->get(index).getKey() == key))
        deleteKey(node, index);
    else {
        ShrdPtr<Node> child_index = children->get(index);

        if (child_index) {
            if (child_index->getKeys()->getLength() < degree_) {
                ShrdPtr<Node> child_index_new = makeEnoughKeys(child_index, index);
                deleteByKeyRecurse(child_index_new, key);
            } else {
                try {
                    deleteByKeyRecurse(child_index, key);
                } catch (...) {
                    throw;
                }
            }
        } else
            throw std::out_of_range("The tree does not contain this key\n");
    }
}

template <TotalOrdering K, typename V>
ShrdPtr<typename BTree<K, V>::Node> BTree<K, V>::makeEnoughKeys(ShrdPtr<Node> node, int index_node) {
    WeakPtr<Node> parent = node->getParent();
    ShrdPtr<Sequence<ShrdPtr<Node>>> siblings = parent->getChildren();
    ShrdPtr<Node> node_new(node);

    if (index_node == 0) {
        ShrdPtr<Node> sibling_right = siblings->get(1);

        if (sibling_right->getKeys()->getLength() < degree_)
            node_new = mergeNodes(node, index_node, 1);
        else {
            redistributeKeys(node, index_node, 1);
        }
    } else if (index_node == parent->getKeys()->getLength()) {
        ShrdPtr<Node> sibling_left = siblings->get(index_node - 1);

        if (sibling_left->getKeys()->getLength() < degree_)
            node_new = mergeNodes(node, index_node, 0);
        else {
            redistributeKeys(node, index_node, 0);
        }
    } else {
        ShrdPtr<Node> sibling_left = siblings->get(index_node - 1);
        ShrdPtr<Node> sibling_right = siblings->get(index_node + 1);

        if (sibling_left->getKeys()->getLength() >= degree_) {
            redistributeKeys(node, index_node, 0);
        } else if (sibling_right->getKeys()->getLength() >= degree_) {
            redistributeKeys(node, index_node, 1);
        } else
            node_new = mergeNodes(node, index_node, 0);
    }

    return node_new;
}

template <TotalOrdering K, typename V>
ShrdPtr<typename BTree<K, V>::Node> BTree<K, V>::mergeNodes(ShrdPtr<Node> node, int index_node, int way) { //way: 0 - left sibling, 1 - right sibling
    WeakPtr<Node> parent = node->getParent();
    ShrdPtr<Sequence<ShrdPtr<Node>>> siblings = parent->getChildren();
    ShrdPtr<Node> node_sibling;
    ShrdPtr<Sequence<Pair<K, V>>> keys_new;
    int index_insert_parent_key;
    int index_parent_key;
    ShrdPtr<Sequence<ShrdPtr<Node>>> children_new;

    if (way) {
        node_sibling = siblings->get(index_node + 1);
        keys_new = (node->getKeys())->concat(*(node_sibling->getKeys()));
        index_insert_parent_key = node->getKeys()->getLength();
        index_parent_key = index_node;

        children_new = *(node->getChildren()->getSubSequence(0, node->getKeys())) + *(node_sibling->getChildren()->getSubSequence(0, node_sibling->getKeys()->getLength()));
    } else {
        node_sibling = siblings->get(index_node - 1);
        keys_new = (node_sibling->getKeys())->concat(*(node->getKeys()));
        index_insert_parent_key = node_sibling->getKeys()->getLength();
        index_parent_key = index_node - 1;

        children_new = *(node_sibling->getChildren()->getSubSequence(0, node_sibling->getKeys()->getLength())) + *(node->getChildren()->getSubSequence(0, node->getKeys()->getLength()));
    }

    Pair<K, V> parent_value = parent->getKeys()->get(index_parent_key);
    keys_new->insertAt(parent_value, index_insert_parent_key);

    ShrdPtr<Node> node_new(new Node(keys_new, children_new, parent, degree_));

    for (int i = 0; i < children_new->getLength(); i++) {
        if (children_new->get(i))
            children_new->get(i)->setParent(WeakPtr<Node>(node_new));
    }

    (parent->getKeys())->deleteElement(index_parent_key);

    if (parent->getKeys()->getLength() == 0) {
        root_ = node_new;
        node_new->setParent(WeakPtr<Node>(nullptr));
    }

    siblings->deleteElement(index_node);
    siblings->append(ShrdPtr<Node>(nullptr));
    siblings->set(index_parent_key, node_new);

    return node_new;
}

template <TotalOrdering K, typename V>
void BTree<K, V>::redistributeKeys(ShrdPtr<Node> node, int index_node, int way) {
    WeakPtr<Node> parent = node->getParent();
    ShrdPtr<Sequence<ShrdPtr<Node>>> siblings = parent->getChildren();
    ShrdPtr<Node> node_sibling;
    int index_parent_key;
    int index_sibling_key;
    Pair<K, V> parent_key;
    Pair<K, V> sibling_key;

    if (way) {
        node_sibling = siblings->get(index_node + 1);
        index_parent_key = index_node;
        parent_key = parent->getKeys()->get(index_parent_key);
        index_sibling_key = 0;
        sibling_key = node_sibling->getKeys()->get(index_sibling_key);
        node->getKeys()->append(parent_key);

        if (node_sibling->getChildren()->getFirst())
            node_sibling->getChildren()->getFirst()->setParent(WeakPtr<Node>(node));

        node->getChildren()->set(node->getKeys()->getLength(), node_sibling->getChildren()->getFirst());

        if (node_sibling->getChildren()->getFirst())
            node_sibling->getChildren()->getFirst()->setParent(WeakPtr<Node>(node));

        parent->getKeys()->set(index_parent_key, sibling_key);
        node_sibling->getKeys()->deleteElement(0);
        node_sibling->getChildren()->deleteElement(0);
        node_sibling->getChildren()->append(ShrdPtr<Node>(nullptr));
    } else {
        node_sibling = siblings->get(index_node - 1);
        index_parent_key = index_node - 1;
        parent_key = parent->getKeys()->get(index_parent_key);
        index_sibling_key = node_sibling->getKeys()->getLength() - 1;
        sibling_key = node_sibling->getKeys()->get(index_sibling_key);
        node->getKeys()->prepend(parent_key);

        if (node_sibling->getChildren()->get(index_sibling_key + 1))
            node_sibling->getChildren()->get(index_sibling_key + 1)->setParent(WeakPtr<Node>(node));

        node->getChildren()->prepend(node_sibling->getChildren()->get(index_sibling_key + 1));
        node->getChildren()->deleteElement(2 * degree_);

        if (node_sibling->getChildren()->getLast())
            node_sibling->getChildren()->getLast()->setParent(WeakPtr<Node>(node));

        parent->getKeys()->set(index_parent_key, sibling_key);
        node_sibling->getKeys()->deleteElement(index_sibling_key);
        node_sibling->getChildren()->deleteElement(index_sibling_key + 1);
        node_sibling->getChildren()->append(ShrdPtr<Node>(nullptr));
    }
}

template <TotalOrdering K, typename V>
void BTree<K, V>::deleteKey(ShrdPtr<Node> node, int index_key) {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();

    if (node->isLeaf())
        keys->deleteElement(index_key);
    else {
        if (children->get(index_key)->getKeys()->getLength() >= degree_) {
            deleteByRedistribute(node, index_key, 0);
        } else if (children->get(index_key + 1)->getKeys()->getLength() >= degree_) {
            deleteByRedistribute(node, index_key, 1);
        } else {
            deleteByMerge(node, index_key);
        }
    }
}

template <TotalOrdering K, typename V>
void BTree<K, V>::deleteByRedistribute(ShrdPtr<Node> node, int index_key, int way) {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();

    ShrdPtr<Node> child;
    Pair<K, V> key_child;

    if (way) {
        child = children->get(index_key + 1);
        key_child = child->getKeys()->getFirst();
    } else {
        child = children->get(index_key);
        key_child = child->getKeys()->getLast();
    }

    keys->set(index_key, key_child);
    deleteByKeyRecurse(child, key_child.getKey());
}

template <TotalOrdering K, typename V>
void BTree<K, V>::deleteByMerge(ShrdPtr<Node> node, int index_key) {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    ShrdPtr<Node> child_left = children->get(index_key);
    ShrdPtr<Node> child_right = children->get(index_key + 1);

    Pair<K, V> key_deleted = keys->get(index_key);

    ShrdPtr<Sequence<Pair<K, V>>> keys_new = *(child_left->getKeys()) + *(child_right->getKeys());
    keys_new->insertAt(key_deleted, child_left->getKeys()->getLength());
    ShrdPtr<Sequence<ShrdPtr<Node>>> children_new = *(child_left->getChildren()->getSubSequence(0, child_left->getKeys()->getLength())) + *(child_right->getChildren()->getSubSequence(0, child_right->getKeys()->getLength()));

    ShrdPtr<Node> node_new(new Node(keys_new, children_new, WeakPtr<Node>(node), degree_));

    for (int i = 0; i < children_new->getLength(); i++) {
        ShrdPtr<Node> child = children_new->get(i);

        if (child)
            child->setParent(WeakPtr<Node>(node_new));
    }

    keys->deleteElement(index_key);
    children->deleteElement(index_key);
    children->append(ShrdPtr<Node>(nullptr));
    children->set(index_key, node_new);

    deleteByKeyRecurse(node_new, key_deleted.getKey());

    if ((keys->getLength() == 0) && (node == root_)) {
        node_new->setParent(WeakPtr<Node>(nullptr));
        root_ = node_new;
    }
}

template <TotalOrdering K, typename V>
void BTree<K, V>::deleteByKey(K key) {
    try {
        deleteByKeyRecurse(root_, key);
    } catch (...) {
        throw;
    }
}





template <TotalOrdering K, typename V>
V BTree<K, V>::searchByKeyRecurse(ShrdPtr<Node> node, K key) const {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    int number_keys = keys->getLength();
    int index = 0;

    while ((number_keys > index) && (key > (keys->get(index)).getKey())) {
        index++;
    }

    if ((number_keys > index) && (key == (keys->get(index)).getKey()))
        return (keys->get(index)).getValue();
    else {
        if ((node->getChildren())->get(index)) {
            try {
                return searchByKeyRecurse((node->getChildren())->get(index), key);
            } catch (...) {
                throw;
            }
        } else
            throw std::out_of_range("The tree does not contain this key\n");
    }
}

template <TotalOrdering K, typename V>
V BTree<K, V>::searchByKey(K key) const {
    try {
        return searchByKeyRecurse(root_, key);
    } catch (...) {
        throw;
    }
}





template <TotalOrdering K, typename V>
Pair<K, V> BTree<K, V>::getMinSuperiorKeyRecurse(ShrdPtr<Node> node, K key) const {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    int number_keys = keys->getLength();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    int index = 0;

    while ((index < number_keys) && (key >= (keys->get(index)).getKey())) {
        index++;
    }

    if (index == number_keys) {
        Pair<K, V> last_key = keys->get(number_keys - 1);
        if (key == last_key.getKey())
            return last_key;
        else {
            if (node->isLeaf())
                throw std::out_of_range("There are no superior keys in the tree\n");
            else {
                try {
                    return getMinSuperiorKeyRecurse(children->get(index), key);
                } catch (...) {
                    throw;
                }
            }
        }
    } else {
        if ((index > 0) && (key == keys->get(index - 1).getKey()))
            return keys->get(index - 1);
        else {
            if (node->isLeaf())
                return keys->get(index);
            else {
                try {
                    return getMinSuperiorKeyRecurse(children->get(index), key);
                } catch (...) {
                    return keys->get(index);
                }
            }
        }
    }
}

template <TotalOrdering K, typename V>
Pair<K, V> BTree<K, V>::getMinSuperiorKey(K key) const {
    if (root_->getKeys()->getLength() != 0) {
        try {
            return getMinSuperiorKeyRecurse(root_, key);
        } catch (...) {
            throw;
        }
    } else {
        throw std::out_of_range("There are no superior keys in the tree\n");
    }
}





template <TotalOrdering K, typename V>
Pair<K, V> BTree<K, V>::getMaxInferiorKeyRecurse(ShrdPtr<Node> node, K key) const {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    int number_keys = keys->getLength();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    int index = 0;

    while ((index < number_keys) && (keys->get(index).getKey() < key)) {
        index++;
    }

    if (children->get(index)) {
        try {
            return getMaxInferiorKeyRecurse(children->get(index), key);
        } catch (...) {
            if (index > 0)
                return keys->get(index - 1);
            else
                throw std::out_of_range("There are no inferior keys in the tree\n");
        }
    } else {
        if (index > 0)
            return keys->get(index - 1);
        else
            throw std::out_of_range("There are no inferior keys in the tree\n");
    }
}

template <TotalOrdering K, typename V>
Pair<K, V> BTree<K, V>::getMaxInferiorKey(K key) const {
    if (root_->getKeys()->getLength() != 0) {
        try {
            return getMaxInferiorKeyRecurse(root_, key);
        } catch (...) {
            throw;
        }
    } else {
        throw std::out_of_range("There are no inferior keys in the tree\n");
    }
}





template <TotalOrdering K, typename V>
void BTree<K, V>::traversalRootChildrenRecurse(ShrdPtr<Node> node, ShrdPtr<Sequence<Pair<K, V>>> elements) const noexcept {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    int number_keys = keys->getLength();

    for (int i = 0; i < number_keys; i++) {
        elements->append(keys->get(i));
    }

    for (int i = 0; i <= number_keys; i++) {
        if (children->get(i))
            traversalRootChildrenRecurse(children->get(i), elements);
    }
}

template <TotalOrdering K, typename V>
ShrdPtr<Sequence<Pair<K, V>>> BTree<K, V>::traversalRootChildren() const noexcept {
    ShrdPtr<Sequence<Pair<K, V>>> elements(new ArraySequence<Pair<K, V>>);
    traversalRootChildrenRecurse(root_, elements);

    return elements;
}





template <TotalOrdering K, typename V>
void BTree<K, V>::traversalIncreasingOrderRecurse(ShrdPtr<Node> node, ShrdPtr<Sequence<Pair<K, V>>> elements) const noexcept {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();
    int number_keys = keys->getLength();

    for (int i = 0; i < number_keys; i++) {
        if (children->get(i))
            traversalIncreasingOrderRecurse(children->get(i), elements);

        elements->append(keys->get(i));
    }

    if (children->get(number_keys))
        traversalIncreasingOrderRecurse(children->get(number_keys), elements);
}

template <TotalOrdering K, typename V>
ShrdPtr<Sequence<Pair<K, V>>> BTree<K, V>::traversalIncreasingOrder() const noexcept {
    ShrdPtr<Sequence<Pair<K, V>>> elements(new ArraySequence<Pair<K, V>>);
    traversalIncreasingOrderRecurse(root_, elements);

    return elements;
}





template <TotalOrdering K, typename V>
void BTree<K, V>::traversalRecurse(ShrdPtr<Node> node) const noexcept {
    ShrdPtr<Sequence<Pair<K, V>>> keys = node->getKeys();
    ShrdPtr<Sequence<ShrdPtr<Node>>> children = node->getChildren();

    std::cout << "node: ";
    for (int i = 0; i < keys->getLength(); i++) {
        std::cout << (keys->get(i)).getKey() << "     ";
    }
    std::cout << "\nparent: ";
    if (node->getParent()) {
        for (int i = 0; i < ((node->getParent())->getKeys())->getLength(); i++) {
            std::cout << (((node->getParent())->getKeys())->get(i)).getKey() << "     ";
        }
    } else {
        std::cout << "none";
    }
    std::cout << "\n\n";

    for (int i = 0; i < children->getLength(); i++) {
        std::cout << "children of node: ";
        for (int j = 0; j < keys->getLength(); j++) {
            std::cout << (keys->get(j)).getKey() << "     ";
        }
        std::cout << "\n";
        std::cout << "child " << i << ": ";
        if (children->get(i))
            traversalRecurse(children->get(i));
        else
            std::cout << " null\n";
    }
}

template <TotalOrdering K, typename V>
void BTree<K, V>::traversal() const noexcept {
    traversalRecurse(root_);
}



#endif //LAB_3SEM_3_B_TREE_H
