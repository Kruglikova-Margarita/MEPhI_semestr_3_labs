#ifndef LAB_3SEM_3_SHRD_PTR_MM_H
#define LAB_3SEM_3_SHRD_PTR_MM_H

#include <iostream>
#include "memory_manager.h"

template <typename T>
class ShrdPtrMM {
private:
    ShrdPtr<MemoryManager> memory_manager_;
    T* ptr_;
    size_t* counter_;

    void destruct() noexcept;

public:
    ShrdPtrMM() noexcept;
    ShrdPtrMM(ShrdPtr<MemoryManager> manager) noexcept;
    ShrdPtrMM(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept;
    ShrdPtrMM(const ShrdPtrMM<T>& setted_ptr) noexcept;
    ShrdPtrMM(ShrdPtrMM<T>&& setted_ptr) noexcept;

    ~ShrdPtrMM() noexcept;

    void reset(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept;
    void swap(ShrdPtrMM<T>& other_ptr) noexcept;
    bool unique() const noexcept;
    size_t use_count() const noexcept;
    operator bool() const noexcept;
    ShrdPtrMM<T>& operator=(ShrdPtrMM<T> setted_ptr) noexcept;
    T& operator*() const noexcept;
    T* operator->() const noexcept;
    bool operator==(ShrdPtrMM<T> other_ptr) const noexcept;
};



template <typename T>
class ShrdPtrMM<T[]> {
private:
    ShrdPtr<MemoryManager> memory_manager_;
    T* ptr_;
    size_t* counter_;

    void destruct() noexcept;

public:
    ShrdPtrMM(ShrdPtr<MemoryManager> manager) noexcept;
    ShrdPtrMM(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept;
    ShrdPtrMM(const ShrdPtrMM<T[]>& setted_ptr) noexcept;
    ShrdPtrMM(ShrdPtrMM<T[]>&& setted_ptr) noexcept;

    ~ShrdPtrMM() noexcept;

    void reset(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept;
    void swap(ShrdPtrMM<T[]>& other_ptr) noexcept;
    bool unique() const noexcept;
    size_t use_count() const noexcept;
    operator bool() const noexcept;
    ShrdPtrMM<T[]>& operator=(ShrdPtrMM<T[]> setted_ptr) noexcept;
    T& operator[](size_t index) const;
    bool operator==(ShrdPtrMM<T[]> other_ptr) const noexcept;
};





template <typename T>
inline void ShrdPtrMM<T>::destruct() noexcept {
    if (memory_manager_) {
        if (*counter_ > 1)
            (*counter_)--;
        else {
            if (ptr_ != nullptr) {
                ptr_->~T();
                operator delete(ptr_, memory_manager_);
                ptr_ = nullptr;
            }
            if (counter_ != nullptr) {
                operator delete(counter_, memory_manager_);
                counter_ = nullptr;
            }
        }
    }
}

template <typename T>
inline ShrdPtrMM<T>::ShrdPtrMM() noexcept : memory_manager_(nullptr), ptr_(nullptr), counter_(nullptr) {}

template <typename T>
inline ShrdPtrMM<T>::ShrdPtrMM(ShrdPtr<MemoryManager> manager) noexcept : memory_manager_(manager), ptr_(nullptr), counter_(new(manager) size_t(1)) {}

template <typename T>
inline ShrdPtrMM<T>::ShrdPtrMM(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept : memory_manager_(manager), ptr_(nullptr), counter_(new(manager) size_t(1)) {
    std::swap(ptr_, setted_ptr);
}

template <typename T>
inline ShrdPtrMM<T>::ShrdPtrMM(const ShrdPtrMM<T>& setted_ptr) noexcept : memory_manager_(setted_ptr.memory_manager_), ptr_(setted_ptr.ptr_), counter_(setted_ptr.counter_) {
    (*counter_)++;
}

template <typename T>
inline ShrdPtrMM<T>::ShrdPtrMM(ShrdPtrMM<T>&& setted_ptr) noexcept : memory_manager_(ShrdPtr<MemoryManager>()), ptr_(nullptr), counter_(nullptr) {
    memory_manager_.swap(setted_ptr.memory_manager_);
    std::swap(ptr_, setted_ptr.ptr_);
    std::swap(counter_, setted_ptr.counter_);
}

template <typename T>
inline ShrdPtrMM<T>::~ShrdPtrMM() noexcept {
    destruct();
}

template <typename T>
inline void ShrdPtrMM<T>::reset(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept {
    if (ptr_ != setted_ptr) {
        if (*counter_ == 1) {
            ptr_->~T();
            operator delete(ptr_, memory_manager_);
            operator delete(counter_, memory_manager_);
        } else {
            (*counter_)--;
        }

        ptr_ = setted_ptr;
        if (manager)
            counter_ = new(manager) size_t(1);
        else
            counter_ = nullptr;
        memory_manager_ = manager;
    }
}

template <typename T>
inline void ShrdPtrMM<T>::swap(ShrdPtrMM<T>& other_ptr) noexcept {
    memory_manager_.swap(other_ptr.memory_manager_);
    std::swap(ptr_, other_ptr.ptr_);
    std::swap(counter_, other_ptr.counter_);
}

template <typename T>
inline bool ShrdPtrMM<T>::unique() const noexcept {
    if (*counter_ == 1)
        return true;
    else
        return false;
}

template <typename T>
inline size_t ShrdPtrMM<T>::use_count() const noexcept {
    return *counter_;
}

template <typename T>
inline ShrdPtrMM<T>::operator bool() const noexcept {
    if (ptr_ == nullptr)
        return false;
    else
        return true;
}

template <typename T>
inline ShrdPtrMM<T>& ShrdPtrMM<T>::operator=(ShrdPtrMM<T> setted_ptr) noexcept {
    if (memory_manager_) {
        if (*counter_ == 1) {
            if (ptr_ != nullptr) {
                ptr_->~T();
                operator delete(ptr_, memory_manager_);
            }

            if (counter_ != nullptr)
                operator delete(counter_, memory_manager_);
        } else
            (*counter_)--;
    }

    memory_manager_ = setted_ptr.memory_manager_;
    ptr_ = setted_ptr.ptr_;
    counter_ = setted_ptr.counter_;

    if (counter_)
        (*counter_)++;

    return *this;
}

template <typename T>
inline T& ShrdPtrMM<T>::operator* () const noexcept {
    return *ptr_;
}

template <typename T>
inline T* ShrdPtrMM<T>::operator->() const noexcept {
    return ptr_;
}

template <typename T>
bool ShrdPtrMM<T>::operator==(ShrdPtrMM<T> other_ptr) const noexcept {
    if (ptr_ == other_ptr.ptr_)
        return true;
    else
        return false;
}






template <typename T>
inline void ShrdPtrMM<T[]>::destruct() noexcept {
    if (*counter_ > 1)
        (*counter_)--;
    else {
        if (ptr_ != nullptr) {
            operator delete(ptr_, memory_manager_);
            ptr_ = nullptr;
        }
        if (counter_ != nullptr) {
            operator delete(counter_, memory_manager_);
            counter_ = nullptr;
        }
    }
}

template <typename T>
inline ShrdPtrMM<T[]>::ShrdPtrMM(ShrdPtr<MemoryManager> manager) noexcept : memory_manager_(manager), ptr_(nullptr), counter_(new(manager) size_t(1)) {}

template <typename T>
inline ShrdPtrMM<T[]>::ShrdPtrMM(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept : memory_manager_(manager), ptr_(nullptr), counter_(new(manager) size_t(1)) {
    std::swap(ptr_, setted_ptr);
}

template <typename T>
inline ShrdPtrMM<T[]>::ShrdPtrMM(const ShrdPtrMM<T[]>& setted_ptr) noexcept : memory_manager_(setted_ptr.memory_manager_), ptr_(setted_ptr.ptr_), counter_(setted_ptr.counter_) {
    (*counter_)++;
}

template <typename T>
inline ShrdPtrMM<T[]>::ShrdPtrMM(ShrdPtrMM<T[]>&& setted_ptr) noexcept : memory_manager_(ShrdPtr<MemoryManager>()), ptr_(nullptr), counter_() {
    memory_manager_.swap(setted_ptr.memory_manager_);
    std::swap(ptr_, setted_ptr.ptr_);
    std::swap(counter_, setted_ptr.counter_);
}

template <typename T>
inline ShrdPtrMM<T[]>::~ShrdPtrMM() noexcept {
    destruct();
}

template <typename T>
inline void ShrdPtrMM<T[]>::reset(ShrdPtr<MemoryManager> manager, T* setted_ptr) noexcept {
    if (ptr_ != setted_ptr) {
        if (*counter_ == 1) {
            operator delete(ptr_, memory_manager_);
            operator delete(counter_, memory_manager_);
        } else {
            (*counter_)--;
        }

        ptr_ = setted_ptr;
        counter_ = new(manager) size_t(1);
        memory_manager_ = manager;
    }
}

template <typename T>
inline void ShrdPtrMM<T[]>::swap(ShrdPtrMM<T[]>& other_ptr) noexcept {
    memory_manager_.swap(other_ptr.memory_manager_);
    std::swap(ptr_, other_ptr.ptr_);
    std::swap(counter_, other_ptr.counter_);
}

template <typename T>
inline bool ShrdPtrMM<T[]>::unique() const noexcept {
    if (*counter_ == 1)
        return true;
    else
        return false;
}

template <typename T>
inline size_t ShrdPtrMM<T[]>::use_count() const noexcept {
    return *counter_;
}

template <typename T>
inline ShrdPtrMM<T[]>::operator bool() const noexcept {
    if (ptr_ == nullptr)
        return false;
    else
        return true;
}

template <typename T>
inline ShrdPtrMM<T[]>& ShrdPtrMM<T[]>::operator=(ShrdPtrMM<T[]> setted_ptr) noexcept {
    if (*counter_ == 1) {
        operator delete(ptr_, memory_manager_);
        operator delete(counter_, memory_manager_);
    } else
        (*counter_)--;

    memory_manager_ = setted_ptr.memory_manager_;
    ptr_ = setted_ptr.ptr_;
    counter_ = setted_ptr.counter_;
    (*counter_)++;

    return *this;
}

template <typename T>
inline T& ShrdPtrMM<T[]>::operator[](size_t index) const {
    return ptr_[index];
}

template <typename T>
bool ShrdPtrMM<T[]>::operator==(ShrdPtrMM<T[]> other_ptr) const noexcept {
    if (ptr_ == other_ptr.ptr_)
        return true;
    else
        return false;
}


#endif //LAB_3SEM_3_SHRD_PTR_MM_H
