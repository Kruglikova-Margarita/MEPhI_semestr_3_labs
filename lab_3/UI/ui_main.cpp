#include <iostream>
#include <string>
#include "../MemoryManager/memory_manager.h"
#include "printer.h"
#include "tuple.h"
#include "Input/input.h"
#include "Menu/menu.h"
#include "Actions/actions.h"

int main() {
    std::cout << "\nInput size of memory manager: ";
    size_t size = inputNatural();
    std::cout << "\n";
    ShrdPtr<MemoryManager> memory_manager(new MemoryManager(size));
    ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects(new ArraySequence<Tuple<std::string, size_t, void*>>());

    Printer printer;

    printMenu();

    int action = inputAction();

    while (action != -1) {
        switch (action) {
            case 1:
                try {
                    action1(objects, memory_manager);
                    printer.printMemoryInfo(objects, memory_manager);
                } catch (std::out_of_range& e) {
                    printf("\033[1;31m\n%s\033[0m\n", e.what());
                }

                break;

            case 2:
                try {
                    action2(objects, memory_manager);
                    printer.printMemoryInfo(objects, memory_manager);
                } catch (std::out_of_range& e) {
                    printf("\033[1;31m\n%s\033[0m\n", e.what());
                }

                break;
        }

        action = inputAction();
    }

    size_t amount_alloc = memory_manager->getAmountOfAllocatedMemory();

    if (amount_alloc == 0)
        printf("\033[1;32m\nNo memory leaks\033[0m\n");
    else
        printf("\033[1;31m\nMemory leaks: %ld bytes\033[0m\n", memory_manager->getAmountOfAllocatedMemory());

    return 0;
}