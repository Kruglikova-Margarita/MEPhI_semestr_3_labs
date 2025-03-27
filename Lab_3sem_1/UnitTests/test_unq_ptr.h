#include "../SmartPtrs/unq_ptr.h"
#include "../Sequence/option.h"

using namespace std;

#ifndef testUnqPtr_h
#define testUnqPtr_h

class TestUnqPtr_SingleObject {
private:
    bool is_correct_;

public:
    TestUnqPtr_SingleObject() : is_correct_(true) {}

    bool isCorrect() const noexcept;

    void testGet() noexcept;
    void testRelease() noexcept;
    void testReset() noexcept;
    void testSwap() noexcept;
    void testOperatorAssignment() noexcept;
    void testOperatorBool() noexcept;
    void testOperatorDereference() noexcept;
    void testOperatorAccess() noexcept;
    void testOperatorCompare() noexcept;

};



class TestUnqPtr_Array {
private:
    bool is_correct_;

public:
    TestUnqPtr_Array() : is_correct_(true) {}

    bool isCorrect() const noexcept;

    void testGet() noexcept;
    void testRelease() noexcept;
    void testReset() noexcept;
    void testSwap() noexcept;
    void testOperatorAssignment() noexcept;
    void testOperatorBool() noexcept;
    void testOperatorGetElement() noexcept;
    void testOperatorCompare() noexcept;

};







bool TestUnqPtr_SingleObject::isCorrect() const noexcept {
    return is_correct_;
}

