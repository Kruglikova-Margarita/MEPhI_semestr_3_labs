#include <iostream>
#include "../Sorters/measure_sort.h"
#include "printer.h"
#include "../Sorters/sorters.h"
#include "../Sequence/sequence.h"
#include "../SmartPtrs/shrd_ptr.h"
#include "../Sorters/concept_total_ordering.h"
#include "Input/input.h"

using namespace std;

#ifndef LAB_3SEM_2_ACTIONS_H
#define LAB_3SEM_2_ACTIONS_H

template <TotalOrdering T>
void actionSort(ShrdPtr<ISorter<T>> sorter, ShrdPtr<Sequence<T>> sequence) {
    ShrdPtr<Sequence<float>> sorted_sequence = sorter->sort(sequence);
    cout << "Sorted sequence:\n";
    printSequence(sorted_sequence);

    MeasureSorts<T> measure_sorts;
    double time = measure_sorts.getTimeSort(sorter, sequence);
    cout << "The sorting time is " << time << " s\n";
}

template <TotalOrdering T>
void actionAppend(ShrdPtr<Sequence<T>> sequence) {
    cout << "Input number to append: ";
    float new_number = inputFloat();
    sequence->append(new_number);

    cout << "Updated sequence:\n";
    printSequence(sequence);
}

#endif //LAB_3SEM_2_ACTIONS_H
