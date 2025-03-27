#include <iostream>

#ifndef shrdPtr_h
#define shrdPtr_h

template <typename T>
class ShrdPtr {
private:
	T* ptr_;
	size_t* counter_;

	void destruct() noexcept;

public:
	ShrdPtr() noexcept;
	ShrdPtr(T* setted_ptr) noexcept;
	ShrdPtr(const ShrdPtr<T>& setted_ptr) noexcept;
	ShrdPtr(ShrdPtr<T>&& setted_ptr) noexcept;

	~ShrdPtr() noexcept;

	T* get() const noexcept;
	void reset(T* setted_ptr) noexcept;
	void swap(ShrdPtr<T>& other_ptr) noexcept;
	bool unique() const noexcept;
	size_t use_count() const noexcept;
	operator bool() const noexcept;
	ShrdPtr<T>& operator=(const ShrdPtr<T>& setted_ptr) noexcept;
	T& operator*() const noexcept;
	T* operator->() const noexcept;
	bool operator==(const ShrdPtr<T>& other_ptr) const noexcept;
};



template <typename T>
class ShrdPtr<T[]> {
private:
	T* ptr_;
	size_t* counter_;

	void destruct() noexcept;

public:
	ShrdPtr() noexcept;
	ShrdPtr(T* setted_ptr) noexcept;
	ShrdPtr(const ShrdPtr<T[]>& setted_ptr) noexcept;
	ShrdPtr(ShrdPtr<T[]>&& setted_ptr) noexcept;

	~ShrdPtr() noexcept;
	
	T* get() const noexcept;
	void reset(T* setted_ptr) noexcept;
	void swap(ShrdPtr<T[]>& other_ptr) noexcept;
	bool unique() const noexcept;
	size_t use_count() const noexcept;
	operator bool() const noexcept;
	ShrdPtr<T[]>& operator=(const ShrdPtr<T[]>& setted_ptr) noexcept;
	T& operator[](size_t index) const;
	bool operator==(const ShrdPtr<T[]>& other_ptr) const noexcept;
};