void TestUnqPtr_SingleObject::testGet() noexcept {
    int *ptr = new int(123);
    UnqPtr<int> unq_ptr(ptr);

    if (unq_ptr.get() == ptr)
        cout << "get           : passed\n";
    else {
        cout << "get           : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testRelease() noexcept {
    int *ptr = new int(123);
    UnqPtr<int> unq_ptr(ptr);

    int *released_ptr = unq_ptr.release();

    if ((released_ptr == ptr) && (unq_ptr.get() == nullptr))
        cout << "release       : passed\n";
    else {
        cout << "release       : failed\n";
        is_correct_ = false;
    }

    delete released_ptr;
}

void TestUnqPtr_SingleObject::testReset() noexcept {
    UnqPtr<int> unq_ptr1(new int(123));
    int *ptr1 = new int(456);

    unq_ptr1.reset(ptr1);

    int *ptr2 = new int(789);
    UnqPtr<int> unq_ptr2(ptr2);

    unq_ptr2.reset(ptr2);

    if ((unq_ptr1.get() == ptr1) && (unq_ptr2.get() == nullptr))
        cout << "reset         : passed\n";
    else {
        cout << "release         : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testSwap() noexcept {
    int *ptr1 = new int(123);
    int *ptr2 = new int(456);
    UnqPtr<int> unq_ptr1(ptr1);
    UnqPtr<int> unq_ptr2(ptr2);

    unq_ptr1.swap(unq_ptr2);

    if ((unq_ptr1.get() == ptr2) && (unq_ptr2.get() == ptr1))
        cout << "swap          : passed\n";
    else {
        cout << "swap          : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testOperatorAssignment() noexcept {
    int *ptr = new int(456);
    UnqPtr<int> unq_ptr1(new int(123));
    UnqPtr<int> unq_ptr2(ptr);

    unq_ptr1 = move(unq_ptr2);

    if (unq_ptr1.get() == ptr)
        cout << "operator =    : passed\n";
    else {
        cout << "operator =    : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testOperatorBool() noexcept {
    UnqPtr<int> unq_ptr1(new int(123));
    UnqPtr<int> unq_ptr2(nullptr);

    if (unq_ptr1 && !unq_ptr2)
        cout << "operator bool : passed\n";
    else {
        cout << "operator bool : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testOperatorDereference() noexcept {
    UnqPtr<int> unq_ptr(new int(123));

    if (*unq_ptr == 123)
        cout << "operator *    : passed\n";
    else {
        cout << "operator *    : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testOperatorAccess() noexcept {
    UnqPtr<Option<int>> unq_ptr(new Option(123));

    if (unq_ptr->get() == 123)
        cout << "operator ->   : passed\n";
    else {
        cout << "operator ->   : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_SingleObject::testOperatorCompare() noexcept {
    UnqPtr<int> unq_ptr1(new int(123));
    UnqPtr<int> unq_ptr2(new int(123));

    if (!(unq_ptr1 == unq_ptr2) && (unq_ptr1 == unq_ptr1))
        cout << "operator ==   : passed\n";
    else {
        cout << "operator ==   : failed\n";
        is_correct_ = false;
    }
}





bool TestUnqPtr_Array::isCorrect() const noexcept {
    return is_correct_;
}

void TestUnqPtr_Array::testGet() noexcept {
    int *ptr = new int[3];
    UnqPtr<int[]> unq_ptr(ptr);

    if (unq_ptr.get() == ptr)
        cout << "get           : passed\n";
    else {
        cout << "get           : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_Array::testRelease() noexcept {
    int *ptr = new int[3];
    UnqPtr<int[]> unq_ptr(ptr);

    int *released_ptr = unq_ptr.release();

    if ((released_ptr == ptr) && (unq_ptr.get() == nullptr))
        cout << "release       : passed\n";
    else {
        cout << "release       : failed\n";
        is_correct_ = false;
    }

    delete[] released_ptr;
}

void TestUnqPtr_Array::testReset() noexcept {
    UnqPtr<int[]> unq_ptr1(new int[3]);
    int *ptr1 = new int[3];

    unq_ptr1.reset(ptr1);

    int *ptr2 = new int[3];
    UnqPtr<int[]> unq_ptr2(ptr2);

    unq_ptr2.reset(ptr2);

    if ((unq_ptr1.get() == ptr1) && (unq_ptr2.get() == nullptr))
        cout << "reset         : passed\n";
    else {
        cout << "release         : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_Array::testSwap() noexcept {
    int *ptr1 = new int[3];
    int *ptr2 = new int[3];
    UnqPtr<int[]> unq_ptr1(ptr1);
    UnqPtr<int[]> unq_ptr2(ptr2);

    unq_ptr1.swap(unq_ptr2);

    if ((unq_ptr1.get() == ptr2) && (unq_ptr2.get() == ptr1))
        cout << "swap          : passed\n";
    else {
        cout << "swap          : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_Array::testOperatorAssignment() noexcept {
    int *ptr = new int[3];
    UnqPtr<int[]> unq_ptr1(new int[3]);
    UnqPtr<int[]> unq_ptr2(ptr);

    unq_ptr1 = move(unq_ptr2);

    if (unq_ptr1.get() == ptr)
        cout << "operator =    : passed\n";
    else {
        cout << "operator =    : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_Array::testOperatorBool() noexcept {
    UnqPtr<int[]> unq_ptr1(new int[3]);
    UnqPtr<int[]> unq_ptr2(nullptr);

    if (unq_ptr1 && !unq_ptr2)
        cout << "operator bool : passed\n";
    else {
        cout << "operator bool : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_Array::testOperatorGetElement() noexcept {
    UnqPtr<int[]> unq_ptr(new int[3]{1, 2, 3});

    if ((unq_ptr[0] == 1) && (unq_ptr[1] == 2) && (unq_ptr[2] == 3))
        cout << "operator []   : passed\n";
    else {
        cout << "operator []   : failed\n";
        is_correct_ = false;
    }
}

void TestUnqPtr_Array::testOperatorCompare() noexcept {
    UnqPtr<int[]> unq_ptr1(new int[3]);
    UnqPtr<int[]> unq_ptr2(new int[3]);

    if (!(unq_ptr1 == unq_ptr2) && (unq_ptr1 == unq_ptr1))
        cout << "operator ==   : passed\n";
    else {
        cout << "operator ==   : failed\n";
        is_correct_ = false;
    }
}

#endif