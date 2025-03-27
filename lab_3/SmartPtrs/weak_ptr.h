#ifndef LAB_3SEM_3_WEAK_PTR_H
#define LAB_3SEM_3_WEAK_PTR_H

#include "shrd_ptr.h"

template <typename T>
class WeakPtr {
    template<typename T1>
    friend class ShrdPtr;
private:
    T* ptr_;

public:
    explicit WeakPtr(ShrdPtr<T> shrd_ptr) noexcept;
    WeakPtr(const WeakPtr<T>& weak_ptr) noexcept;

    T& operator*() const noexcept;
    T* operator->() const noexcept;
    explicit operator bool() const noexcept;
    WeakPtr<T>& operator=(WeakPtr<T> weak_ptr) noexcept;
};



template <typename T>
WeakPtr<T>::WeakPtr(ShrdPtr<T> shrd_ptr) noexcept : ptr_(shrd_ptr.ptr_) {}

template <typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& weak_ptr) noexcept : ptr_(weak_ptr.ptr_) {}

template <typename T>
inline T& WeakPtr<T>::operator*() const noexcept {
    return *ptr_;
}

template <typename T>
inline T* WeakPtr<T>::operator->() const noexcept {
    return ptr_;
}

template <typename T>
inline WeakPtr<T>::operator bool() const noexcept {
    if (ptr_ == nullptr)
        return false;
    else
        return true;
}

template <typename T>
inline WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T> weak_ptr) noexcept {
    ptr_ = weak_ptr.ptr_;

    return *this;
}


#endif //LAB_3SEM_3_WEAK_PTR_H
