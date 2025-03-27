#ifndef LAB_3SEM_3_ACTIONS_H
#define LAB_3SEM_3_ACTIONS_H

#include <iostream>
#include "../tuple.h"
#include "../../Sequence/sequence.h"
#include "../../MemoryManager//memory_manager.h"

void action1(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects, ShrdPtr<MemoryManager> memory_manager);
void action2(ShrdPtr<Sequence<Tuple<std::string, size_t, void*>>> objects, ShrdPtr<MemoryManager> memory_manager);

#endif //LAB_3SEM_3_ACTIONS_H
