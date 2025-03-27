#include "dynamic_array.h"
#include "linked_list.h"
#include "../SmartPtrs/unq_ptr.h"
#include "../SmartPtrs/shrd_ptr.h"

#ifndef sequence_h
#define sequence_h

template <typename T>
class Sequence {
public:
    virtual ~Sequence() {};

    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(int index) const = 0;
    virtual UnqPtr<Sequence<T>> getSubSequence(int start_index, int end_index) const = 0;
    virtual size_t getLength() const noexcept = 0;
    virtual void append(T item) noexcept = 0;
    virtual void prepend(T item) noexcept = 0;
    virtual void insertAt(T item, int index) = 0;
    virtual void deleteElement(int index) = 0;
    virtual void set(int index, T value) = 0;
    virtual void swap(int index1, int index2) = 0;
    virtual UnqPtr<Sequence<T>> concat(const Sequence<T>& added_sequence) const noexcept = 0;
    virtual T operator[](int index) const = 0;
    virtual UnqPtr<Sequence<T>> operator+(const Sequence<T>& added_sequence) const noexcept = 0;
    virtual bool operator==(const Sequence<T>& cmp_sequence) const noexcept = 0;
    virtual UnqPtr<Sequence<T>> map(T (*function)(T)) const noexcept = 0;
    virtual UnqPtr<Sequence<T>> where(bool (*function)(T)) const noexcept = 0;
    virtual T reduce(T (*function)(T, T), T c) const = 0;

};



template <typename T>
class ArraySequence : public Sequence<T> {
private:
    UnqPtr<DynamicArray<T>> dynamic_array_;

public:
    ArraySequence(T *items, int count);
    ArraySequence(UnqPtr<T[]>& items, int count);
    ArraySequence() noexcept;
    ArraySequence(ArraySequence<T> &&arraySequence) noexcept;
    ArraySequence(const Sequence<T> &copy) noexcept;

    T getFirst() const override;
    T getLast() const override;
    T get(int index) const override;
    UnqPtr<Sequence<T>> getSubSequence(int start_index, int end_index) const override;
    size_t getLength() const noexcept override;
    void append(T item) noexcept override;
    void prepend(T item) noexcept override;
    void insertAt(T item, int index) override;
    void deleteElement(int index) override;
    void set(int index, T value) override;
    void swap(int index1, int index2) override;
    UnqPtr<Sequence<T>> concat(const Sequence<T>& added_sequence) const noexcept override;
    T operator[](int index) const override;
    UnqPtr<Sequence<T>> operator+(const Sequence<T>& added_sequence) const noexcept override;
    bool operator==(const Sequence<T>& cmp_sequence) const noexcept override;
    UnqPtr<Sequence<T>> map(T (*function)(T)) const noexcept override;
    UnqPtr<Sequence<T>> where(bool (*function)(T)) const noexcept override;
    T reduce(T (*function)(T, T), T c) const override;
};



template <typename T>
class LinkedListSequence : public Sequence<T> {
private:
    UnqPtr<LinkedList<T>> linked_list_;

public:
    LinkedListSequence(const T *items, int count);
    LinkedListSequence(UnqPtr<T[]>& items, int count);
    LinkedListSequence() noexcept;
    LinkedListSequence(LinkedListSequence<T> &&list) noexcept;
    LinkedListSequence(const Sequence<T> &copy) noexcept;

    T getFirst() const override;
    T getLast() const override;
    T get(int index) const override;
    UnqPtr<Sequence<T>> getSubSequence(int start_index, int end_index) const override;
    size_t getLength() const noexcept override;
    void append(T item) noexcept override;
    void prepend(T item) noexcept override;
    void insertAt(T item, int index) override;
    void deleteElement(int index) override;
    void set(int index, T value) override;
    void swap(int index1, int index2) override;
    UnqPtr<Sequence<T>> concat(const Sequence<T>& added_sequence) const noexcept override;
    T operator[](int index) const override;
    UnqPtr<Sequence<T>> operator+(const Sequence<T>& added_sequence) const noexcept override;
    bool operator==(const Sequence<T>& cmp_sequence) const noexcept override;
    UnqPtr<Sequence<T>> map(T (*function)(T)) const noexcept override;
    UnqPtr<Sequence<T>> where(bool (*function)(T)) const noexcept override;
    T reduce(T (*function)(T, T), T c) const override;
};







template <typename T>
ArraySequence<T>::ArraySequence(T *items, int count) {
    try {
        dynamic_array_ = UnqPtr<DynamicArray<T>>(new DynamicArray<T>(items, count));
    }
    catch (...) {
        throw;
    }
}

