#include <iostream>
#include "test_shrd_ptr_mm.h"

int main() {
    std::cout << "== Testing functions of the ShrdPtrMM class (specification for single objects) ==\n";
    TestShrdPtrMM_SingleObject test_shrd_ptr_mm_single_object;

    test_shrd_ptr_mm_single_object.testAllFunctions();

    if (test_shrd_ptr_mm_single_object.isCorrect()) std::cout << "All functions of the ShrdPtrMM class (specification for single objects) class were successfully PASSED\n\n\n";
    else std::cout << "ERROR! Not all functions of the ShrdPtrMM class (specification for single objects) class were successfully passed\n\n\n";



    std::cout << "== Testing functions of the ShrdPtrMM class (specification for arrays) ==\n";
    TestShrdPtrMM_Array test_shrd_ptr_mm_array;

    test_shrd_ptr_mm_array.testAllFunctions();

    if (test_shrd_ptr_mm_array.isCorrect()) std::cout << "All functions of the ShrdPtrMM class (specification for arrays) class were successfully PASSED\n\n\n\n\n";
    else std::cout << "ERROR! Not all functions of the ShrdPtrMM class (specification for arrays) class were successfully passed\n\n\n\n\n";

    return 0;
}