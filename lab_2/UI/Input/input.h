#include <iostream>
#include "../../Sequence/sequence.h"
#include "../../SmartPtrs/shrd_ptr.h"

#ifndef LAB_3SEM_2_INPUT_H
#define LAB_3SEM_2_INPUT_H

ShrdPtr<Sequence<float>> inputSequence();
int inputNatural();
int inputInt();
float inputFloat();
int inputAction();
int inputWayCreatingSequence();
ShrdPtr<Sequence<float>> generateSequence(int lower_bound, int upper_bound, int length);
ShrdPtr<Sequence<float>> createSequence();

#endif //LAB_3SEM_2_INPUT_H
