#include "option.h"
#include "../SmartPtrs/unq_ptr.h"

#ifndef dynamicArray_h
#define dynamicArray_h

template <typename T>
class DynamicArray {
private:
    size_t length_;
    UnqPtr<Option<T>[]> array_;

public:
    DynamicArray(const T *items, int count);
    DynamicArray(UnqPtr<T[]>& items, int count);
    DynamicArray() noexcept;
    DynamicArray(int setLen);
    DynamicArray(DynamicArray<T>&& dynamic_array) noexcept;

    Option<T> getFirst() const;
    Option<T> getLast() const;
    Option<T> get(int index) const;
    size_t getLength() const noexcept;
    void append(T item) noexcept;
    void prepend(T item) noexcept;
    void insertAt(T item, int index);
    void deleteElement(int index);
    void set(int index, T value);
    void resize(size_t new_len);
};



template <typename T>
DynamicArray<T>::DynamicArray(const T* items, int count) {
    if (count < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = count;

    if (length_ == 0)
        array_ = UnqPtr<Option<T>[]>();
    else {
        array_ = UnqPtr<Option<T>[]>(new Option<T>[count]);
        for (int i = 0; i < count; i++) {
            array_[i] = Option<T>(items[i]);
        }
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(UnqPtr<T[]>& items, int count) {
    if (count < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = count;

    if (length_ == 0)
        array_ = UnqPtr<Option<T>[]>();
    else {
        array_ = UnqPtr<Option<T>[]>(new Option<T>[count]);
        for (int i = 0; i < count; i++) {
            array_[i] = Option<T>(items[i]);
        }
    }
}

template <typename T>
DynamicArray<T>::DynamicArray() noexcept : length_(0), array_(nullptr) {}

template <typename T>
DynamicArray<T>::DynamicArray(int setLen) {
    if (setLen < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = setLen;

    if (length_ == 0)
        array_ = UnqPtr<Option<T>[]>();
    else {
        array_ = UnqPtr<Option<T>[]>(new Option<T>[length_]);
        for (int i = 0; i < length_; i++) {
            array_[i] = Option<T>::getNone();
        }
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& dynamic_array) noexcept : array_() {
    array_.swap(dynamic_array.array_);
    std::swap(length_, dynamic_array.length_);
}

template <typename T>
Option<T> DynamicArray<T>::getFirst() const {
    if (length_ == 0)
        throw std::out_of_range("The sequence is empty\n");

    return array_[0];
}

template <typename T>
Option<T> DynamicArray<T>::getLast() const {
    if (length_ == 0)
        throw std::out_of_range("The sequence is empty\n");

    return array_[length_ - 1];
}

template <typename T>
Option<T> DynamicArray<T>::get(int index) const {
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
        array_ = UnqPtr<Option<T>[]>(new Option<T>[1]);
        array_[0] = Option<T>(item);
    } else {
        UnqPtr<Option<T>[]> copy_array(new Option<T>[length_]);

        for (int i = 0; i < length_; i++) {
            copy_array[i] = Option<T>(array_[i]);
        }

        array_ = UnqPtr<Option<T>[]>(new Option<T>[length_ + 1]);
        
        for (int i = 0; i < length_; i++) {
            array_[i] = copy_array[i];
        }
        
        array_[length_] = Option<T>(item);
    }

    length_++;
}

template <typename T>
void DynamicArray<T>::prepend(T item) noexcept {
    if (length_ == 0) {
        array_ = UnqPtr<Option<T>[]>(new Option<T>[1]);
        array_[0] = Option<T>(item);
    } else {
        UnqPtr<Option<T>[]> copy_array(new Option<T>[length_]);

        for (int i = 0; i < length_; i++) {
            copy_array[i] = Option(array_[i]);
        }

        array_ = UnqPtr<Option<T>[]>(new Option<T>[length_ + 1]);
        array_[0] = Option(item);

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
    
    UnqPtr<Option<T>[]> copy_array(new Option<T>[length_]);
    
    for (int i = 0; i < length_; i++) {
        copy_array[i] = Option<T>(array_[i]);
    }
    
    length_++;
    array_ = UnqPtr<Option<T>[]>(new Option<T>[length_]);

    for (int i = 0; i < index; i++) {
        array_[i] = Option<T>(copy_array[i]);
    }

    array_[index] = Option<T>(item);

    for (int i = index + 1; i < length_; i++) {
        array_[i] = Option<T>(copy_array[i - 1]);
    }
}

template <typename T>
void DynamicArray<T>::deleteElement(int index) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    if (length_ == 1) {
        array_ = UnqPtr<Option<T>[]>();
        length_--;
    } else {
        UnqPtr<Option<T>[]> copy_array(new Option<T>[length_]);

        for (int i = 0; i < length_; i++) {
            copy_array[i] = Option<T>(array_[i]);
        }
        
        length_--;
        array_ = UnqPtr<Option<T>[]>(new Option<T>[length_]);

        for (int i = 0; i < index; i++) {
            array_[i] = Option<T>(copy_array[i]);
        }

        for (int i = index; i < length_; i++) {
            array_[i] = Option<T>(copy_array[i + 1]);
        }
    }
}

template <typename T>
void DynamicArray<T>::set(int index, T value) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    array_[index] = Option<T>(value);
}

template <typename T>
void DynamicArray<T>::resize(size_t new_len) {
    if (new_len < 0)
        throw std::out_of_range("Invalid length of sequence\n");
    
    if (new_len != length_) {
        if (new_len == 0) {
            length_ = 0;
            array_ = UnqPtr<Option<T>[]>();
        } else {
            UnqPtr<Option<T>[]> copy_array(new Option<T>[length_]);

            for (int i = 0; i < length_; i++) {
                copy_array[i] = Option<T>(array_[i]);
            }
            
            array_ = UnqPtr<Option<T>[]>(new Option<T>[new_len]);

            for (int i = 0; i < std::min(length_, new_len); i++) {
                array_[i] = Option<T>(copy_array[i]);
            }
            
            for (int i = std::min(length_, new_len); i < new_len; i++) {
                array_[i] = Option<T>::getNone();
            }
            
            length_ = new_len;
        }
    }
}

#endif