template <typename T>
ArraySequence<T>::ArraySequence(UnqPtr<T[]>& items, int count) {
    try {
        dynamic_array_ = UnqPtr<DynamicArray<T>>(new DynamicArray<T>(items, count));
    }
    catch (...) {
        throw;
    }
}

template <typename T>
ArraySequence<T>::ArraySequence() noexcept : dynamic_array_(new DynamicArray<T>) {}

template <typename T>
ArraySequence<T>::ArraySequence(ArraySequence<T> &&array_sequence) noexcept : dynamic_array_() {
    dynamic_array_.swap(array_sequence.dynamic_array_);
}

template <typename T>
ArraySequence<T>::ArraySequence(const Sequence<T> &copy) noexcept {
    size_t len = copy.getLength();

    if (len == 0)
        dynamic_array_ = UnqPtr<DynamicArray<T>>(new DynamicArray<T>);
    else {
        UnqPtr<T[]> items(new T[len]);

        for (int i = 0; i < len; i++) {
            items[i] = copy[i];
        }

        dynamic_array_ = UnqPtr<DynamicArray<T>>(new DynamicArray<T>(items, len));
    }
}

template <typename T>
T ArraySequence<T>::getFirst() const {
    try {
        return dynamic_array_->getFirst();
    }
    catch (...) {
        throw;
    }
}

template <typename T>
T ArraySequence<T>::getLast() const {
    try {
        return dynamic_array_->getLast();
    }
    catch (...) {
        throw;
    }
}

