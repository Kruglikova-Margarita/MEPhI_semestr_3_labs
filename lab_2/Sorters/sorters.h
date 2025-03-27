#include <iostream>
#include <concepts>
#include "../Sequence/sequence.h"
#include "../SmartPtrs/shrd_ptr.h"
#include "concept_total_ordering.h"

#ifndef LAB_3SEM_2_SORTERS_H
#define LAB_3SEM_2_SORTERS_H

template <TotalOrdering T>
class ISorter {
public:
    virtual ~ISorter() = default;

    virtual ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept = 0;
};



template <TotalOrdering T>
class BubbleSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

public:
    explicit BubbleSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};


template <TotalOrdering T>
class ShakerSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

public:
    explicit ShakerSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};


template <TotalOrdering T>
class InsertionSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

public:
    explicit InsertionSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};

template <typename T>
class BinaryInsertionSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

public:
    explicit BinaryInsertionSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};

template <TotalOrdering T>
class SelectionSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

public:
    explicit SelectionSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};

template <TotalOrdering T>
class MergeSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

    ShrdPtr<Sequence<T>> sortHalf(ShrdPtr<Sequence<T>> sequence, int index_start, int index_end) const noexcept;

public:
    explicit MergeSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};

template <TotalOrdering T>
class ShellSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

public:
    explicit ShellSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};

template <TotalOrdering T>
class QuickSort : public ISorter<T> {
private:
    int (*cmp_)(T, T);

    int partition(ShrdPtr<Sequence<T>> sequence, int index_start, int index_end) const noexcept;
    void sortPart(ShrdPtr<Sequence<T>> sequence, int index_start, int index_end) const noexcept;

public:
    explicit QuickSort(int (*fun_cmp)(T, T)) noexcept : cmp_(fun_cmp) {}

    ShrdPtr<Sequence<T>> sort(ShrdPtr<Sequence<T>> sequence) const noexcept override;
};








template <TotalOrdering T>
ShrdPtr<Sequence<T>> BubbleSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    size_t length = sequence->getLength();

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - 1; j++) {
            if (cmp_((*sorted_sequence)[j], (*sorted_sequence)[j + 1]) > 0)
                sorted_sequence->swap(j, j + 1);
        }
    }

    return sorted_sequence;
}



template <TotalOrdering T>
ShrdPtr<Sequence<T>> ShakerSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    int length = sequence->getLength();

    int left = 0;
    int right = length - 1;

    while (left < right) {
        for (size_t i = left; i < right; i++) {
            if (cmp_((*sorted_sequence)[i], (*sorted_sequence)[i + 1]) > 0)
                sorted_sequence->swap(i, i + 1);
        }

        right--;

        for (size_t i = right; i > left; i--) {
            if (cmp_((*sorted_sequence)[i], (*sorted_sequence)[i - 1]) < 0)
                sorted_sequence->swap(i, i - 1);
        }

        left++;
    }

    return sorted_sequence;
}



template <TotalOrdering T>
ShrdPtr<Sequence<T>> InsertionSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    size_t length = sequence->getLength();

    for (int i = 0; i < length; i++) {
        for (int j = i; j > 0; j--) {
            if (cmp_((*sorted_sequence)[j - 1], (*sorted_sequence)[j]) > 0)
                sorted_sequence->swap(j - 1, j);
        }
    }

    return sorted_sequence;
}



template <typename T>
ShrdPtr<Sequence<T>> BinaryInsertionSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    size_t length = sequence->getLength();

    for (int i = 1; i < length; i++) {
        T key = (*sorted_sequence)[i];
        int left = 0;
        int right = i - 1;
        int middle;

        while (left <= right) {
            middle = (left + right) / 2;
            if (cmp_(key, sorted_sequence->get(middle)) < 0)
                right = middle - 1;
            else
                left = middle + 1;
        }

        for (int j = i; j > left; j--)
            sorted_sequence->set(j, sorted_sequence->get(j - 1));

        sorted_sequence->set(left, key);
    }

    return sorted_sequence;
}



