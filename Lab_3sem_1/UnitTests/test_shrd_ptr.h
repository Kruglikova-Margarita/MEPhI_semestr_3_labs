#include "../SmartPtrs/shrd_ptr.h"
#include "../Sequence/option.h"

using namespace std;

#ifndef testShrdPtr_h
#define testShrdPtr_h

class TestShrdPtr_SingleObject {
private:
    bool is_correct_;

public:
    TestShrdPtr_SingleObject() : is_correct_(true) {}

    bool isCorrect() const noexcept;

    void testGet() noexcept;
    void testReset() noexcept;
    void testSwap() noexcept;
    void testUnique() noexcept;
    void testUseCount() noexcept;
    void testOperatorBool() noexcept;
    void testOperatorAssignment() noexcept;
    void testOperatorDereference() noexcept;
    void testOperatorAccess() noexcept;
    void testOperatorCompare() noexcept;

};



class TestShrdPtr_Array {
private:
    bool is_correct_;

public:
    TestShrdPtr_Array() : is_correct_(true) {}

    bool isCorrect() const noexcept;

    void testGet() noexcept;
    void testReset() noexcept;
    void testSwap() noexcept;
    void testUnique() noexcept;
    void testUseCount() noexcept;
    void testOperatorBool() noexcept;
    void testOperatorAssignment() noexcept;
    void testOperatorGetElement() noexcept;
    void testOperatorCompare() noexcept;
    
};







bool TestShrdPtr_SingleObject::isCorrect() const noexcept {
    return is_correct_;
}

