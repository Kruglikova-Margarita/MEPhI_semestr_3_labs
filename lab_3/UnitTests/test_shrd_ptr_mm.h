#ifndef LAB_3SEM_3_TEST_SHRD_PTR_MM_H
#define LAB_3SEM_3_TEST_SHRD_PTR_MM_H

#include "../MemoryManager//memory_manager.h"
#include "../MemoryManager//shrd_ptr_mm.h"

class TestShrdPtrMM_SingleObject {
private:
    ShrdPtr<MemoryManager> memory_manager_;
    bool is_correct_;

    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_0_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_0_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_1_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_1_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_2_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_2_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_2_1_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_2_1_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_3_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_3_;

    bool testMemory(ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> correct_free_memory, ShrdPtr<Sequence<Pair<size_t, size_t>>> correct_alloc_memory) const noexcept;

    bool testReset() noexcept;
    bool testSwap() noexcept;
    bool testUnique() noexcept;
    bool testUseCount() noexcept;
    bool testOperatorBool() noexcept;
    bool testOperatorAssignment() noexcept;
    bool testOperatorDereference() noexcept;
    bool testOperatorAccess() noexcept;
    bool testOperatorCompare() noexcept;

    void testFunctionTemplate(bool (TestShrdPtrMM_SingleObject::*function)(), std::string message) noexcept;

public:
    TestShrdPtrMM_SingleObject() noexcept;

    bool isCorrect() const noexcept;

    void testAllFunctions() noexcept;

};



class TestShrdPtrMM_Array {
private:
    ShrdPtr<MemoryManager> memory_manager_;
    bool is_correct_;

    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_0_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_0_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_1_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_1_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_2_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_2_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_2_1_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_2_1_;
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory_state_3_;
    ShrdPtr<Sequence<Pair<size_t, size_t>>> alloc_memory_state_3_;

    bool testMemory(ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> correct_free_memory, ShrdPtr<Sequence<Pair<size_t, size_t>>> correct_alloc_memory) const noexcept;

    bool testReset() noexcept;
    bool testSwap() noexcept;
    bool testUnique() noexcept;
    bool testUseCount() noexcept;
    bool testOperatorBool() noexcept;
    bool testOperatorAssignment() noexcept;
    bool testOperatorGetElement() noexcept;
    bool testOperatorCompare() noexcept;

    void testFunctionTemplate(bool (TestShrdPtrMM_Array::*function)(), std::string message) noexcept;

public:
    TestShrdPtrMM_Array() noexcept;

    bool isCorrect() const noexcept;

    void testAllFunctions() noexcept;

};



class Integer {
private:
    int value_;

public:
    Integer(int data) noexcept : value_(data) {}

    int get() const noexcept {
        return value_;
    }
};





TestShrdPtrMM_SingleObject::TestShrdPtrMM_SingleObject() noexcept : memory_manager_(new MemoryManager(50)), is_correct_(true),
    free_memory_state_0_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(50, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{0}), 1)))}), 1)),
    alloc_memory_state_0_(new ArraySequence<Pair<size_t, size_t>>),

    free_memory_state_1_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(38, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{12}), 1)))}), 1)),
    alloc_memory_state_1_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[2]{Pair<size_t, size_t>(0, 4),Pair<size_t, size_t>(4, 8)}), 2)),

    free_memory_state_2_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(26, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{24}), 1)))}), 1)),
    alloc_memory_state_2_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[4]{Pair<size_t, size_t>(0, 4),Pair<size_t, size_t>(4, 8),Pair<size_t, size_t>(12, 4),Pair<size_t, size_t>(16, 8)}), 4)),

    free_memory_state_2_1_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(30, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{20}), 1)))}), 1)),
    alloc_memory_state_2_1_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[3]{Pair<size_t, size_t>(0, 4),Pair<size_t, size_t>(4, 8),Pair<size_t, size_t>(12, 8)}), 3)),

    free_memory_state_3_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(14, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{36}), 1)))}), 1)),
    alloc_memory_state_3_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[6]{Pair<size_t, size_t>(0, 4),Pair<size_t, size_t>(4, 8),Pair<size_t, size_t>(12, 4),Pair<size_t, size_t>(16, 8), Pair<size_t, size_t>(24, 4), Pair<size_t, size_t>(28, 8)}), 6))

    {}