template <TotalOrdering T>
ShrdPtr<Sequence<T>> SelectionSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    int length = sequence->getLength();

    for (int i = length - 1; i > 0; i--) {
        size_t index_max = 0;

        for (size_t j = 1; j <= i; j++) {
            if (cmp_((*sorted_sequence)[index_max], (*sorted_sequence)[j]) < 0)
                index_max = j;
        }

        sorted_sequence->swap(index_max, i);
    }

    return sorted_sequence;
}



template <TotalOrdering T>
ShrdPtr<Sequence<T>> MergeSort<T>::sortHalf(ShrdPtr<Sequence<T>> sequence, int index_start, int index_end) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>;
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    if (index_end - index_start > 0) {
        ShrdPtr<Sequence<T>> half1 = sortHalf(sequence, index_start, (index_start + index_end) / 2);
        ShrdPtr<Sequence<T>> half2 = sortHalf(sequence, ((index_start + index_end) / 2) + 1, index_end);

        size_t index1 = 0;
        size_t index2 = 0;

        while ((index1 < half1->getLength()) || (index2 < half2->getLength())) {
            if ((index1 < half1->getLength()) && (index2 < half2->getLength())) {
                if (cmp_(half1->get(index1), half2->get(index2)) < 0) {
                    sorted_sequence->append(half1->get(index1));
                    index1++;
                } else {
                    sorted_sequence->append(half2->get(index2));
                    index2++;
                }
            } else if ((index1 < half1->getLength()) && (index2 >= half2->getLength())) {
                sorted_sequence->append(half1->get(index1));
                index1++;
            } else {
                sorted_sequence->append(half2->get(index2));
                index2++;
            }
        }
    } else if (index_end - index_start == 0)
        sorted_sequence->append(sequence->get(index_start));

    return sorted_sequence;
}

template <TotalOrdering T>
ShrdPtr<Sequence<T>> MergeSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    ShrdPtr<Sequence<T>> sorted_sequence = sortHalf(sequence, 0, sequence->getLength() - 1);

    return sorted_sequence;
}



template <TotalOrdering T>
ShrdPtr<Sequence<T>> ShellSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    int length = sequence->getLength();

    for (int step = length / 2; step > 0; step /= 2) {
        for (int i = step; i < length; i += step) {
            for (int j = i; j > 0; j -= step) {
                if (cmp_(sorted_sequence->get(j - 1), sorted_sequence->get(j)) > 0)
                    sorted_sequence->swap(j - 1, j);
            }
        }
    }

    return sorted_sequence;
}



template <TotalOrdering T>
int QuickSort<T>::partition(ShrdPtr<Sequence<T>> sequence, int index_start, int index_end) const noexcept {
    srand(time(nullptr));
    int index_pivot = rand() % (index_end - index_start + 1) + index_start;
    T pivot = sequence->get(index_pivot);

    int index_partition = index_start;

    for (int i = index_start; i <= index_end; i++) {
        if (cmp_(sequence->get(i), pivot) < 0) {
            sequence->swap(i, index_partition);

            if (index_pivot == index_partition)
                index_pivot = i;

            index_partition++;
        }
    }

    sequence->swap(index_partition, index_pivot);

    return index_partition;
}

template <TotalOrdering T>
void QuickSort<T>::sortPart(ShrdPtr<Sequence<T>> sequence, int index_start, int index_end) const noexcept {
    if (index_end - index_start <= 0)
        return;
    else {
        int index_partition = partition(sequence, index_start, index_end);
        sortPart(sequence, index_start, index_partition - 1);
        sortPart(sequence, index_partition + 1, index_end);
    }
}

template <TotalOrdering T>
ShrdPtr<Sequence<T>> QuickSort<T>::sort(ShrdPtr<Sequence<T>> sequence) const noexcept {
    Sequence<T>* ptr_sorted_sequence = new ArraySequence<T>(*sequence);
    ShrdPtr<Sequence<T>> sorted_sequence(ptr_sorted_sequence);

    int length = sequence->getLength();

    sortPart(sorted_sequence, 0, length - 1);

    return sorted_sequence;
}

#endif //LAB_3SEM_2_SORTERS_H
