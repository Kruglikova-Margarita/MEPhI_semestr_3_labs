#include <iostream>
#include <ctime>
#include "sorters.h"
#include "../Sequence/sequence.h"
#include "../SmartPtrs/shrd_ptr.h"
#include "concept_total_ordering.h"

#ifndef LAB_3SEM_2_MEASURE_SORT_H
#define LAB_3SEM_2_MEASURE_SORT_H

template <TotalOrdering T>
class MeasureSorts {
public:
    MeasureSorts() = default;

    double getTimeSort(ShrdPtr<ISorter<T>> sorter, ShrdPtr<Sequence<T>> sequence) const noexcept;
};



template <TotalOrdering T>
double MeasureSorts<T>::getTimeSort(ShrdPtr<ISorter<T>> sorter, ShrdPtr<Sequence<T>> sequence) const noexcept {
    clock_t time_start = clock();
    ShrdPtr<Sequence<T>> sorted_sequence = sorter->sort(sequence);
    clock_t time_end = clock();

    double time = (double)(time_end - time_start) / CLOCKS_PER_SEC;

    return time;
}

#endif //LAB_3SEM_2_MEASURE_SORT_H