template <typename T>
T ArraySequence<T>::get(int index) const {
    try {
        return dynamic_array_->get(index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
UnqPtr<Sequence<T>> ArraySequence<T>::getSubSequence(int start_index, int end_index) const {
    size_t len = dynamic_array_->getLength();

    if ((start_index < 0) || (start_index >= len) || (end_index < 0) || (end_index >= len))
        throw std::out_of_range("Impossible to get subsequence because index is out of range\n");

    if (start_index > end_index)
        throw std::out_of_range("Impossible to get subsequence because start index is more than end index\n");

    UnqPtr<T[]> items(new T[end_index - start_index + 1]);

    for (int i = start_index; i <= end_index; i++) {
        items[i - start_index] = dynamic_array_->get(i);
    }

    UnqPtr<Sequence<T>> sub_sequence = UnqPtr<Sequence<T>>(new ArraySequence<T>(items, (end_index - start_index + 1)));

    return sub_sequence;
}

template <typename T>
size_t ArraySequence<T>::getLength() const noexcept {
    return dynamic_array_->getLength();
}

template <typename T>
void ArraySequence<T>::append(T item) noexcept {
    dynamic_array_->append(item);
}

template <typename T>
void ArraySequence<T>::prepend(T item) noexcept {
    dynamic_array_->prepend(item);
}

template <typename T>
void ArraySequence<T>::insertAt(T item, int index) {
    try {
        dynamic_array_->insertAt(item, index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
void ArraySequence<T>::deleteElement(int index) {
    try {
        dynamic_array_->deleteElement(index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
void ArraySequence<T>::set(int index, T value) {
    try {
        dynamic_array_->set(index, value);
    }
    catch(...) {
        throw;
    }
}

template <typename T>
void ArraySequence<T>::swap(int index1, int index2) {
    if ((index1 < 0) || (index1 >= this->getLength()) || (index2 < 0) || (index2 >= this->getLength()))
        throw std::out_of_range("Invalid index\n");

    T value1 = this->get(index1);
    T value2 = this->get(index2);

    this->set(index1, value2);
    this->set(index2, value1);
}

template <typename T>
UnqPtr<Sequence<T>> ArraySequence<T>::concat(const Sequence<T>& added_sequence) const noexcept {
    size_t this_len = dynamic_array_->getLength();
    size_t added_len = added_sequence.getLength();

    UnqPtr<Sequence<T>> concat_sequence(new ArraySequence<T>);

    for (int i = 0; i < this_len; i++) {
        concat_sequence->append(this->get(i));
    }

    for (int i = 0; i < added_len; i++) {
        concat_sequence->append(added_sequence.get(i));
    }

    return concat_sequence;
}

template <typename T>
T ArraySequence<T>::operator[](int index) const {
    try {
        return this->get(index);
    }
    catch(...) {
        throw;
    }
}

template <typename T>
UnqPtr<Sequence<T>> ArraySequence<T>::operator+(const Sequence<T> &added_sequence) const noexcept {
    UnqPtr<Sequence<T>> new_sequence = this->concat(added_sequence);

    return new_sequence;
}

template <typename T>
bool ArraySequence<T>::operator==(const Sequence<T>& cmp_sequence) const noexcept {
    size_t this_len = this->getLength();
    size_t cmp_len = cmp_sequence.getLength();

    if (this_len != cmp_len)
        return false;

    for (int i = 0; i < this_len; i++) {
        T item1 = (*this)[i];
        T item2 = cmp_sequence[i];

        if (item1 != item2)
            return false;
    }

    return true;
}

template <typename T>
UnqPtr<Sequence<T>> ArraySequence<T>::map(T (*function)(T)) const noexcept {
    size_t len = this->getLength();

    if (len == 0) {
        UnqPtr<Sequence<T>> map_sequence = UnqPtr<Sequence<T>>(new ArraySequence<T>);

        return map_sequence;
    }

    UnqPtr<T[]> items = UnqPtr<T[]>(new T[len]);

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];
        items[i] = function(el);
    }

    UnqPtr<Sequence<T>> map_sequence = UnqPtr<Sequence<T>>(new ArraySequence<T>(items, len));

    return map_sequence;
}

template <typename T>
UnqPtr<Sequence<T>> ArraySequence<T>::where(bool (*function)(T)) const noexcept {
    size_t len = this->getLength();

    if (len == 0) {
        UnqPtr<Sequence<T>> where_sequence = UnqPtr<Sequence<T>>(new ArraySequence<T>);

        return where_sequence;
    }

    size_t count = 0;

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];

        if (function(el))
            count++;
    }

    if (count == 0) {
        UnqPtr<Sequence<T>> where_sequence = UnqPtr<Sequence<T>>(new ArraySequence<T>);

        return where_sequence;
    }

    UnqPtr<T[]> items = UnqPtr<T[]>(new T[count]);
    size_t index = 0;

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];

        if (function(el)) {
            items[index] = el;
            index++;
        }
    }

    UnqPtr<Sequence<T>> where_sequence = UnqPtr<Sequence<T>>(new ArraySequence<T>(items, count));

    return where_sequence;
}

template <typename T>
T ArraySequence<T>::reduce(T (*function)(T, T), T c) const {
    size_t len = this->getLength();

    if (len == 0)
        throw std::out_of_range("Impossible to reduce\n");

    T result = c;

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];
        result = function(el, result);
    }

    return result;
}









template <typename T>
LinkedListSequence<T>::LinkedListSequence(const T *items, int count) {
    try {
        linked_list_ = UnqPtr<LinkedList<T>>(new LinkedList<T>(items, count));
    }
    catch (...) {
        throw;
    }
}

template <typename T>
LinkedListSequence<T>::LinkedListSequence(UnqPtr<T[]>& items, int count) {
    try {
        linked_list_ = UnqPtr<LinkedList<T>>(new LinkedList<T>(items, count));
    }
    catch (...) {
        throw;
    }
}

template <typename T>
LinkedListSequence<T>::LinkedListSequence() noexcept : linked_list_(new LinkedList<T>) {}

template <typename T>
LinkedListSequence<T>::LinkedListSequence(LinkedListSequence<T>&& list) noexcept : linked_list_() {
    linked_list_.swap(list.linked_list_);
}

template <typename T>
LinkedListSequence<T>::LinkedListSequence(const Sequence<T>& copy) noexcept {
    size_t len = copy.getLength();

    if (len == 0)
        linked_list_ = UnqPtr<LinkedList<T>>(new LinkedList<T>);
    else {
        UnqPtr<T[]> items = UnqPtr<T[]>(new T[len]);

        for (int i = 0; i < len; i++) {
            items[i] = copy[i];
        }

        linked_list_ = UnqPtr<LinkedList<T>>(new LinkedList<T>(items, len));
    }
}

template <typename T>
T LinkedListSequence<T>::getFirst() const {
    try {
        return linked_list_->getFirst();
    }
    catch (...) {
        throw;
    }
}

template <typename T>
T LinkedListSequence<T>::getLast() const {
    try {
        return linked_list_->getLast();
    }
    catch (...) {
        throw;
    }
}

template <typename T>
T LinkedListSequence<T>::get(int index) const {
    try {
        return linked_list_->get(index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
UnqPtr<Sequence<T>> LinkedListSequence<T>::getSubSequence(int start_index, int end_index) const {
    size_t len = linked_list_->getLength();

    if ((start_index < 0) || (start_index >= len) || (end_index < 0) || (end_index >= len))
        throw std::out_of_range("Impossible to get subsequence because index is out of range\n");

    if (start_index > end_index)
        throw std::out_of_range("Impossible to get subsequence because start index is more than end index\n");

    UnqPtr<T[]> items = UnqPtr<T[]>(new T[end_index - start_index + 1]);

    for (int i = start_index; i <= end_index; i++) {
        items[i - start_index] = linked_list_->get(i);
    }

    UnqPtr<Sequence<T>> subSequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>(items, (end_index - start_index + 1)));

    return subSequence;
}

template <typename T>
size_t LinkedListSequence<T>::getLength() const noexcept {
    return linked_list_->getLength();
}

template <typename T>
void LinkedListSequence<T>::append(T item) noexcept {
    linked_list_->append(item);
}

template <typename T>
void LinkedListSequence<T>::prepend(T item) noexcept {
    linked_list_->prepend(item);
}

template <typename T>
void LinkedListSequence<T>::insertAt(T item, int index) {
    try {
        linked_list_->insertAt(item, index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
void LinkedListSequence<T>::deleteElement(int index) {
    try {
        linked_list_->deleteElement(index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
void LinkedListSequence<T>::set(int index, T value) {
    try {
        linked_list_->set(index, value);
    }
    catch(...) {
        throw;
    }
}

template <typename T>
void LinkedListSequence<T>::swap(int index1, int index2) {
    if ((index1 < 0) || (index1 >= this->getLength()) || (index2 < 0) || (index2 >= this->getLength()))
        throw std::out_of_range("Invalid index\n");

    T value1 = this->get(index1);
    T value2 = this->get(index2);

    this->set(index1, value2);
    this->set(index2, value1);
}

template <typename T>
UnqPtr<Sequence<T>> LinkedListSequence<T>::concat(const Sequence<T>& added_sequence) const noexcept {
    size_t this_len = linked_list_->getLength();
    size_t added_len = added_sequence.getLength();

    if ((this_len + added_len) == 0) {
        UnqPtr<Sequence<T>> concat_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>);

        return concat_sequence;
    }

    UnqPtr<T[]> items = UnqPtr<T[]>(new T[this_len + added_len]);

    for (int i = 0; i < this_len; i++) {
        items[i] = linked_list_->get(i);
    }

    for (int i = 0; i < added_len; i++) {
        items[i + this_len] = added_sequence.get(i);
    }

    UnqPtr<Sequence<T>> concat_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>(items, this_len + added_len));

    return concat_sequence;
}

template <typename T>
T LinkedListSequence<T>::operator[](int index) const {
    try {
        return this->get(index);
    }
    catch (...) {
        throw;
    }
}

template <typename T>
UnqPtr<Sequence<T>> LinkedListSequence<T>::operator+(const Sequence<T>& added_sequence) const noexcept {
    UnqPtr<Sequence<T>> new_sequence = this->concat(added_sequence);

    return new_sequence;
}

template <typename T>
bool LinkedListSequence<T>::operator==(const Sequence<T> &cmp_sequence) const noexcept {
    size_t len1 = this->getLength();
    size_t len2 = cmp_sequence.getLength();

    if (len1 != len2)
        return false;

    for (int i = 0; i < len1; i++) {
        T item1 = (*this)[i];
        T item2 = cmp_sequence[i];

        if (item1 != item2)
            return false;
    }

    return true;
}

template <typename T>
UnqPtr<Sequence<T>> LinkedListSequence<T>::map(T (*function)(T)) const noexcept {
    size_t len = this->getLength();

    if (len == 0) {
        UnqPtr<Sequence<T>> map_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>);

        return map_sequence;
    }

    UnqPtr<T[]> items = UnqPtr<T[]>(new T[len]);

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];
        items[i] = function(el);
    }

    UnqPtr<Sequence<T>> map_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>(items, len));

    return map_sequence;
}

template <typename T>
UnqPtr<Sequence<T>> LinkedListSequence<T>::where(bool (*function)(T)) const noexcept {
    size_t len = this->getLength();

    if (len == 0) {
        UnqPtr<Sequence<T>> where_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>);

        return where_sequence;
    }

    size_t count = 0;

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];
        if (function(el))
            count++;
    }

    if (count == 0) {
        UnqPtr<Sequence<T>> where_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>);

        return where_sequence;
    }

    UnqPtr<T[]> items = UnqPtr<T[]>(new T[count]);
    size_t index = 0;

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];

        if (function(el)) {
            items[index] = el;
            index++;
        }
    }

    UnqPtr<Sequence<T>> where_sequence = UnqPtr<Sequence<T>>(new LinkedListSequence<T>(items, count));

    return where_sequence;
}

template <typename T>
T LinkedListSequence<T>::reduce(T (*function)(T, T), T c) const {
    size_t len = this->getLength();

    if (len == 0)
        throw std::out_of_range("Impossible to reduce\n");

    T result = c;

    for (int i = 0; i < len; i++) {
        T el = (*this)[i];
        result = function(el, result);
    }

    return result;
}




#endif