template <typename T, typename... Args>
typename std::enable_if<!std::is_array<T>::value, ShrdPtr<T>>::type make_shared(Args&&... args) {
	return ShrdPtr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
inline void ShrdPtr<T>::destruct() noexcept {
	if (*counter_ > 1) 
		(*counter_)--;
	else {
		if (ptr_ != nullptr) 
			delete ptr_;
		if (counter_ != nullptr) 
			delete counter_;
	}
}

template <typename T>
inline ShrdPtr<T>::ShrdPtr() noexcept : ptr_(nullptr), counter_(new size_t(1)) {}

template <typename T>
inline ShrdPtr<T>::ShrdPtr(T* setted_ptr) noexcept : ptr_(nullptr), counter_(new size_t(1)) {
	std::swap(ptr_, setted_ptr);
}

template <typename T>
inline ShrdPtr<T>::ShrdPtr(const ShrdPtr<T>& setted_ptr) noexcept : ptr_(setted_ptr.ptr_), counter_(setted_ptr.counter_) {
	(*counter_)++;
}

template <typename T>
inline ShrdPtr<T>::ShrdPtr(ShrdPtr<T>&& setted_ptr) noexcept : ptr_(nullptr), counter_(nullptr) {
	std::swap(ptr_, setted_ptr.ptr_);
	std::swap(counter_, setted_ptr.counter_);
}

template <typename T>
inline ShrdPtr<T>::~ShrdPtr() noexcept {
	destruct();
}

template<typename T>
inline T* ShrdPtr<T>::get() const noexcept {
	return ptr_;
}

template <typename T>
inline void ShrdPtr<T>::reset(T* setted_ptr) noexcept {
	if (ptr_ != setted_ptr) {
		if (*counter_ == 1)
			delete ptr_;
		else {
			(*counter_)--;
			counter_ = new size_t(1);
		}

		ptr_ = setted_ptr;
	}
}

template <typename T>
inline void ShrdPtr<T>::swap(ShrdPtr<T>& other_ptr) noexcept {
	std::swap(ptr_, other_ptr.ptr_);
	std::swap(counter_, other_ptr.counter_);
}

template <typename T>
inline bool ShrdPtr<T>::unique() const noexcept {
	if (*counter_ == 1)
		return true;
	else
		return false;
}

template <typename T>
inline size_t ShrdPtr<T>::use_count() const noexcept {
	return *counter_;
}

template <typename T>
inline ShrdPtr<T>::operator bool() const noexcept {
	if (ptr_ == nullptr)
		return false;
	else
		return true;
}

template <typename T>
inline ShrdPtr<T>& ShrdPtr<T>::operator=(const ShrdPtr<T>& setted_ptr) noexcept {
	if (*counter_ == 1) {
	 	delete ptr_;
		delete counter_;
	} else
		(*counter_)--;

	ptr_ = setted_ptr.ptr_;
	counter_ = setted_ptr.counter_;
	(*counter_)++;

	return *this;
}

template <typename T>
inline T& ShrdPtr<T>::operator* () const noexcept {
	return *ptr_;
}

template <typename T>
inline T* ShrdPtr<T>::operator->() const noexcept {
	return ptr_;
}

template <typename T>
bool ShrdPtr<T>::operator==(const ShrdPtr<T>& other_ptr) const noexcept {
	if (ptr_ == other_ptr.ptr_)
		return true;
	else
		return false;
}







template <typename T>
inline void ShrdPtr<T[]>::destruct() noexcept {
	if (*counter_ > 1)
		(*counter_)--;
	else {
		if (ptr_ != nullptr)
			delete[] ptr_;
		if (counter_ != nullptr)
			delete counter_;
	}
}

template <typename T>
inline ShrdPtr<T[]>::ShrdPtr() noexcept : ptr_(nullptr), counter_(new size_t(1)) {}

template <typename T>
inline ShrdPtr<T[]>::ShrdPtr(T* setted_ptr) noexcept : ptr_(nullptr), counter_(new size_t(1)) {
	std::swap(ptr_, setted_ptr);
}

template <typename T>
inline ShrdPtr<T[]>::ShrdPtr(const ShrdPtr<T[]>& setted_ptr) noexcept : ptr_(setted_ptr.ptr_), counter_(setted_ptr.counter_) {
	(*counter_)++;
}

template <typename T>
inline ShrdPtr<T[]>::ShrdPtr(ShrdPtr<T[]>&& setted_ptr) noexcept : ptr_(nullptr), counter_() {
	std::swap(ptr_, setted_ptr.ptr_);
	std::swap(counter_, setted_ptr.counter_);
}

template <typename T>
inline ShrdPtr<T[]>::~ShrdPtr() noexcept {
	destruct();
}

template<typename T>
inline T* ShrdPtr<T[]>::get() const noexcept {
	return ptr_;
}

template <typename T>
inline void ShrdPtr<T[]>::reset(T* setted_ptr) noexcept {
	if (ptr_ != setted_ptr) {
		if (*counter_ == 1)
			delete[] ptr_;
		else {
			(*counter_)--;
			counter_ = new size_t(1);
		}

		ptr_ = setted_ptr;
	}
}

template <typename T>
inline void ShrdPtr<T[]>::swap(ShrdPtr<T[]>& other_ptr) noexcept {
	std::swap(ptr_, other_ptr.ptr_);
	std::swap(counter_, other_ptr.counter_);
}

template <typename T>
inline bool ShrdPtr<T[]>::unique() const noexcept {
	if (*counter_ == 1)
		return true;
	else
		return false;
}

template <typename T>
inline size_t ShrdPtr<T[]>::use_count() const noexcept {
	return *counter_;
}

template <typename T>
inline ShrdPtr<T[]>::operator bool() const noexcept {
	if (ptr_ == nullptr)
		return false;
	else
		return true;
}

template <typename T>
inline ShrdPtr<T[]>& ShrdPtr<T[]>::operator=(const ShrdPtr<T[]>& setted_ptr) noexcept {
	if (*counter_ == 1) {
	 	delete[] ptr_;
		delete counter_;
	} else
		(*counter_)--;

	ptr_ = setted_ptr.ptr_;
	counter_ = setted_ptr.counter_;
	(*counter_)++;

	return *this;
}

template <typename T>
inline T& ShrdPtr<T[]>::operator[](size_t index) const {
	return ptr_[index];
}

template <typename T>
bool ShrdPtr<T[]>::operator==(const ShrdPtr<T[]>& other_ptr) const noexcept {
	if (ptr_ == other_ptr.ptr_)
		return true;
	else
		return false;
}

#endif
