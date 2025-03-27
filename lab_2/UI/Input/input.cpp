#include <iostream>
#include "input.h"
#include "../../Sequence/sequence.h"
#include "../../SmartPtrs/shrd_ptr.h"
#include "../Menu/menu.h"

using namespace std;

ShrdPtr<Sequence<float>> inputSequence() {
    cout << "Input the length of sequence: ";
    int length = inputNatural();

    Sequence<float>* ptr_sequence = new ArraySequence<float>;
    ShrdPtr<Sequence<float>> sequence(ptr_sequence);

    for (int i = 0; i < length; i++) {
        cout << "sequence[" << i << "] = ";
        float item = inputFloat();
        sequence->append(item);
    }

    return sequence;
}

int inputNatural() {
    int n = 0;
    int check = 0;
    while ((check != 1) || (n <= 0)) {
        check = scanf("%d", &n);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if ((check != 1) || (n <= 0)) {
            scanf("%*[^\n]");
            printf("Invalid value! Try again: ");
        }
    }

    return n;
}

int inputInt() {
    int n = 0;
    int check = 0;
    while (check != 1) {
        check = scanf("%d", &n);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if (check != 1) {
            scanf("%*[^\n]");
            printf("Invalid value! Try again: ");
        }
    }

    return n;
}

float inputFloat() {
    float n = 0;
    int check = 0;
    while (check != 1) {
        check = scanf("%f", &n);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if (check != 1) {
            scanf("%*[^\n]");
            printf("Invalid value! Try again: ");
        }
    }

    return n;
}

int inputAction() {
    int a = -10;
    int check = 0;
    std::cout << "\nChoose action: ";
    while ((a != 1) && (a != 2) && (a != 3) && (a != 4) && (a != 5) && (a != 6) && (a != 7) && (a != 8) && (a != 9) && (a != 10) && (a != 0) && (a != -1)) {
        check = scanf("%d", &a);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if ((a != 1) && (a != 2) && (a != 3) && (a != 4) && (a != 5) && (a != 6) && (a != 7) && (a != 8) && (a != 9) && (a != 10) && (a != 0) && (a != -1)) {
            scanf("%*[^\n]");
            std::cout << "Invalid action! Try again: ";
        }
    }

    return a;
}

int inputWayCreatingSequence() {
    int a = -10;
    int check = 0;
    std::cout << "\nChoose way: ";
    while ((a != 1) && (a != 2)) {
        check = scanf("%d", &a);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if ((a != 1) && (a != 2)) {
            scanf("%*[^\n]");
            std::cout << "Invalid way! Try again: ";
        }
    }

    return a;
}

ShrdPtr<Sequence<float>> generateSequence(int lower_bound, int upper_bound, int length) {
    Sequence<float>* ptr_sequence = new ArraySequence<float>;
    ShrdPtr<Sequence<float>> sequence(ptr_sequence);

    if (lower_bound > upper_bound)
        cout << "The lower bound can't be larger than the upper one\n";
    else {
        float number;

        srand(time(nullptr));

        for (int i = 0; i < length; i++) {
            number = rand() % (upper_bound - lower_bound + 1) + lower_bound;
            sequence->append(number);
        }
    }

    return sequence;
}

ShrdPtr<Sequence<float>> createSequence() {
    printMenuOfCreatingSequence();
    int way_creating_sequence = inputWayCreatingSequence();

    ShrdPtr<Sequence<float>> sequence;

    switch (way_creating_sequence) {
        case 1:
            cout << "Input sequence to sort:\n";
            sequence = inputSequence();

            break;

        case 2:
            cout << "Input lower bound of the range: ";
            int lower_bound = inputInt();
            cout << "Input upper bound of the range: ";
            int upper_bound = inputInt();
            cout << "Input the length of sequence: ";
            int length = inputNatural();

            sequence = generateSequence(lower_bound, upper_bound, length);

            break;
    }

    return sequence;
}