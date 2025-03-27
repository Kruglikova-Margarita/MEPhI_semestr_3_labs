#include "../SmartPtrs/unq_ptr.h"
#include "../SmartPtrs/shrd_ptr.h"

#ifndef linkedList_h
#define linkedList_h

template <typename T>
class LinkedList {
private:
    class Node {
    public:
        T data_;
        ShrdPtr<Node> next_;
    };

    size_t length_;
    ShrdPtr<Node> head_;
    ShrdPtr<Node> tail_;

public:
    LinkedList(const T *items, int count);
    LinkedList(UnqPtr<T[]>& items, int count);
    LinkedList() noexcept;
    LinkedList(LinkedList<T> &&list) noexcept;

    T getFirst() const;
    T getLast() const;
    T get(int index) const;
    UnqPtr<LinkedList<T>> getSubList(int start_index, int end_index) const;
    size_t getLength() const noexcept;
    void append(T item) noexcept;
    void prepend(T item) noexcept;
    void insertAt(T item, int index);
    void deleteElement(int index);
    void set(int index, T value);
    UnqPtr<LinkedList<T>> concat(const UnqPtr<LinkedList<T>> list);
};




template <typename T>
LinkedList<T>::LinkedList(const T *items, int count) {
    if (count < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = count;
    
    if (length_ == 0) {
        head_ = ShrdPtr<Node>();
        tail_ = ShrdPtr<Node>();
    } else {
        head_ = ShrdPtr<Node>(new Node);
        head_->data_ = items[0];
        head_->next_ = ShrdPtr<Node>();
        tail_ = head_;
        ShrdPtr<Node> ptr = head_;

        for (int i = 1; i < count; i++) {
            ShrdPtr<Node> ptr_next = ShrdPtr<Node>(new Node);
            ptr_next->data_ = items[i];
            ptr_next->next_ = ShrdPtr<Node>(nullptr);
            ptr->next_ = ptr_next;
            ptr = ptr_next;
            tail_ = ptr_next;
        }
    }
}

template <typename T>
LinkedList<T>::LinkedList(UnqPtr<T[]>& items, int count) {
    if (count < 0)
        throw std::out_of_range("Invalid length of sequence\n");

    length_ = count;
    
    if (length_ == 0) {
        head_ = ShrdPtr<Node>();
        tail_ = ShrdPtr<Node>();
    } else {
        head_ = ShrdPtr<Node>(new Node);
        head_->data_ = items[0];
        head_->next_ = ShrdPtr<Node>();
        tail_ = head_;
        ShrdPtr<Node> ptr = head_;

        for (int i = 1; i < count; i++) {            
            ShrdPtr<Node> ptr_next = ShrdPtr<Node>(new Node);
            ptr_next->data_ = items[i];
            ptr_next->next_ = ShrdPtr<Node>(nullptr);
            ptr->next_ = ptr_next;
            ptr = ptr_next;
            tail_ = ptr_next;
        }
    }
}

template <typename T>
LinkedList<T>::LinkedList() noexcept : length_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&list) noexcept {
    length_ = list.length_;

    if (length_ == 0) {
        head_ = ShrdPtr<Node>();
        tail_ = ShrdPtr<Node>();
    } else {
        head_ = ShrdPtr<Node>(new Node);
        head_->data_ = list.head_->data_;
        head_->next_ = ShrdPtr<Node>();
        tail_ = head_;
        ShrdPtr<Node> ptr = head_;
        ShrdPtr<Node> ptr_list = list.head_->next_;

        for (int i = 1; i < length_; i++) {
            ShrdPtr<Node> ptr_next = ShrdPtr<Node>(new Node);
            ptr_next->data_ = ptr_list->data_;
            ptr_next->next_ = ShrdPtr<Node>();
            ptr->next_ = ptr_next;
            tail_ = ptr_next;
            ptr = ptr_next;
            ptr_list = ptr_list->next_;
        }
    }
}

template <typename T>
T LinkedList<T>::getFirst() const {
    if (length_ == 0)
        throw std::out_of_range("The sequence is empty\n");

    return head_->data_;
}

