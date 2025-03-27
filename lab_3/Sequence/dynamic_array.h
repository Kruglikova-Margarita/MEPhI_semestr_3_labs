#ifndef dynamicArray_h
#define dynamicArray_h

#include "../SmartPtrs/unq_ptr.h"
#include "../SmartPtrs/shrd_ptr.h"

template <typename T>
class DynamicArray {
private:
    size_t length_;
    UnqPtr<T[]> array_;

public:
    DynamicArray(const T *items, int count);
    DynamicArray(ShrdPtr<T[]> items, int count);
    DynamicArray() noexcept;
    DynamicArray(DynamicArray<T>&& dynamic_array) noexcept;

    T& getFirst() const;
    T& getLast() const;
    T& get(int index) const;
    size_t getLength() const noexcept;
    void append(T item) noexcept;
    void prepend(T item) noexcept;
    void insertAt(T item, int index);
    void deleteElement(int index);
    void set(int index, T value);
};



template <typename T>
DynamicArray<T>::DynamicArray(const T* items, int count) {
    if (count < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = count;

    if (length_ == 0)
        array_ = UnqPtr<T[]>();
    else {
        array_ = UnqPtr<T[]>(new T[count]);
        for (int i = 0; i < count; i++) {
            array_[i] = items[i];
        }
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(ShrdPtr<T[]> items, int count) {
    if (count < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = count;

    if (length_ == 0)
        array_ = UnqPtr<T[]>();
    else {
        array_ = UnqPtr<T[]>(new T[count]);
        for (int i = 0; i < count; i++) {
            array_[i] = items[i];
        }
    }
}

template <typename T>
DynamicArray<T>::DynamicArray() noexcept : length_(0), array_(nullptr) {}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& dynamic_array) noexcept : array_() {
    array_.swap(dynamic_array.array_);
    std::swap(length_, dynamic_array.length_);
}

template <typename T>
T& DynamicArray<T>::getFirst() const {
    if (length_ == 0)
        throw std::out_of_range("The sequence is empty\n");

    return array_[0];
}

template <typename T>
T& DynamicArray<T>::getLast() const {
    if (length_ == 0)
        throw std::out_of_range("The sequence is empty\n");

    return array_[length_ - 1];
}

template <typename T>
T& DynamicArray<T>::get(int index) const {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    return array_[index];
}

template <typename T>
size_t DynamicArray<T>::getLength() const noexcept {
    return length_;
}

template <typename T>
void DynamicArray<T>::append(T item) noexcept {
    if (length_ == 0) {
        array_ = UnqPtr<T[]>(new T[1]);
        array_[0] = item;
    } else {
        UnqPtr<T[]> copy_array(std::move(array_));

        array_ = UnqPtr<T[]>(new T[length_ + 1]);
        
        for (int i = 0; i < length_; i++) {
            array_[i] = copy_array[i];
        }
        
        array_[length_] = item;
    }

    length_++;
}

template <typename T>
void DynamicArray<T>::prepend(T item) noexcept {
    if (length_ == 0) {
        array_ = UnqPtr<T[]>(new T[1]);
        array_[0] = item;
    } else {
        UnqPtr<T[]> copy_array(std::move(array_));

        array_ = UnqPtr<T[]>(new T[length_ + 1]);
        array_[0] = item;

        for (int i = 1; i <= length_; i++) {
            array_[i] = copy_array[i - 1];
        }
    }

    length_++;
}

template <typename T>
void DynamicArray<T>::insertAt(T item, int index) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");
    
    UnqPtr<T[]> copy_array(std::move(array_));

    length_++;
    array_ = UnqPtr<T[]>(new T[length_]);

    for (int i = 0; i < index; i++) {
        array_[i] = copy_array[i];
    }

    array_[index] = item;

    for (int i = index + 1; i < length_; i++) {
        array_[i] = copy_array[i - 1];
    }
}

template <typename T>
void DynamicArray<T>::deleteElement(int index) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    if (length_ == 1) {
        array_ = UnqPtr<T[]>();
        length_--;
    } else {
        UnqPtr<T[]> copy_array(std::move(array_));
        
        length_--;
        array_ = UnqPtr<T[]>(new T[length_]);

        for (int i = 0; i < index; i++) {
            array_[i] = copy_array[i];
        }

        for (int i = index; i < length_; i++) {
            array_[i] = copy_array[i + 1];
        }
    }
}

template <typename T>
void DynamicArray<T>::set(int index, T value) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    array_[index] = value;
}

#endif