bool TestShrdPtrMM_SingleObject::testMemory(ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> correct_free_memory, ShrdPtr<Sequence<Pair<size_t, size_t>>> correct_alloc_memory) const noexcept {
    bool check_correct = true;
    int len = correct_free_memory->getLength();
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory = memory_manager_->getListOfFreeMemory();

    if (free_memory->getLength() != len)
        check_correct = false;
    else {
        for (int i = 0; i < len; i++) {
            Pair<size_t, ShrdPtr<Sequence<size_t>>> free_memory_el = free_memory->get(i);
            Pair<size_t, ShrdPtr<Sequence<size_t>>> check_free_memory_el = correct_free_memory->get(i);

            if ((free_memory_el.getKey() != check_free_memory_el.getKey()) || (*free_memory_el.getValue() != *check_free_memory_el.getValue()))
                check_correct = false;
        }
    }

    if (check_correct && (*memory_manager_->getListOfAllocatedMemory() == *correct_alloc_memory))
        return true;
    else
        return false;
}

bool TestShrdPtrMM_SingleObject::isCorrect() const noexcept {
    return is_correct_;
}


void TestShrdPtrMM_SingleObject::testFunctionTemplate(bool (TestShrdPtrMM_SingleObject::*function)(), std::string message) noexcept {
    if ((this->*function)() && testMemory(free_memory_state_0_, alloc_memory_state_0_))
        std::cout << message << ": passed\n";
    else {
        std::cout << message << ": failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtrMM_SingleObject::testAllFunctions() noexcept {
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testReset,               "reset         ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testSwap,                "swap          ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testUnique,              "unique        ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testUseCount,            "use_count     ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testOperatorBool,        "operator bool ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testOperatorAssignment,  "operator =    ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testOperatorDereference, "operator *    ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testOperatorAccess,      "operator ->   ");
    testFunctionTemplate(&TestShrdPtrMM_SingleObject::testOperatorCompare,     "operator ==   ");
}


bool TestShrdPtrMM_SingleObject::testReset() noexcept {
    int *ptr1 = new(memory_manager_) int(123);

    ShrdPtrMM<int> shrd_ptr1(memory_manager_, ptr1);
    ShrdPtrMM<int> shrd_ptr2(shrd_ptr1);

    int *ptr2 = new(memory_manager_) int(456);
    shrd_ptr1.reset(memory_manager_, ptr2);

    if (!((*shrd_ptr1 == 456) && (*shrd_ptr2 == 123) && testMemory(free_memory_state_2_, alloc_memory_state_2_)))
        return false;

    return true;
}

bool TestShrdPtrMM_SingleObject::testSwap() noexcept {
    ShrdPtrMM<int> shrd_ptr11(memory_manager_, new(memory_manager_) int(123));
    ShrdPtrMM<int> shrd_ptr12(shrd_ptr11);
    ShrdPtrMM<int> shrd_ptr13(shrd_ptr11);

    ShrdPtrMM<int> shrd_ptr21(memory_manager_, new(memory_manager_) int(456));
    ShrdPtrMM<int> shrd_ptr22(shrd_ptr21);

    shrd_ptr11.swap(shrd_ptr21);

    if ((*shrd_ptr11 == 456) && (shrd_ptr11.use_count() == 2) && (*shrd_ptr21 == 123) && (shrd_ptr21.use_count() == 3) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testUnique() noexcept {
    ShrdPtrMM<int> shrd_ptr11(memory_manager_, new(memory_manager_) int(123));

    ShrdPtrMM<int> shrd_ptr21(memory_manager_, new(memory_manager_) int(456));
    ShrdPtrMM<int> shrd_ptr22(shrd_ptr21);

    if (shrd_ptr11.unique() && !(shrd_ptr21.unique()) && !(shrd_ptr22.unique() && testMemory(free_memory_state_2_, alloc_memory_state_2_)))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testUseCount() noexcept {
    ShrdPtrMM<int> shrd_ptr11(memory_manager_, new(memory_manager_) int(123));
    ShrdPtrMM<int> shrd_ptr12(shrd_ptr11);
    ShrdPtrMM<int> shrd_ptr13(shrd_ptr11);

    ShrdPtrMM<int> shrd_ptr21(memory_manager_, new(memory_manager_) int(456));
    ShrdPtrMM<int> shrd_ptr22(shrd_ptr21);

    if ((shrd_ptr11.use_count() == 3) && (shrd_ptr12.use_count() == 3) && (shrd_ptr13.use_count() == 3) && (shrd_ptr21.use_count() == 2) && (shrd_ptr22.use_count() == 2) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testOperatorBool() noexcept {
    ShrdPtrMM<int> shrd_ptr1(memory_manager_, new(memory_manager_) int(123));
    ShrdPtrMM<int> shrd_ptr2(memory_manager_);

    if (shrd_ptr1 && !shrd_ptr2 && testMemory(free_memory_state_2_1_, alloc_memory_state_2_1_))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testOperatorAssignment() noexcept {
    ShrdPtrMM<int> shrd_ptr11(memory_manager_, new(memory_manager_) int(123));

    ShrdPtrMM<int> shrd_ptr21(memory_manager_, new(memory_manager_) int(456));
    ShrdPtrMM<int> shrd_ptr22(shrd_ptr21);

    shrd_ptr11 = shrd_ptr21;

    ShrdPtrMM<int> shrd_ptr31(memory_manager_, new(memory_manager_) int(678));
    ShrdPtrMM<int> shrd_ptr32(shrd_ptr31);

    ShrdPtrMM<int> shrd_ptr41(memory_manager_, new(memory_manager_) int(987));
    ShrdPtrMM<int> shrd_ptr42(shrd_ptr41);

    shrd_ptr31 = shrd_ptr41;

    if ((*shrd_ptr11 == 456) && (shrd_ptr11.use_count() == 3) && (shrd_ptr21.use_count() == 3) && (shrd_ptr22.use_count() == 3) && (*shrd_ptr31 == 987) && (shrd_ptr31.use_count() == 3) && (shrd_ptr41.use_count() == 3) && (shrd_ptr42.use_count() == 3) && (shrd_ptr32.use_count() == 1) && testMemory(free_memory_state_3_, alloc_memory_state_3_))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testOperatorDereference() noexcept {
    ShrdPtrMM<int> shrd_ptr(memory_manager_, new(memory_manager_) int(123));

    if ((*shrd_ptr == 123) && testMemory(free_memory_state_1_, alloc_memory_state_1_))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testOperatorAccess() noexcept {
    ShrdPtrMM<Integer> shrd_ptr(memory_manager_, new(memory_manager_) Integer(123));

    if ((shrd_ptr->get() == 123) && testMemory(free_memory_state_1_, alloc_memory_state_1_))
        return true;

    return false;
}

bool TestShrdPtrMM_SingleObject::testOperatorCompare() noexcept {
    ShrdPtrMM<int> shrd_ptr11(memory_manager_, new(memory_manager_) int(123));
    ShrdPtrMM<int> shrd_ptr12(shrd_ptr11);

    ShrdPtrMM<int> shrd_ptr21(memory_manager_, new(memory_manager_) int(456));

    if ((shrd_ptr11 == shrd_ptr11) && (shrd_ptr11 == shrd_ptr12) && !(shrd_ptr11 == shrd_ptr21) && !(shrd_ptr12 == shrd_ptr21) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}






TestShrdPtrMM_Array::TestShrdPtrMM_Array() noexcept : memory_manager_(new MemoryManager(70)), is_correct_(true),
    free_memory_state_0_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(70, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{0}), 1)))}), 1)),
    alloc_memory_state_0_(new ArraySequence<Pair<size_t, size_t>>),

    free_memory_state_1_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(54, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{16}), 1)))}), 1)),
    alloc_memory_state_1_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[2]{Pair<size_t, size_t>(0, 8),Pair<size_t, size_t>(8, 8)}), 2)),

    free_memory_state_2_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(38, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{32}), 1)))}), 1)),
    alloc_memory_state_2_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[4]{Pair<size_t, size_t>(0, 8),Pair<size_t, size_t>(8, 8),Pair<size_t, size_t>(16, 8),Pair<size_t, size_t>(24, 8)}), 4)),

    free_memory_state_2_1_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(46, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{24}), 1)))}), 1)),
    alloc_memory_state_2_1_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[3]{Pair<size_t, size_t>(0, 8),Pair<size_t, size_t>(8, 8),Pair<size_t, size_t>(16, 8)}), 3)),

    free_memory_state_3_ (new ArraySequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>(ShrdPtr<Pair<size_t, ShrdPtr<Sequence<size_t>>>[]>(new Pair<size_t, ShrdPtr<Sequence<size_t>>>[1]{Pair<size_t, ShrdPtr<Sequence<size_t>>>(22, ShrdPtr<Sequence<size_t>>(new ArraySequence<size_t>(ShrdPtr<size_t[]>(new size_t[1]{48}), 1)))}), 1)),
    alloc_memory_state_3_(new ArraySequence<Pair<size_t, size_t>>(ShrdPtr<Pair<size_t, size_t>[]>(new Pair<size_t, size_t>[6]{Pair<size_t, size_t>(0, 8),Pair<size_t, size_t>(8, 8),Pair<size_t, size_t>(16, 8),Pair<size_t, size_t>(24, 8), Pair<size_t, size_t>(32, 8), Pair<size_t, size_t>(40, 8)}), 6))


