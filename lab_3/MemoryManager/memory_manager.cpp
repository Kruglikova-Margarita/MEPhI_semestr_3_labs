#include "memory_manager.h"

MemoryManager::MemoryManager(size_t size) noexcept: size_(size), free_memory_(new BTree<size_t, ShrdPtr<Sequence<size_t>>>(2, size, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{0}), 1)))), allocated_memory_(new BTree<size_t, size_t>(2)) {
    memory_ = (char*)calloc(size, sizeof(char));
}

MemoryManager::MemoryManager(MemoryManager& manager) noexcept : size_(manager.size_), memory_(manager.memory_), free_memory_(manager.free_memory_), allocated_memory_(manager.allocated_memory_) {}

MemoryManager::~MemoryManager() noexcept {
    free(memory_);
    delete free_memory_;
    delete allocated_memory_;
}

size_t MemoryManager::getSize() const noexcept {
    return size_;
}

ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> MemoryManager::getListOfFreeMemory() const noexcept {
    return free_memory_->traversalRootChildren();
}

ShrdPtr<Sequence<Pair<size_t, size_t>>> MemoryManager::getListOfAllocatedMemory() const noexcept {
    return allocated_memory_->traversalIncreasingOrder();
}

size_t MemoryManager::getAmountOfAllocatedMemory() const noexcept {
    ShrdPtr<Sequence<Pair<size_t, size_t>>> list_of_alloc_memory = allocated_memory_->traversalIncreasingOrder();
    int num_allocs = list_of_alloc_memory->getLength();

    size_t alloc_amount = 0;
    Pair<size_t, size_t> alloc;

    for (int i = 0; i < num_allocs; i++) {
        alloc = list_of_alloc_memory->get(i);
        alloc_amount += alloc.getValue();
    }

    return alloc_amount;
}

void* MemoryManager::operator_new_general(size_t size) {
    Pair<size_t, ShrdPtr<Sequence<size_t>>> min_superior_size;

    try {
        min_superior_size = free_memory_->getMinSuperiorKey(size);
    } catch(...) {
        throw std::out_of_range("There is not enough free space of this size\n");
    }

    ShrdPtr<Sequence<size_t>> indexes_of_spaces = min_superior_size.getValue();
    size_t index_alloc = indexes_of_spaces->getFirst();

    if (indexes_of_spaces->getLength() == 1)
        free_memory_->deleteByKey(min_superior_size.getKey());
    else
        indexes_of_spaces->deleteElement(0);

    if (size != min_superior_size.getKey()) {
        try {
            free_memory_->append(min_superior_size.getKey() - size, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{index_alloc + size}), 1)));
        } catch (...) {
            ShrdPtr<Sequence<size_t>> indexes_of_remain_size = free_memory_->searchByKey(min_superior_size.getKey() - size);
            indexes_of_remain_size->append(index_alloc + size);
        }
    }

    allocated_memory_->append(index_alloc, size);

    return memory_ + index_alloc;
}

void* operator new(size_t size, ShrdPtr<MemoryManager> memory_manager) {
    return memory_manager->operator_new_general(size);
}

void* operator new[] (size_t size, ShrdPtr<MemoryManager> memory_manager) {
    return memory_manager->operator_new_general(size);
}

void MemoryManager::delete_index(ShrdPtr<Sequence<size_t>> indexes, size_t size, size_t deleted_index) noexcept {
    if (indexes->getLength() == 1)
        free_memory_->deleteByKey(size);
    else {
        int index = 0;

        while (indexes->get(index) != deleted_index) {
            index++;
        }

        indexes->deleteElement(index);
    }
}

void operator delete(void* ptr, ShrdPtr<MemoryManager> memory_manager) noexcept {
    if (ptr != nullptr) {
        size_t index_delete = (char *) ptr - memory_manager->memory_;
        size_t size = memory_manager->allocated_memory_->searchByKey(index_delete);

        memory_manager->allocated_memory_->deleteByKey(index_delete);

        size_t index_free_prev = 0;

        try {
            Pair<size_t, size_t> prev_alloc = memory_manager->allocated_memory_->getMaxInferiorKey(index_delete);
            index_free_prev = prev_alloc.getKey() + prev_alloc.getValue();
        } catch (...) {}

        if (index_free_prev != index_delete) {
            size_t free_size_prev = index_delete - index_free_prev;
            ShrdPtr<Sequence<size_t>> free_size_prev_ind = memory_manager->free_memory_->searchByKey(free_size_prev);

            memory_manager->delete_index(free_size_prev_ind, free_size_prev, index_free_prev);
        }

        size_t index_end_free_space = index_delete + size;

        try {
            Pair<size_t, size_t> index_next_alloc = memory_manager->allocated_memory_->getMinSuperiorKey(
                    index_end_free_space);
            if (index_next_alloc.getKey() != index_end_free_space) {
                size_t free_size_next = index_next_alloc.getKey() - index_end_free_space;
                ShrdPtr<Sequence<size_t>> free_size_next_ind = memory_manager->free_memory_->searchByKey(
                        free_size_next);

                memory_manager->delete_index(free_size_next_ind, free_size_next, index_end_free_space);

                index_end_free_space = index_next_alloc.getKey();
            }
        } catch (...) {
            size_t free_space_after = memory_manager->size_ - index_end_free_space;
            ShrdPtr<Sequence<size_t>> free_space_after_ind = memory_manager->free_memory_->searchByKey(
                    free_space_after);

            memory_manager->delete_index(free_space_after_ind, free_space_after, index_end_free_space);

            index_end_free_space = memory_manager->size_;
        }

        try {
            memory_manager->free_memory_->append(index_end_free_space - index_free_prev, ShrdPtr<Sequence<size_t>>(
                    new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{index_free_prev}), 1)));
        } catch (...) {
            ShrdPtr<Sequence<size_t>> indexes = memory_manager->free_memory_->searchByKey(
                    index_end_free_space - index_free_prev);
            indexes->append(index_free_prev);
        }
    }
}
