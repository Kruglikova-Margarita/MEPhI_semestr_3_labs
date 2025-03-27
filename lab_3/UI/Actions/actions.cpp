#include <iostream>
#include "../Menu/menu.h"
#include "../Input/input.h"
#include "../tuple.h"
#include "../../MemoryManager//memory_manager.h"
#include "actions.h"

void action1(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects, ShrdPtr<MemoryManager> memory_manager) {
    printMenuOfTypes();
    int type = inputType();
    printMenuArrayOrNot();
    int way = inputWayArrayOrNot();

    void* ptr;
    std::string object_type;
    size_t object_size;

    switch (way) {
        case 1:
            switch (type) {
                case 1:
                    try {
                        ptr = new(memory_manager) char;
                    } catch (...) {
                        throw;
                    }

                    object_type = "char";
                    object_size = sizeof(char);
                    break;

                case 2:
                    try {
                        ptr = new(memory_manager) int;
                    } catch (...) {
                        throw;
                    }

                    object_type = "int";
                    object_size = sizeof(int);
                    break;

                case 3:
                    try {
                        ptr = new(memory_manager) double;
                    } catch (...) {
                        throw;
                    }

                    object_type = "double";
                    object_size = sizeof(double);
                    break;
            }
            break;

        case 2:
            std::cout << "Input the size of array: ";
            int size = inputNatural();
            switch (type) {
                case 1:
                    try {
                        ptr = new(memory_manager) char[size];
                    } catch (...) {
                        throw;
                    }

                    object_type = "char[" + std::to_string(size) + "]";
                    object_size = sizeof(char) * size;
                    break;

                case 2:
                    try {
                        ptr = new(memory_manager) int[size];
                    } catch (...) {
                        throw;
                    }

                    object_type = "int[" + std::to_string(size) + "]";
                    object_size = sizeof(int) * size;
                    break;

                case 3:
                    try {
                        ptr = new(memory_manager) double[size];
                    } catch (...) {
                        throw;
                    }

                    object_type = "double[" + std::to_string(size) + "]";
                    object_size = sizeof(double) * size;
                    break;
            }
            break;
    }

    objects->append(Tuple<std::string, size_t, void*>(object_type, object_size, ptr));
}

void action2(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects, ShrdPtr<MemoryManager> memory_manager) {
    if (objects->getLength() == 0)
        std::cout << "There are no allocated objects\n";
    else {
        std::cout << "Input number of deleted object: ";
        int num = inputInt();

        try {
            Tuple<std::string, size_t, void *> deleted_object = objects->get(num - 1);
            operator delete(deleted_object.getValue3(), memory_manager);
        } catch (...) {
            throw;
        }

        objects->deleteElement(num - 1);
    }
}

