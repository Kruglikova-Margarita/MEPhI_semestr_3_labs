#include "../Sequence/sequence.h"
#include "../SmartPtrs/unq_ptr.h"
#include "../SmartPtrs/shrd_ptr.h"
#include "functions_for_tests.h"

#ifndef testArraySequence_h
#define testArraySequence_h

class TestArraySequence {
private:
    bool is_correct_;

public:
    TestArraySequence() : is_correct_(true) {}

    bool isCorrect() const noexcept;

    void testGetFirst() noexcept;
    void testGetLast() noexcept;
    void testGet() noexcept;
    void testGetSubSequence() noexcept;
    void testGetLength() noexcept;
    void testAppend() noexcept;
    void testPrepend() noexcept;
    void testInsertAt() noexcept;
    void testDeleteElement() noexcept;
    void testSet() noexcept;
    void testConcat() noexcept;
    void testOperatorGet() noexcept;
    void testOperatorConcat() noexcept;
    void testOperatorCompare() noexcept;
    void testMap() noexcept;
    void testWhere() noexcept;
    void testReduce() noexcept;

};





bool TestArraySequence::isCorrect() const noexcept {
    return is_correct_;
}

void TestArraySequence::testGetFirst() noexcept {
    UnqPtr<int[]> ar(new int[2]{1, 2});
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 2));
    int first1 = s1->getFirst();
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>);

    bool correct = false;
    try {
        int first2 = s2->getFirst();
    }
    catch (...) {
        correct = true;
    }

    if ((first1 == 1) && (correct == true))
        std::cout << "getFirst       : passed\n";
    else {
        std::cout << "getFirst       : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testGetLast() noexcept {
    UnqPtr<int[]> ar(new int[2]{1, 2});
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 2));
    int last1 = s1->getLast();
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>);

    bool correct = false;
    try {
        int last2 = s2->getFirst();
    }
    catch (...) {
        correct = true;
    }

    if ((last1 == 2) && (correct == true))
        std::cout << "getLast        : passed\n";
    else {
        std::cout << "getLast        : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testGet() noexcept {
    UnqPtr<int[]> ar(new int[4]{1, 2, 3, 4});
    UnqPtr<Sequence<int>> s = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 4));
    int el1 = s->get(2);

    bool correct1 = false;
    try {
        int el2 = s->get(-1);
    }
    catch (...) {
        correct1 = true;
    }

    bool correct2 = false;
    try {
        int el3 = s->get(5);
    }
    catch (...) {
        correct2 = true;
    }

    if ((el1 == 3) && (correct1 == true) && (correct2 == true))
        std::cout << "get            : passed\n";
    else {
        std::cout << "get            : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testGetSubSequence() noexcept {
    int* ar = new int[7]{1, 2, 3, 4, 5, 6, 7};
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 7));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar + 2, 3));
    UnqPtr<Sequence<int>> subS1 = s1->getSubSequence(2, 4);

    bool correct1 = false;
    try {
        UnqPtr<Sequence<int>> subS2 = s1->getSubSequence(-1, 3);
    }
    catch (...) {
        correct1 = true;
    }

    bool correct2 = false;
    try {
        UnqPtr<Sequence<int>> subS3 = s1->getSubSequence(2, 10);
    }
    catch (...) {
        correct2 = true;
    }

    bool correct3 = false;
    try {
        UnqPtr<Sequence<int>> subS4 = s1->getSubSequence(5, 1);
    }
    catch (...) {
        correct3 = true;
    }

    if (((*s2) == (*subS1)) && correct1 && correct2 && correct3)
        std::cout << "getSubSequence : passed\n";
    else {
        std::cout << "getSubSequence : failed\n";
        is_correct_ = false;
    }

    delete[] ar;
}

