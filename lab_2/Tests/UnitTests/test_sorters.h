#include "../../Sorters/sorters.h"
#include "../../SmartPtrs/shrd_ptr.h"
#include "../../Sequence/sequence.h"

#ifndef LAB_3SEM_2_TEST_SORTERS_H
#define LAB_3SEM_2_TEST_SORTERS_H

using namespace std;

int cmp_fun(int a, int b) {
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    return 0;
}

class TestSorters {
private:
    ShrdPtr<Sequence<int>> random_sequence_;
    ShrdPtr<Sequence<int>> sorted_sequence_;
    ShrdPtr<Sequence<int>> reverse_sorted_sequence_;
    ShrdPtr<Sequence<int>> empty_sequence_;
    int (*cmp_)(int, int);
    bool is_correct_;

    bool testSorter(ShrdPtr<ISorter<int>> sorter) const noexcept;

public:
    TestSorters() noexcept;

    bool isCorrect() const noexcept;

    void testBubbleSort() noexcept;
    void testShakerSort() noexcept;
    void testInsertionSort() noexcept;
    void testBinaryInsertionSort() noexcept;
    void testSelectionSort() noexcept;
    void testMergeSort() noexcept;
    void testShellSort() noexcept;
    void testQuickSort() noexcept;
};

TestSorters::TestSorters() noexcept : is_correct_(true), cmp_(cmp_fun) {
    int* array = new int[10]{-1, 5, 0, -4, 10, 3, 1, 7, 3, 8};
    Sequence<int>* ptr_random_sequence = new ArraySequence(array, 10);
    random_sequence_ = ShrdPtr<Sequence<int>>(ptr_random_sequence);
    delete[] array;

    array = new int[10]{-4, -1, 0, 1, 3, 3, 5, 7, 8, 10};
    Sequence<int>* ptr_sorted_sequence = new ArraySequence(array, 10);
    sorted_sequence_ = ShrdPtr<Sequence<int>>(ptr_sorted_sequence);
    delete[] array;

    array = new int[10]{10, 8, 7, 5, 3, 3, 1, 0, -1, -4};
    Sequence<int>* ptr_reverse_sorted_sequence = new ArraySequence(array, 10);
    reverse_sorted_sequence_ = ShrdPtr<Sequence<int>>(ptr_reverse_sorted_sequence);
    delete[] array;

    Sequence<int>* ptr_empty_sequence = new ArraySequence<int>;
    empty_sequence_ = ShrdPtr<Sequence<int>>(ptr_empty_sequence);
}

bool TestSorters::isCorrect() const noexcept {
    return is_correct_;
}

bool TestSorters::testSorter(ShrdPtr<ISorter<int>> sorter) const noexcept {
    ShrdPtr<Sequence<int>> check1 = sorter->sort(random_sequence_);
    ShrdPtr<Sequence<int>> check2 = sorter->sort(sorted_sequence_);
    ShrdPtr<Sequence<int>> check3 = sorter->sort(reverse_sorted_sequence_);
    ShrdPtr<Sequence<int>> check4 = sorter->sort(empty_sequence_);

    return ((*check1 == *sorted_sequence_) && (*check2 == *sorted_sequence_) && (*check3 == *sorted_sequence_) && (*check4 == *empty_sequence_));
}

void TestSorters::testBubbleSort() noexcept {
    ISorter<int>* ptr_sorter = new BubbleSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "BubbleSort          : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testShakerSort() noexcept {
    ISorter<int>* ptr_sorter = new ShakerSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "ShakerSort          : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testInsertionSort() noexcept {
    ISorter<int>* ptr_sorter = new InsertionSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "InsertionSort       : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testBinaryInsertionSort()  noexcept {
    ISorter<int>* ptr_sorter = new BinaryInsertionSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "BinaryInsertionSort : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testSelectionSort() noexcept {
    ISorter<int>* ptr_sorter = new SelectionSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "SelectionSort       : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testMergeSort() noexcept {
    ISorter<int>* ptr_sorter = new MergeSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "MergeSort           : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testShellSort() noexcept {
    ISorter<int>* ptr_sorter = new ShellSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "ShellSort           : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}

void TestSorters::testQuickSort() noexcept {
    ISorter<int>* ptr_sorter = new QuickSort<int>(cmp_);
    ShrdPtr<ISorter<int>> sorter(ptr_sorter);

    bool check_correct = testSorter(sorter);

    cout << "QuickSort           : ";
    if (check_correct)
        cout << "passed\n";
    else {
        cout << "failed\n";
        is_correct_ = false;
    }
}


#endif //LAB_3SEM_2_TEST_SORTERS_H