void TestShrdPtr_SingleObject::testGet() noexcept {
    int *ptr = new int(123);
    ShrdPtr<int> shrd_ptr1(ptr);
    ShrdPtr<int> shrd_ptr2(shrd_ptr1);

    if ((shrd_ptr1.get() == ptr) && (shrd_ptr2.get() == ptr))
        cout << "get           : passed\n";
    else {
        cout << "get           : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testReset() noexcept {
    int *ptr1 = new int(123);
    int *ptr2 = new int(456);
    ShrdPtr<int> shrd_ptr1(ptr1);
    ShrdPtr<int> shrd_ptr2(shrd_ptr1);

    shrd_ptr1.reset(ptr2);

    if ((shrd_ptr1.get() == ptr2) && (shrd_ptr2.get() == ptr1))
        cout << "reset         : passed\n";
    else {
        cout << "reset         : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testSwap() noexcept {
    int *ptr1 = new int(123);
    ShrdPtr<int> shrd_ptr11(ptr1);
    ShrdPtr<int> shrd_ptr12(shrd_ptr11);
    ShrdPtr<int> shrd_ptr13(shrd_ptr11);
    int *ptr2 = new int(456);
    ShrdPtr<int> shrd_ptr21(ptr2);
    ShrdPtr<int> shrd_ptr22(shrd_ptr21);

    shrd_ptr11.swap(shrd_ptr21);

    if ((shrd_ptr11.get() == ptr2) && (shrd_ptr11.use_count() == 2) && (shrd_ptr21.get() == ptr1) && (shrd_ptr21.use_count() == 3))
        cout << "swap          : passed\n";
    else {
        cout << "swap          : failed\n";
        is_correct_ = false;
    }

}

void TestShrdPtr_SingleObject::testUnique() noexcept {
    ShrdPtr<int> shrd_ptr11(new int(123));

    ShrdPtr<int> shrd_ptr21(new int(456));
    ShrdPtr<int> shrd_ptr22(shrd_ptr21);

    if (shrd_ptr11.unique() && !(shrd_ptr21.unique()) && !(shrd_ptr22.unique()))
        cout << "unique        : passed\n";
    else {
        cout << "unique        : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testUseCount() noexcept {
    ShrdPtr<int> shrd_ptr11(new int(123));
    ShrdPtr<int> shrd_ptr12(shrd_ptr11);
    ShrdPtr<int> shrd_ptr13(shrd_ptr11);

    ShrdPtr<int> shrd_ptr21(new int(456));
    ShrdPtr<int> shrd_ptr22(shrd_ptr21);

    if ((shrd_ptr11.use_count() == 3) && (shrd_ptr12.use_count() == 3) && (shrd_ptr13.use_count() == 3) && (shrd_ptr21.use_count() == 2) && (shrd_ptr22.use_count() == 2))
        cout << "use_count     : passed\n";
    else {
        cout << "use_count     : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testOperatorBool() noexcept {
    ShrdPtr<int> shrd_ptr1(new int(123));
    ShrdPtr<int> shrd_ptr2(nullptr);

    if (shrd_ptr1 && !shrd_ptr2)
        cout << "operator bool : passed\n";
    else {
        cout << "operator bool : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testOperatorAssignment() noexcept {
    ShrdPtr<int> shrd_ptr11(new int(123));
    int *ptr2 = new int(456);
    ShrdPtr<int> shrd_ptr21(ptr2);
    ShrdPtr<int> shrd_ptr22(shrd_ptr21);

    shrd_ptr11 = shrd_ptr21;

    int *ptr3 = new int(678);
    ShrdPtr<int> shrd_ptr31(ptr3);
    ShrdPtr<int> shrd_ptr32(shrd_ptr31);
    int *ptr4 = new int(987);
    ShrdPtr<int> shrd_ptr41(ptr4);
    ShrdPtr<int> shrd_ptr42(shrd_ptr41);

    shrd_ptr31 = shrd_ptr41;

    if ((shrd_ptr11.get() == ptr2) && (shrd_ptr11.use_count() == 3) && (shrd_ptr21.use_count() == 3) && (shrd_ptr22.use_count() == 3) && (shrd_ptr31.get() == ptr4) && (shrd_ptr31.use_count() == 3) && (shrd_ptr41.use_count() == 3) && (shrd_ptr42.use_count() == 3) && (shrd_ptr32.use_count() == 1))
        cout << "operator =    : passed\n";
    else {
        cout << "operator =    : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testOperatorDereference() noexcept {
    ShrdPtr<int> shrd_ptr(new int(123));

    if (*shrd_ptr == 123)
        cout << "operator *    : passed\n";
    else {
        cout << "operator *    : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testOperatorAccess() noexcept {
    ShrdPtr<Option<int>> shrd_ptr(new Option(123));

    if (shrd_ptr->get() == 123)
        cout << "operator ->   : passed\n";
    else {
        cout << "operator ->   : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_SingleObject::testOperatorCompare() noexcept {
    ShrdPtr<int> shrd_ptr11(new int(123));
    ShrdPtr<int> shrd_ptr12(shrd_ptr11);

    ShrdPtr<int> shrd_ptr21(new int(456));

    if ((shrd_ptr11 == shrd_ptr11) && (shrd_ptr11 == shrd_ptr12) && !(shrd_ptr11 == shrd_ptr21) && !(shrd_ptr12 == shrd_ptr21))
        cout << "operator ==   : passed\n";
    else {
        cout << "operator ==   : failed\n";
        is_correct_ = false;
    }
}





bool TestShrdPtr_Array::isCorrect() const noexcept {
    return is_correct_;
}

void TestShrdPtr_Array::testGet() noexcept {
    int *ptr = new int[3];
    ShrdPtr<int[]> shrd_ptr1(ptr);
    ShrdPtr<int[]> shrd_ptr2(shrd_ptr1);

    if ((shrd_ptr1.get() == ptr) && (shrd_ptr2.get() == ptr))
        cout << "get           : passed\n";
    else {
        cout << "get           : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testReset() noexcept {
    int *ptr1 = new int[3];
    int *ptr2 = new int[3];
    ShrdPtr<int[]> shrd_ptr1(ptr1);
    ShrdPtr<int[]> shrd_ptr2(shrd_ptr1);

    shrd_ptr1.reset(ptr2);

    if ((shrd_ptr1.get() == ptr2) && (shrd_ptr2.get() == ptr1))
        cout << "reset         : passed\n";
    else {
        cout << "reset         : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testSwap() noexcept {
    int *ptr1 = new int[3];
    ShrdPtr<int[]> shrd_ptr11(ptr1);
    ShrdPtr<int[]> shrd_ptr12(shrd_ptr11);
    ShrdPtr<int[]> shrd_ptr13(shrd_ptr11);
    int *ptr2 = new int[3];
    ShrdPtr<int[]> shrd_ptr21(ptr2);
    ShrdPtr<int[]> shrd_ptr22(shrd_ptr21);

    shrd_ptr11.swap(shrd_ptr21);

    if ((shrd_ptr11.get() == ptr2) && (shrd_ptr11.use_count() == 2) && (shrd_ptr21.get() == ptr1) && (shrd_ptr21.use_count() == 3))
        cout << "swap          : passed\n";
    else {
        cout << "swap          : failed\n";
        is_correct_ = false;
    }

}

void TestShrdPtr_Array::testUnique() noexcept {
    ShrdPtr<int[]> shrd_ptr11(new int[3]);

    ShrdPtr<int[]> shrd_ptr21(new int[3]);
    ShrdPtr<int[]> shrd_ptr22(shrd_ptr21);

    if (shrd_ptr11.unique() && !(shrd_ptr21.unique()) && !(shrd_ptr22.unique()))
        cout << "unique        : passed\n";
    else {
        cout << "unique        : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testUseCount() noexcept {
    ShrdPtr<int[]> shrd_ptr11(new int[3]);
    ShrdPtr<int[]> shrd_ptr12(shrd_ptr11);
    ShrdPtr<int[]> shrd_ptr13(shrd_ptr11);

    ShrdPtr<int[]> shrd_ptr21(new int[3]);
    ShrdPtr<int[]> shrd_ptr22(shrd_ptr21);

    if ((shrd_ptr11.use_count() == 3) && (shrd_ptr12.use_count() == 3) && (shrd_ptr13.use_count() == 3) && (shrd_ptr21.use_count() == 2) && (shrd_ptr22.use_count() == 2))
        cout << "use_count     : passed\n";
    else {
        cout << "use_count     : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testOperatorBool() noexcept {
    ShrdPtr<int[]> shrd_ptr1(new int[3]);
    ShrdPtr<int[]> shrd_ptr2(nullptr);

    if (shrd_ptr1 && !shrd_ptr2)
        cout << "operator bool : passed\n";
    else {
        cout << "operator bool : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testOperatorAssignment() noexcept {
    ShrdPtr<int[]> shrd_ptr11(new int[3]);
    int *ptr2 = new int[3];
    ShrdPtr<int[]> shrd_ptr21(ptr2);
    ShrdPtr<int[]> shrd_ptr22(shrd_ptr21);

    shrd_ptr11 = shrd_ptr21;

    int *ptr3 = new int[3];
    ShrdPtr<int[]> shrd_ptr31(ptr3);
    ShrdPtr<int[]> shrd_ptr32(shrd_ptr31);
    int *ptr4 = new int[3];
    ShrdPtr<int[]> shrd_ptr41(ptr4);
    ShrdPtr<int[]> shrd_ptr42(shrd_ptr41);

    shrd_ptr31 = shrd_ptr41;

    if ((shrd_ptr11.get() == ptr2) && (shrd_ptr11.use_count() == 3) && (shrd_ptr21.use_count() == 3) && (shrd_ptr22.use_count() == 3) && (shrd_ptr31.get() == ptr4) && (shrd_ptr31.use_count() == 3) && (shrd_ptr41.use_count() == 3) && (shrd_ptr42.use_count() == 3) && (shrd_ptr32.use_count() == 1))
        cout << "operator =    : passed\n";
    else {
        cout << "operator =    : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testOperatorGetElement() noexcept {
    ShrdPtr<int[]> shrd_ptr(new int[3]{1, 2, 3});

    if ((shrd_ptr[0] == 1) && (shrd_ptr[1] == 2) && (shrd_ptr[2] == 3))
        cout << "operator []   : passed\n";
    else {
        cout << "operator []   : failed\n";
        is_correct_ = false;
    }
}

void TestShrdPtr_Array::testOperatorCompare() noexcept {
    ShrdPtr<int[]> shrd_ptr11(new int[3]);
    ShrdPtr<int[]> shrd_ptr12(shrd_ptr11);

    ShrdPtr<int[]> shrd_ptr21(new int[3]);

    if ((shrd_ptr11 == shrd_ptr11) && (shrd_ptr11 == shrd_ptr12) && !(shrd_ptr11 == shrd_ptr21) && !(shrd_ptr12 == shrd_ptr21))
        cout << "operator ==   : passed\n";
    else {
        cout << "operator ==   : failed\n";
        is_correct_ = false;
    }
}



#endif