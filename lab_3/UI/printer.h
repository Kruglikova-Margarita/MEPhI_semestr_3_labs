#ifndef LAB_3SEM_3_PRINTER_H
#define LAB_3SEM_3_PRINTER_H

#include <stdio.h>
#include <iomanip>
#include "../MemoryManager//memory_manager.h"
#include "../SmartPtrs/shrd_ptr.h"
#include "tuple.h"

class Printer {
public:
    Printer() = default;

    template <typename T1, typename T2>
    static void printPair(Pair<T1, T2>& pair) noexcept;

    template <typename T1, typename T2>
    static void printPairWithSequenceValue(Pair<T1, ShrdPtr<Sequence<T2>>>& pair) noexcept;

    template<typename T>
    static void printSequence(ShrdPtr<Sequence<T>> sequence) noexcept;

    template <typename T1, typename T2>
    static void printSequenceOfPairs(ShrdPtr<Sequence<Pair<T1, T2>>> sequence) noexcept;

    template <typename T1, typename T2>
    static void printSequenceOfPairsWithSequenceValue(ShrdPtr<Sequence<Pair<T1, ShrdPtr<Sequence<T2>>>>> sequence) noexcept;

    static void printMemoryState(ShrdPtr<MemoryManager> memory_manager) noexcept;

    static void printTable(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects) noexcept;

    static void printMemoryInfo(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects, ShrdPtr<MemoryManager> memory_manager) noexcept;
};




template <typename T1, typename T2>
void Printer::printPair(Pair<T1, T2>& pair) noexcept {
    std::cout << "(" << pair.getKey() << "; " << pair.getValue() << ")";
}

template <typename T1, typename T2>
void Printer::printPairWithSequenceValue(Pair<T1, ShrdPtr<Sequence<T2>>>& pair) noexcept {
    std::cout << "(" << pair.getKey() << "; ";
    printSequence(pair.getValue());
    std::cout << ")";
}

template<typename T>
void Printer::printSequence(ShrdPtr<Sequence<T>> sequence) noexcept {
    int len = sequence->getLength();

    if (len == 0)
        std::cout << "Sequence is empty\n";
    else {
        std::cout << "{";
        for (int i = 0; i < len - 1; i++) {
            std::cout << sequence->get(i) << "; ";
        }
        std::cout << sequence->get(len - 1) << "}";
    }
}

template <typename T1, typename T2>
void Printer::printSequenceOfPairs(ShrdPtr<Sequence<Pair<T1, T2>>> sequence) noexcept {
    int len = sequence->getLength();

    if (len == 0)
        std::cout << "Sequence is empty\n";
    else {
        std::cout << "{";
        for (int i = 0; i < len - 1; i++) {
            printPair(sequence->get(i));
            std::cout << "; ";
        }
        printPair(sequence->get(len - 1));
        std::cout << "}";
    }
}

template <typename T1, typename T2>
void Printer::printSequenceOfPairsWithSequenceValue(ShrdPtr<Sequence<Pair<T1, ShrdPtr<Sequence<T2>>>>> sequence) noexcept {
    int len = sequence->getLength();

    if (len == 0)
        std::cout << "Sequence is empty\n";
    else {
        std::cout << "{";
        for (int i = 0; i < len - 1; i++) {
            printPairWithSequenceValue(sequence->get(i));
            std::cout << "; ";
        }
        printPairWithSequenceValue(sequence->get(len - 1));
        std::cout << "}";
    }
}

void Printer::printMemoryState(ShrdPtr<MemoryManager> memory_manager) noexcept {
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory = memory_manager->getListOfAllocatedMemory();
    int num_of_allocs = alloc_memory->getLength();
    float size = memory_manager->getSize();
    float coef = 1;

    if (size > 100)
        coef = 100 / size;

    std::cout << "     ";

    if (num_of_allocs > 0) {
        for (int i = 0; i < num_of_allocs; i++) {
            Pair<size_t, size_t> alloc = alloc_memory->get(i);

            if ((i == 0) && (alloc.getKey() != 0)) {
                for (int j = 0; j < alloc.getKey(); j++) {
                    printf("\033[1;32m|\033[0m");
                }
            }

            for (int j = 0; j < alloc.getValue() * coef; j++) {
                printf("\033[1;31m|\033[0m");
            }

            int next_alloc_index;

            if (i < num_of_allocs - 1) {
                Pair<size_t, size_t> next_alloc = alloc_memory->get(i + 1);
                next_alloc_index = next_alloc.getKey();
            } else
                next_alloc_index = size;

            for (int j = 0; j < (next_alloc_index - (alloc.getKey() + alloc.getValue())) * coef; j++) {
                printf("\033[1;32m|\033[0m");
            }
        }
    } else {
        for (int i = 0; i < size * coef; i++) {
            printf("\033[1;32m|\033[0m");
        }
    }

    std::cout << "  \n";
}

void Printer::printTable(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects) noexcept {
    int num_objects = objects->getLength();

    printf("\033[1;96m\n%*s\t\033[0m", 5, "N");
    printf("\033[1;96m%*s\t\033[0m", 20, "type");
    printf("\033[1;96m%*s\t\033[0m\n", 20, "size");

    if (num_objects == 0) {
        printf("%*s\t", 5, "-");
        printf("%*s\t", 20, "-");
        printf("%*s\t\n", 20, "-");
    }

    for (int i = 0; i < num_objects; i++) {
        std::string str = objects->get(i).getValue1();
        const char* type = str.c_str();

        printf("%*d\t", 5, i + 1);
        printf("%*s\t", 20, type);
        printf("%*ld\t\n", 20, objects->get(i).getValue2());
    }
}

void Printer::printMemoryInfo(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects, ShrdPtr<MemoryManager> memory_manager) noexcept {
    printf("\033[1;96m\nAllocated objects:\033[0m");
    printTable(objects);

    printf("\033[1;96m\nCurrent state of memory:\033[0m");
    printMemoryState(memory_manager);
}


#endif //LAB_3SEM_3_PRINTER_H
