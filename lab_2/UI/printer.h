#include "../Sequence/sequence.h"

#ifndef LAB_3SEM_2_PRINTER_H
#define LAB_3SEM_2_PRINTER_H

using namespace std;

template <typename T>
void printSequence(ShrdPtr<Sequence<T>> sequence) {
    int len = sequence->getLength();
    for (int i = 0; i < len; i++) {
        cout << "[" << i << "] = " << sequence->get(i) << "\n";
        //cout << sequence->get(i) << "; ";
    }
    cout << "\n";
}

#endif //LAB_3SEM_2_PRINTER_H
