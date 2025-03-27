#include <iostream>
#include <fstream>
#include "../../Sorters/sorters.h"
#include "../../Sorters/measure_sort.h"
#include "../../Sequence/sequence.h"
#include "../../SmartPtrs/shrd_ptr.h"

using namespace std;

int cmp_fun(int a, int b);

int main() {
    ofstream file;
    file.open("/home/margo/Documents/Labs_3sem/Lab_3sem_2/SortingTime.ods");
    file << "Amount\t" << "Bubble\t" << "Shaker\t" << "Insertion\t" << "BinaryInsertion\t" << "Selection\t" << "Merge\t" << "Shell\t" << "Quick\n";

    int length = 100000;

    Sequence<int>* ptr_sequence = new ArraySequence<int>;
    ShrdPtr<Sequence<int>> sequence(ptr_sequence);

    srand(time(nullptr));
    int number;

    ISorter<int>* ptr_bubble_sorter = new BubbleSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> bubble_sorter(ptr_bubble_sorter);

    ISorter<int>* ptr_shaker_sorter = new ShakerSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> shaker_sorter(ptr_shaker_sorter);

    ISorter<int>* ptr_insertion_sorter = new InsertionSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> insertion_sorter(ptr_insertion_sorter);

    ISorter<int>* ptr_binary_insertion_sorter = new BinaryInsertionSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> binary_insertion_sorter(ptr_binary_insertion_sorter);

    ISorter<int>* ptr_selection_sorter = new SelectionSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> selection_sorter(ptr_selection_sorter);

    ISorter<int>* ptr_merge_sorter = new MergeSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> merge_sorter(ptr_merge_sorter);

    ISorter<int>* ptr_shell_sorter = new ShellSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> shell_sorter(ptr_shell_sorter);

    ISorter<int>* ptr_quick_sorter = new QuickSort<int>(cmp_fun);
    ShrdPtr<ISorter<int>> quick_sorter(ptr_quick_sorter);

    double time_bubble, time_shaker, time_insertion, time_binary_insertion, time_selection, time_merge, time_shell, time_quick;

    MeasureSorts<int> measure_sorts;

    for (int i = 1; i <= length; i++) {
        if (i % 25000 == 0)
            cout << "Amount = " << i << "\n";

        number = rand();
        sequence->append(number);

        //if (i % 10000 == 0) {
        if (((i <= 5000) && (i % 500 == 0)) || ((i >= 6000) && (i <= 20000) && (i % 2000 == 0)) || ((i >= 40000) && (i % 20000 == 0))) {
            file << i << "\t";


            time_bubble = measure_sorts.getTimeSort(bubble_sorter, sequence);
            file << time_bubble << "\t";

            time_shaker = measure_sorts.getTimeSort(shaker_sorter, sequence);
            file << time_shaker << "\t";

            time_insertion = measure_sorts.getTimeSort(insertion_sorter, sequence);
            file << time_insertion << "\t";

            time_binary_insertion = measure_sorts.getTimeSort(binary_insertion_sorter, sequence);
            file << time_binary_insertion << "\t";

            time_selection = measure_sorts.getTimeSort(selection_sorter, sequence);
            file << time_selection << "\t";

            time_merge = measure_sorts.getTimeSort(merge_sorter, sequence);
            file << time_merge << "\t";

            time_shell = measure_sorts.getTimeSort(shell_sorter, sequence);
            file << time_shell << "\t";

            time_quick = measure_sorts.getTimeSort(quick_sorter, sequence);
            file << time_quick << "\n";
        }

    }

    file.close();

    return 0;
}


int cmp_fun(int a, int b) {
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    return 0;
}