template <typename T>
T LinkedList<T>::getLast() const {
    if (length_ == 0)
        throw std::out_of_range("The sequence is empty\n");
    
    return tail_->data_;
}

template <typename T>
T LinkedList<T>::get(int index) const {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");
    
    ShrdPtr<Node> ptr(head_);

    for (int i = 0; i < index; i++) {
        ptr = ptr->next_;
    }

    return ptr->data_;
}

template <typename T>
UnqPtr<LinkedList<T>> LinkedList<T>::getSubList(int start_index, int end_index) const {
    if ((start_index < 0) || (start_index >= length_) || (end_index < 0) || (end_index >= length_))
        throw std::out_of_range("Index out of range\n");

    if (start_index > end_index)
        throw std::out_of_range("Start index is more than end index\n");
    
    UnqPtr<T[]> items = UnqPtr<T[]>(new T[end_index - start_index + 1]);
    ShrdPtr<Node> ptr = head_;
    int index = 0;
    
    while(index <= end_index) {
        if (index >= start_index)
            items[index - start_index] = ptr->data;

        ptr = ptr->next_;
        index++;
    }

    UnqPtr<LinkedList<T>> sub_list = UnqPtr<LinkedList<T>>(new LinkedList<T>(items, end_index - start_index + 1));

    return sub_list;
}

template <typename T>
size_t LinkedList<T>::getLength() const noexcept {
    return length_;
}

template <typename T>
void LinkedList<T>::append(T item) noexcept {
    ShrdPtr<Node> new_node = ShrdPtr<Node>(new Node);
    new_node->data_ = item;
    new_node->next_ = ShrdPtr<Node>();

    if (length_ == 0)
        head_ = new_node;
    else
        tail_->next_ = new_node;

    tail_ = new_node;
    length_++;
}

template <typename T>
void LinkedList<T>::prepend(T item) noexcept {
    ShrdPtr<Node> new_node = ShrdPtr<Node>(new Node);
    new_node->data_ = item;

    if (length_ == 0) {
        new_node->next_ = ShrdPtr<Node>();
        tail_ = new_node;
    } else
        new_node->next_ = head_;

    head_ = new_node;
    length_++;
}

template <typename T>
void LinkedList<T>::insertAt(T item, int index) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    ShrdPtr<Node> new_node = ShrdPtr<Node>(new Node);
    new_node->data_ = item;

    if (index == 0) {
        new_node->next_ = head_;
        head_ = new_node;
    } else {
        int count = 0;
        ShrdPtr<Node> ptr = head_;

        while(count < index - 1) {
            ptr = ptr->next_;
            count++;
        }

        ShrdPtr<Node> ptr_next = ptr->next_;
        new_node->next_ = ptr_next;
        ptr->next_ = new_node;
    }

    length_++;
}

template <typename T>
void LinkedList<T>::deleteElement(int index) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");

    if (length_ == 1) {
        head_.reset(nullptr);
        tail_.reset(nullptr);
    } else if (index == 0) {
        ShrdPtr<Node> ptr = head_;
        head_ = head_->next_;
    } else if (index == length_ - 1) {
        ShrdPtr<Node> ptr = head_;

        while (ptr->next_ != tail_) {
            ptr = ptr->next_;
        }
        
        tail_ = ptr;
        tail_->next_ = ShrdPtr<Node>(nullptr);
    } else {
        ShrdPtr<Node> ptr = head_;

        for (int i = 0; i < index - 1; i++) {
            ptr = ptr->next_;
        }

        ShrdPtr<Node> ptr_del = ptr->next_;
        ptr->next_ = ptr_del->next_;
    }
    length_--;
}

template <typename T>
void LinkedList<T>::set(int index, T value) {
    if ((index < 0) || (index >= length_))
        throw std::out_of_range("Index is out of range\n");
    
    ShrdPtr<Node> ptr = head_;

    for (int i = 0; i < index; i++) {
        ptr = ptr->next_;
    }

    ptr->data_ = value;
}


#endif