{}

bool TestShrdPtrMM_Array::testMemory(ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> correct_free_memory, ShrdPtr<Sequence<Pair<size_t, size_t>>> correct_alloc_memory) const noexcept {
    bool check_correct = true;
    int len = correct_free_memory->getLength();
    ShrdPtr<Sequence<Pair<size_t, ShrdPtr<Sequence<size_t>>>>> free_memory = memory_manager_->getListOfFreeMemory();

    if (free_memory->getLength() != len)
        check_correct = false;
    else {
        for (int i = 0; i < len; i++) {
            Pair<size_t, ShrdPtr<Sequence<size_t>>> free_memory_el = free_memory->get(i);
            Pair<size_t, ShrdPtr<Sequence<size_t>>> check_free_memory_el = correct_free_memory->get(i);

            if ((free_memory_el.getKey() != check_free_memory_el.getKey()) || (*free_memory_el.getValue() != *check_free_memory_el.getValue()))
                check_correct = false;
        }
    }

    if (check_correct && (*memory_manager_->getListOfAllocatedMemory() == *correct_alloc_memory))
        return true;
    else
        return false;
}

bool TestShrdPtrMM_Array::isCorrect() const noexcept {
    return is_correct_;
}


void TestShrdPtrMM_Array::testFunctionTemplate(bool (TestShrdPtrMM_Array::*function)(), std::string message) noexcept {
    if ((this->*function)() && testMemory(free_memory_state_0_, alloc_memory_state_0_))
        std::cout << message << ": passed\n";
    else {
        std::cout << message << ": failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtrMM_Array::testAllFunctions() noexcept {
    testFunctionTemplate(&TestShrdPtrMM_Array::testReset,              "reset         ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testSwap,               "swap          ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testUnique,             "unique        ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testUseCount,           "use_count     ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testOperatorBool,       "operator bool ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testOperatorAssignment, "operator =    ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testOperatorGetElement, "operator []   ");
    testFunctionTemplate(&TestShrdPtrMM_Array::testOperatorCompare,    "operator ==   ");
}


bool TestShrdPtrMM_Array::testReset() noexcept {
    ShrdPtrMM<int[]> shrd_ptr1(memory_manager_, new(memory_manager_) int[2]{1, 2});
    ShrdPtrMM<int[]> shrd_ptr2(shrd_ptr1);

    shrd_ptr1.reset(memory_manager_, new(memory_manager_) int[2]{4, 5});

    if ((shrd_ptr1[0] == 4) && (shrd_ptr1[1] == 5) && (shrd_ptr2[0] == 1) && (shrd_ptr2[1] == 2) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testSwap() noexcept {
    ShrdPtrMM<int[]> shrd_ptr11(memory_manager_, new(memory_manager_) int[2]{1, 2});
    ShrdPtrMM<int[]> shrd_ptr12(shrd_ptr11);
    ShrdPtrMM<int[]> shrd_ptr13(shrd_ptr11);

    ShrdPtrMM<int[]> shrd_ptr21(memory_manager_, new(memory_manager_) int[2]{4, 5});
    ShrdPtrMM<int[]> shrd_ptr22(shrd_ptr21);

    shrd_ptr11.swap(shrd_ptr21);

    if ((shrd_ptr11[0] == 4) && (shrd_ptr11[1] == 5) && (shrd_ptr11.use_count() == 2) && (shrd_ptr21[0] == 1) && (shrd_ptr21[1] == 2) && (shrd_ptr21.use_count() == 3) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testUnique() noexcept {
    ShrdPtrMM<int[]> shrd_ptr11(memory_manager_, new(memory_manager_) int[2]{1, 2});

    ShrdPtrMM<int[]> shrd_ptr21(memory_manager_, new(memory_manager_) int[2]{4, 5});
    ShrdPtrMM<int[]> shrd_ptr22(shrd_ptr21);

    if (shrd_ptr11.unique() && !(shrd_ptr21.unique()) && !(shrd_ptr22.unique()) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testUseCount() noexcept {
    ShrdPtrMM<int[]> shrd_ptr11(memory_manager_, new(memory_manager_) int[2]{1, 2});
    ShrdPtrMM<int[]> shrd_ptr12(shrd_ptr11);
    ShrdPtrMM<int[]> shrd_ptr13(shrd_ptr11);

    ShrdPtrMM<int[]> shrd_ptr21(memory_manager_, new(memory_manager_) int[2]{4, 5});
    ShrdPtrMM<int[]> shrd_ptr22(shrd_ptr21);

    if ((shrd_ptr11.use_count() == 3) && (shrd_ptr12.use_count() == 3) && (shrd_ptr13.use_count() == 3) && (shrd_ptr21.use_count() == 2) && (shrd_ptr22.use_count() == 2) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testOperatorBool() noexcept {
    ShrdPtrMM<int[]> shrd_ptr1(memory_manager_, new(memory_manager_) int[2]{1, 2});
    ShrdPtrMM<int[]> shrd_ptr2(memory_manager_);

    if (shrd_ptr1 && !shrd_ptr2 && testMemory(free_memory_state_2_1_, alloc_memory_state_2_1_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testOperatorAssignment() noexcept {
    ShrdPtrMM<int[]> shrd_ptr11(memory_manager_, new(memory_manager_) int[2]{1, 2});

    ShrdPtrMM<int[]> shrd_ptr21(memory_manager_, new(memory_manager_) int[2]{3, 4});
    ShrdPtrMM<int[]> shrd_ptr22(shrd_ptr21);

    shrd_ptr11 = shrd_ptr21;

    ShrdPtrMM<int[]> shrd_ptr31(memory_manager_, new(memory_manager_) int[2]{5, 6});
    ShrdPtrMM<int[]> shrd_ptr32(shrd_ptr31);

    ShrdPtrMM<int[]> shrd_ptr41(memory_manager_, new(memory_manager_) int[2]{7, 8});
    ShrdPtrMM<int[]> shrd_ptr42(shrd_ptr41);

    shrd_ptr31 = shrd_ptr41;

    if ((shrd_ptr11[0] == 3) && (shrd_ptr11[1] == 4) && (shrd_ptr11.use_count() == 3) && (shrd_ptr21.use_count() == 3) && (shrd_ptr22.use_count() == 3) && (shrd_ptr31[0] == 7) && (shrd_ptr31[1] == 8) && (shrd_ptr31.use_count() == 3) && (shrd_ptr41.use_count() == 3) && (shrd_ptr42.use_count() == 3) && (shrd_ptr32.use_count() == 1)) //&& testMemory(free_memory_state_3_, alloc_memory_state_3_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testOperatorGetElement() noexcept {
    ShrdPtrMM<int[]> shrd_ptr(memory_manager_, new(memory_manager_) int[2]{1, 2});

    if ((shrd_ptr[0] == 1) && (shrd_ptr[1] == 2) && testMemory(free_memory_state_1_, alloc_memory_state_1_))
        return true;

    return false;
}

bool TestShrdPtrMM_Array::testOperatorCompare() noexcept {
    ShrdPtrMM<int[]> shrd_ptr11(memory_manager_, new(memory_manager_) int[2]{1, 2});
    ShrdPtrMM<int[]> shrd_ptr12(shrd_ptr11);

    ShrdPtrMM<int[]> shrd_ptr21(memory_manager_, new(memory_manager_) int[2]{3, 4});

    if ((shrd_ptr11 == shrd_ptr11) && (shrd_ptr11 == shrd_ptr12) && !(shrd_ptr11 == shrd_ptr21) && !(shrd_ptr12 == shrd_ptr21) && testMemory(free_memory_state_2_, alloc_memory_state_2_))
        return true;

    return false;
}

#endif //LAB_3SEM_3_TEST_SHRD_PTR_MM_H
