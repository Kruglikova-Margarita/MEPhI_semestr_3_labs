#ifndef LAB_3SEM_3_PAIR_H
#define LAB_3SEM_3_PAIR_H

#include "concept_total_ordering.h"

template <TotalOrdering K, typename V>
class Pair {
private:
    K key_;
    V value_;

public:
    Pair() = default;
    Pair(K key, V value) noexcept;
    Pair(Pair<K, V>& pair) noexcept;

    K getKey() const noexcept;
    V getValue() const noexcept;
    void setKey(K key) noexcept;
    void setValue(V value) noexcept;
    //bool operator =(const Pair<K, V>& pair) const noexcept;
    bool operator !=(const Pair<K, V>& pair) const noexcept;
};



template <TotalOrdering K, typename V>
Pair<K, V>::Pair(K key, V value) noexcept : key_(key), value_(value) {}

template <TotalOrdering K, typename V>
Pair<K, V>::Pair(Pair<K, V>& pair) noexcept : key_(pair.key_), value_(pair.value_) {}

template <TotalOrdering K, typename V>
K Pair<K, V>::getKey() const noexcept {
    return key_;
}

template <TotalOrdering K, typename V>
V Pair<K, V>::getValue() const noexcept {
    return value_;
}

template <TotalOrdering K, typename V>
void Pair<K, V>::setKey(K key) noexcept {
    key_ = key;
}

template <TotalOrdering K, typename V>
void Pair<K, V>::setValue(V value) noexcept {
    value_ = value;
}
//
//template <TotalOrdering K, typename V>
//bool Pair<K, V>::operator =(const Pair<K, V>& pair) const noexcept {
//    if ((key_ == pair.key_) && (value_ == pair.value_))
//        return true;
//    else
//        return false;
//}

template <TotalOrdering K, typename V>
bool Pair<K, V>::operator !=(const Pair<K, V>& pair) const noexcept {
    if ((key_ == pair.key_) && (value_ == pair.value_))
        return false;
    else
        return true;
}


#endif //LAB_3SEM_3_PAIR_H
