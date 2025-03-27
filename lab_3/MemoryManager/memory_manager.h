#ifndef LAB_3SEM_3_MEMORY_MANAGER_H
#define LAB_3SEM_3_MEMORY_MANAGER_H

#include "b_tree.h"
#include "pair.h"

class MemoryManager {
private:
    size_t size_;
    char* memory_;
    BTree<size_t, ShrdPtr<Sequence<size_t>>>* free_memory_;
    BTree<size_t, size_t>* allocated_memory_;

    void *operator_new_general(size_t size);
    void delete_index(ShrdPtr<Sequence<size_t>> indexes, size_t size, size_t deleted_index) noexcept;

    friend void *operator new(size_t size, ShrdPtr<MemoryManager> memory_manager);
    friend void *operator new[](size_t size, ShrdPtr<MemoryManager> memory_manager);
    friend void operator delete(void* ptr, ShrdPtr<MemoryManager> memory_manager) noexcept;

public:
    explicit MemoryManager(size_t size) noexcept;
    MemoryManager(MemoryManager& manager) noexcept;

    ~MemoryManager() noexcept;

    size_t getSize() const noexcept;

    [[nodiscard]] ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> getListOfFreeMemory() const noexcept;
    [[nodiscard]] ShrdPtr<Sequence<Pair<size_t, size_t>>> getListOfAllocatedMemory() const noexcept;

    size_t getAmountOfAllocatedMemory() const noexcept;
};



void* operator new(size_t size, ShrdPtr<MemoryManager> memory_manager);

void* operator new[] (size_t size, ShrdPtr<MemoryManager> memory_manager);

void operator delete(void* ptr, ShrdPtr<MemoryManager> memory_manager) noexcept;

#endif //LAB_3SEM_3_MEMORY_MANAGER_H