void TestArraySequence::testGetLength() noexcept {
    UnqPtr<int[]> ar(new int[7]{1, 2, 3, 4, 5, 6, 7});
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 7));
    size_t len1 = s1->getLength();
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    size_t len2 = s2->getLength();

    if ((len1 == 7) && (len2 == 0))
        std::cout << "getLength      : passed\n";
    else {
        std::cout << "getLength      : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testAppend() noexcept {
    UnqPtr<int[]> ar(new int[5]{1, 2, 3, 4, 5});
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 5));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 4));
    s2->append(5);

    UnqPtr<Sequence<int>> s3 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 1));
    UnqPtr<Sequence<int>> s4 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    s4->append(1);

    if (((*s1) == (*s2)) && ((*s3) == (*s4)))
        std::cout << "append         : passed\n";
    else {
        std::cout << "append         : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testPrepend() noexcept {
    int* ar = new int[5]{1, 2, 3, 4, 5};
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 5));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar + 1, 4));
    s2->prepend(1);

    UnqPtr<Sequence<int>> s3 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 1));
    UnqPtr<Sequence<int>> s4 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    s4->prepend(1);

    if (((*s1) == (*s2)) && ((*s3) == (*s4)))
        std::cout << "prepend        : passed\n";
    else {
        std::cout << "prepend        : failed\n";
        is_correct_ = false;
    }

    delete[] ar;
}

void TestArraySequence::testInsertAt() noexcept {
    UnqPtr<int[]> ar1(new int[4]{1, 2, 4, 5});

    UnqPtr<int[]> ar2(new int[5]{1, 2, 3, 4, 5});

    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar1, 4));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar2, 5));
    s1->insertAt(3, 2);

    bool correct1 = false;
    try {
        s1->insertAt(1, -1);
    }
    catch (...) {
        correct1 = true;
    }

    bool correct2 = false;
    try {
        s1->insertAt(1, 10);
    }
    catch (...) {
        correct2 = true;
    }

    if (((*s1) == (*s2)) && correct1 && correct2)
        std::cout << "insertAt       : passed\n";
    else {
        std::cout << "insertAt       : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testDeleteElement() noexcept {
    int *ar = new int[3]{1, 2, 3};
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 3));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar + 1, 2));
    UnqPtr<Sequence<int>> s3 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar + 1, 1));
    UnqPtr<Sequence<int>> s4 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    bool correct1 = false;
    try {
        s1->deleteElement(-2);
    }
    catch (...) {
        correct1 = true;
    }
    bool correct2 = false;
    try {
        s1->deleteElement(10);
    }
    catch (...) {
        correct2 = true;
    }
    int correct3 = 0;
    s1->deleteElement(0);
    if ((*s1) == (*s2)) correct3++;
    s1->deleteElement(1);
    if ((*s1) == (*s3)) correct3++;
    s1->deleteElement(0);
    if ((*s1) == (*s4)) correct3++;

    if (correct1 && correct2 && (correct3 == 3))
        std::cout << "deleteElement  : passed\n";
    else {
        std::cout << "deleteElement  : failed\n";
        is_correct_ = false;
    }

    delete [] ar;
}

void TestArraySequence::testSet() noexcept {
    int *ar = new int[3]{1, 2, 3};
    UnqPtr<Sequence<int>> s = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 3));
    bool correct1 = false;
    try {
        s->set(-2, 0);
    }
    catch (...) {
        correct1 = true;
    }
    bool correct2 = false;
    try {
        s->set(10, 0);
    }
    catch (...) {
        correct2 = true;
    }

    s->set(1, 10);

    if (correct1 && correct2 && ((*s)[1] == 10))
        std::cout << "set            : passed\n";
    else {
        std::cout << "set            : failed\n";
        is_correct_ = false;
    }

    delete[] ar;
}

void TestArraySequence::testConcat() noexcept {
    int *ar = new int[5]{1, 2, 3, 4, 5};
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 2));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar + 2, 3));
    UnqPtr<Sequence<int>> s3 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 5));
    UnqPtr<Sequence<int>> s4 = s1->concat(*s2);
    UnqPtr<Sequence<int>> s5 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    UnqPtr<Sequence<int>> s6 = s1->concat(*s5);
    UnqPtr<Sequence<int>> s7 = s5->concat(*s1);

    if (((*s3) == (*s4)) && ((*s1) == (*s6)) && ((*s1) == (*s7)))
        std::cout << "concat         : passed\n";
    else {
        std::cout << "concat         : failed\n";
        is_correct_ = false;
    }

    delete [] ar;
}

