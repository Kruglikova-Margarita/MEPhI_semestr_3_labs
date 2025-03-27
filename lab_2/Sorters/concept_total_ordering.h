#ifndef LAB_3SEM_2_CONCEPT_TOTAL_ORDERING_H
#define LAB_3SEM_2_CONCEPT_TOTAL_ORDERING_H

template <typename T>
concept TotalOrdering =
requires(T a, T b) {
    a < b;
    a > b;
    a == b;
};

#endif //LAB_3SEM_2_CONCEPT_TOTAL_ORDERING_H
