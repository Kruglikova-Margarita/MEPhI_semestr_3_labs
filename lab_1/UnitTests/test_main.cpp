#include <iostream>
#include "test_unq_ptr.h"
#include "test_shrd_ptr.h"
#include "test_array_sequence.h"
#include "test_linked_list_sequence.h"

using namespace std;

int main() {
    
    cout << "\n== Testing functions of the UnqPtr class (specification for single objects) ==\n";
    TestUnqPtr_SingleObject test_unq_ptr_single_object;

    test_unq_ptr_single_object.testGet();
    test_unq_ptr_single_object.testRelease();
    test_unq_ptr_single_object.testReset();
    test_unq_ptr_single_object.testSwap();
    test_unq_ptr_single_object.testOperatorAssignment();
    test_unq_ptr_single_object.testOperatorBool();
    test_unq_ptr_single_object.testOperatorDereference();
    test_unq_ptr_single_object.testOperatorAccess();
    test_unq_ptr_single_object.testOperatorCompare();

    if (test_unq_ptr_single_object.isCorrect()) cout << "All functions of the UnqPtr class (specification for single objects) class were successfully PASSED\n\n\n";
    else cout << "ERROR! Not all functions of the UnqPtr class (specification for single objects) class were successfully passed\n\n\n";



    cout << "== Testing functions of the UnqPtr class (specification for arrays) ==\n";
    TestUnqPtr_Array test_unq_ptr_array;

    test_unq_ptr_array.testGet();
    test_unq_ptr_array.testRelease();
    test_unq_ptr_array.testReset();
    test_unq_ptr_array.testSwap();
    test_unq_ptr_array.testOperatorAssignment();
    test_unq_ptr_array.testOperatorBool();
    test_unq_ptr_array.testOperatorGetElement();
    test_unq_ptr_array.testOperatorCompare();

    if (test_unq_ptr_array.isCorrect()) cout << "All functions of the UnqPtr class (specification for arrays) class were successfully PASSED\n\n\n\n\n";
    else cout << "ERROR! Not all functions of the UnqPtr class (specification for arrays) class were successfully passed\n\n\n\n\n";



    cout << "== Testing functions of the ShrdPtr class (specification for single objects) ==\n";
    TestShrdPtr_SingleObject test_shrd_ptr_single_object;

    test_shrd_ptr_single_object.testGet();
    test_shrd_ptr_single_object.testReset();
    test_shrd_ptr_single_object.testSwap();
    test_shrd_ptr_single_object.testUnique();
    test_shrd_ptr_single_object.testUseCount();
    test_shrd_ptr_single_object.testOperatorBool();
    test_shrd_ptr_single_object.testOperatorAssignment();
    test_shrd_ptr_single_object.testOperatorDereference();
    test_shrd_ptr_single_object.testOperatorAccess();
    test_shrd_ptr_single_object.testOperatorCompare();

    if (test_shrd_ptr_single_object.isCorrect()) cout << "All functions of the ShrdPtr class (specification for single objects) class were successfully PASSED\n\n\n";
    else cout << "ERROR! Not all functions of the ShrdPtr class (specification for single objects) class were successfully passed\n\n\n";



    cout << "== Testing functions of the ShrdPtr class (specification for arrays) ==\n";
    TestShrdPtr_Array test_shrd_ptr_array;

    test_shrd_ptr_array.testGet();
    test_shrd_ptr_array.testReset();
    test_shrd_ptr_array.testSwap();
    test_shrd_ptr_array.testUnique();
    test_shrd_ptr_array.testUseCount();
    test_shrd_ptr_array.testOperatorBool();
    test_shrd_ptr_array.testOperatorAssignment();
    test_shrd_ptr_array.testOperatorGetElement();
    test_shrd_ptr_array.testOperatorCompare();

    if (test_shrd_ptr_array.isCorrect()) cout << "All functions of the ShrdPtr class (specification for arrays) class were successfully PASSED\n\n\n\n\n";
    else cout << "ERROR! Not all functions of the ShrdPtr class (specification for arrays) class were successfully passed\n\n\n\n\n";    



    cout << "== Testing functions of the ArraySequence class ==\n";
    TestArraySequence test_array_sequence;

    test_array_sequence.testGetFirst();
    test_array_sequence.testGetLast();
    test_array_sequence.testGet();
    test_array_sequence.testGetSubSequence();
    test_array_sequence.testGetLength();
    test_array_sequence.testAppend();
    test_array_sequence.testPrepend();
    test_array_sequence.testInsertAt();
    test_array_sequence.testDeleteElement();
    test_array_sequence.testSet();
    test_array_sequence.testConcat();
    test_array_sequence.testOperatorGet();
    test_array_sequence.testOperatorConcat();
    test_array_sequence.testOperatorCompare();
    test_array_sequence.testMap();
    test_array_sequence.testWhere();
    test_array_sequence.testReduce();

    if (test_array_sequence.isCorrect()) cout << "All functions of the ArraySequence class were successfully PASSED\n\n\n";
    else cout << "ERROR! Not all functions of the ArraySequence class were successfully passed\n\n\n";



    cout << "== Testing functions of the LinkedListSequence class ==\n";
    TestLinkedListSequence test_linked_list_sequence;

    test_linked_list_sequence.testGetFirst();
    test_linked_list_sequence.testGetLast();
    test_linked_list_sequence.testGet();
    test_linked_list_sequence.testGetSubSequence();
    test_linked_list_sequence.testGetLength();
    test_linked_list_sequence.testAppend();
    test_linked_list_sequence.testPrepend();
    test_linked_list_sequence.testInsertAt();
    test_linked_list_sequence.testDeleteElement();
    test_linked_list_sequence.testSet();
    test_linked_list_sequence.testConcat();
    test_linked_list_sequence.testOperatorGet();
    test_linked_list_sequence.testOperatorConcat();
    test_linked_list_sequence.testOperatorCompare();
    test_linked_list_sequence.testMap();
    test_linked_list_sequence.testWhere();
    test_linked_list_sequence.testReduce();

    if (test_linked_list_sequence.isCorrect()) cout << "All functions of the LinkedListSequence class were successfully PASSED\n\n\n";
    else cout << "ERROR! Not all functions of the LinkedListSequence class were successfully passed\n\n\n";
    

    return 0;
}