void TestArraySequence::testOperatorGet() noexcept {
    int *ar = new int[4]{1, 2, 3, 4};
    UnqPtr<Sequence<int>> s = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 4));
    int el1 = (*s)[2];

    bool correct1 = false;
    try {
        int el2 = (*s)[-1];
    }
    catch (...) {
        correct1 = true;
    }

    bool correct2 = false;
    try {
        int el3 = (*s)[5];
    }
    catch (...) {
        correct2 = true;
    }

    if ((el1 == 3) && (correct1 == true) && (correct2 == true))
        std::cout << "operator []    : passed\n";
    else {
        std::cout << "operator []    : failed\n";
        is_correct_ = false;
    }

    delete [] ar;
}

void TestArraySequence::testOperatorConcat() noexcept {
    int *ar = new int[5]{1, 2, 3, 4, 5};
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 2));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar + 2, 3));
    UnqPtr<Sequence<int>> s3 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 5));
    UnqPtr<Sequence<int>> s4 = (*s1) + (*s2);
    UnqPtr<Sequence<int>> s5 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    UnqPtr<Sequence<int>> s6 = (*s1) + (*s5);
    UnqPtr<Sequence<int>> s7 = (*s5) + (*s1);

    if (((*s3) == (*s4)) && ((*s1) == (*s6)) && ((*s1) == (*s7)))
        std::cout << "operator +     : passed\n";
    else {
        std::cout << "operator +     : failed\n";
        is_correct_ = false;
    }

    delete [] ar;
}

void TestArraySequence::testOperatorCompare() noexcept {
    int *ar = new int[4]{1, 2, 3, 4};
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 4));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    UnqPtr<Sequence<int>> s3 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 3));
    s3->append(10);

    if ((!((*s1) == (*s2))) && (!((*s1) == (*s3))) && ((*s1) == (*s1)))
        std::cout << "operator ==    : passed\n";
    else {
        std::cout << "operator ==    : failed\n";
        is_correct_ = false;
    }

    delete [] ar;
}

void TestArraySequence::testMap() noexcept {
    UnqPtr<int[]> ar1 = UnqPtr<int[]>(new int[4]{1, 2, 3, 4});
    UnqPtr<int[]> ar2 = UnqPtr<int[]>(new int[4]{2, 4, 6, 8});
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar1, 4));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar2, 4));
    UnqPtr<Sequence<int>> s3 = s1->map(mapFunction);
    UnqPtr<Sequence<int>> s4 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    UnqPtr<Sequence<int>> s5 = s4->map(mapFunction);

    if (((*s2) == (*s3)) && ((*s4) == (*s5)))
        std::cout << "map            : passed\n";
    else {
        std::cout << "map            : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testWhere() noexcept {
    UnqPtr<int[]> ar1 = UnqPtr<int[]>(new int[8]{4, 2, 9, 13, 42, -4, 5, 1});
    UnqPtr<int[]> ar2 = UnqPtr<int[]>(new int[8]{4, 2, 42, -4});

    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar1, 8));
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar2, 4));
    UnqPtr<Sequence<int>> s3 = s1->where(whereFunction);
    UnqPtr<Sequence<int>> s4 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    UnqPtr<Sequence<int>> s5 = s4->where(whereFunction);

    if (((*s2) == (*s3)) && ((*s4) == (*s5)))
        std::cout << "where          : passed\n";
    else {
        std::cout << "where          : failed\n";
        is_correct_ = false;
    }
}

void TestArraySequence::testReduce() noexcept {
    UnqPtr<int[]> ar = UnqPtr<int[]>(new int[5]{1, 2, 3, 4, 5});
    UnqPtr<Sequence<int>> s1 = UnqPtr<Sequence<int>>(new ArraySequence<int>(ar, 5));
    int r1 = s1->reduce(reduceFunction, 10);
    UnqPtr<Sequence<int>> s2 = UnqPtr<Sequence<int>>(new ArraySequence<int>);
    bool correct = false;
    try {
        int r2 = s2->reduce(reduceFunction, 10);
    }
    catch (...) {
        correct = true;
    }

    if ((r1 == 25) && correct)
        std::cout << "reduce         : passed\n";
    else {
        std::cout << "reduce         : failed\n";
        is_correct_ = false;
    }
}

#endif