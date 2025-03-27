#include <iostream>
#include "test_sorters.h"
#include "../../UI/printer.h"

using namespace std;

int main() {
    cout << "\n== Testing sort classes ==\n\n";

    TestSorters test_sorters;

    test_sorters.testBubbleSort();
    test_sorters.testShakerSort();
    test_sorters.testInsertionSort();
    test_sorters.testBinaryInsertionSort();
    test_sorters.testSelectionSort();
    test_sorters.testMergeSort();
    test_sorters.testShellSort();
    test_sorters.testQuickSort();

    if (test_sorters.isCorrect())
        cout << "\nAll sorters work CORRECT\n\n";
    else
        cout << "\nERROR! Not all sorters work correct\n\n";

    return 0;
}
