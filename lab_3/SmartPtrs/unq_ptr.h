#ifndef LAB_3SEM_3_UNQ_PTR_H
#define LAB_3SEM_3_UNQ_PTR_H

#include <iostream>

template <typename T>
class UnqPtr {
private:
	T* ptr_;

public:
	UnqPtr() noexcept;
	UnqPtr(T* ptr) noexcept;
	UnqPtr(UnqPtr<T>&& ptr) noexcept;

	~UnqPtr() noexcept;

	void reset(T* setted_ptr) noexcept;
	void swap(UnqPtr<T>& other_ptr) noexcept;
	UnqPtr<T>& operator=(UnqPtr<T>&& setted_ptr) noexcept;
	operator bool() const noexcept;
	T& operator*() const noexcept;
	T* operator->() const noexcept;
	bool operator==(UnqPtr<T> other_ptr) const noexcept;
};



template <typename T>
class UnqPtr<T[]> {
private:
	T* ptr_;

public:
	UnqPtr() noexcept;
	UnqPtr(T* ptr) noexcept;
	UnqPtr(UnqPtr<T[]>&& ptr) noexcept;

	~UnqPtr() noexcept;

	void reset(T* setted_ptr) noexcept;
	void swap(UnqPtr<T[]>& other_ptr) noexcept;
	UnqPtr<T[]>& operator=(UnqPtr<T[]>&& setted_ptr) noexcept;
	operator bool() const noexcept;
	T& operator[](size_t index) const;
	bool operator==(UnqPtr<T[]> other_ptr) const noexcept;
};







template <typename T, typename... Args>
typename std::enable_if<!std::is_array<T>::value, UnqPtr<T>>::type make_unique(Args&&... args) {
	return UnqPtr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
inline UnqPtr<T>::UnqPtr() noexcept : ptr_(nullptr) {}

template <typename T>
inline UnqPtr<T>::UnqPtr(T* setted_ptr) noexcept : ptr_(nullptr) {
	std::swap(ptr_, setted_ptr);
}

template <typename T>
inline UnqPtr<T>::UnqPtr(UnqPtr<T>&& setted_ptr) noexcept : ptr_(nullptr) {
	std::swap(ptr_, setted_ptr.ptr_);
}

template <typename T>
inline UnqPtr<T>::~UnqPtr() noexcept {
	if (ptr_ != nullptr)
		delete ptr_;
}

template <typename T>
inline void UnqPtr<T>::reset(T* setted_ptr) noexcept {
	T* ptr = ptr_;

	if (ptr_ == setted_ptr)
		ptr_ = nullptr;
	else
		ptr_ = setted_ptr;

	delete ptr;
}

template <typename T>
inline void UnqPtr<T>::swap(UnqPtr<T>& other_ptr) noexcept {
	std::swap(ptr_, other_ptr.ptr_);
}

template <typename T>
inline UnqPtr<T>& UnqPtr<T>::operator=(UnqPtr<T>&& setted_ptr) noexcept {
	std::swap(ptr_, setted_ptr.ptr_);

	return *this;
}

template <typename T>
inline UnqPtr<T>::operator bool() const noexcept {
	if (ptr_ == nullptr)
		return false;
	else
		return true;
}

template <typename T>
inline T& UnqPtr<T>::operator*() const noexcept {
	return *ptr_;
}

template <typename T>
inline T* UnqPtr<T>::operator->() const noexcept {
	return ptr_;
}

template <typename T>
bool UnqPtr<T>::operator==(UnqPtr<T> other_ptr) const noexcept {
	if (ptr_ == other_ptr.ptr_)
		return true;
	else
		return false;
}







template <typename T>
inline UnqPtr<T[]>::UnqPtr() noexcept : ptr_(nullptr) {}

template <typename T>
inline UnqPtr<T[]>::UnqPtr(T* setted_ptr) noexcept : ptr_(nullptr) {
	std::swap(ptr_, setted_ptr);
}

template <typename T>
inline UnqPtr<T[]>::UnqPtr(UnqPtr<T[]>&& setted_ptr) noexcept : ptr_(nullptr) {
	std::swap(ptr_, setted_ptr.ptr_);
}

template <typename T>
inline UnqPtr<T[]>::~UnqPtr() noexcept {
	if (ptr_ != nullptr)
		delete[] ptr_;
}

template <typename T>
inline void UnqPtr<T[]>::reset(T* setted_ptr) noexcept {
	T* ptr = ptr_;

	if (ptr_ == setted_ptr)
		ptr_ = nullptr;
	else
		ptr_ = setted_ptr;
	
	delete[] ptr;
}

template <typename T>
inline void UnqPtr<T[]>::swap(UnqPtr<T[]>& other_ptr) noexcept {
	std::swap(ptr_, other_ptr.ptr_);
}

template <typename T>
inline UnqPtr<T[]>& UnqPtr<T[]>::operator=(UnqPtr<T[]>&& setted_ptr) noexcept {
	std::swap(ptr_, setted_ptr.ptr_);

	return *this;
}

template <typename T>
inline UnqPtr<T[]>::operator bool() const noexcept {
	if (ptr_ == nullptr)
		return false;
	else
		return true;
}

template <typename T>
inline T& UnqPtr<T[]>::operator[](size_t index) const {
	return ptr_[index];
}

template <typename T>
bool UnqPtr<T[]>::operator==(UnqPtr<T[]> other_ptr) const noexcept {
	if (ptr_ == other_ptr.ptr_)
		return true;
	else
		return false;
}

#endif
