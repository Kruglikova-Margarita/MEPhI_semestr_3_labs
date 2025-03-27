#include <iostream>
#include "../Sequence/sequence.h"
#include "../SmartPtrs/shrd_ptr.h"
#include "../Sorters/sorters.h"
#include "../Sorters/measure_sort.h"
#include "Input/input.h"
#include "printer.h"
#include "Menu/menu.h"
#include "actions.h"

using namespace std;

int cmp_fun(float a, float b) {
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    return 0;
}

int main() {
    ShrdPtr<Sequence<float>> sequence = createSequence();

    cout << "\nCreated sequence:\n";
    printSequence(sequence);

    printMenuOfActions();

    int action = inputAction();

    ISorter<float>* ptr_sorter;
    ShrdPtr<ISorter<float>> sorter;

    while (action != -1) {
        switch (action) {
            case 1:
                ptr_sorter = new BubbleSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 2:
                ptr_sorter = new ShakerSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 3:
                ptr_sorter = new InsertionSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 4:
                ptr_sorter = new BinaryInsertionSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 5:
                ptr_sorter = new SelectionSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 6:
                ptr_sorter = new MergeSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 7:
                ptr_sorter = new ShellSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 8:
                ptr_sorter = new QuickSort<float>(cmp_fun);
                sorter = ShrdPtr<ISorter<float>>(ptr_sorter);
                actionSort(sorter, sequence);

                break;

            case 9:
                actionAppend(sequence);

                break;

            case 10:
                sequence = createSequence();

                break;

            case 0:
                printMenuOfActions();

                break;

        }

        action = inputAction();
    }

    return 0;
}
