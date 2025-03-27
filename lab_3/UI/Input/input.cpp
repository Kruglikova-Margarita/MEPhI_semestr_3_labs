#include <iostream>

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

int inputAction() {
    int a = -10;
    int check = 0;
    std::cout << "\nChoose action: ";
    while ((a != 1) && (a != 2) && (a != -1)) {
        check = scanf("%d", &a);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if ((a != 1) && (a != 2) && (a != -1)) {
            scanf("%*[^\n]");
            std::cout << "Invalid action! Try again: ";
        }
    }

    return a;
}

int inputWayArrayOrNot() {
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

int inputType() {
    int a = -10;
    int check = 0;
    std::cout << "\nChoose type: ";
    while ((a != 1) && (a != 2) && (a != 3)) {
        check = scanf("%d", &a);
        if (check == EOF) {
            throw std::out_of_range("EOF\n");
        }
        if ((a != 1) && (a != 2) && (a != 3)) {
            scanf("%*[^\n]");
            std::cout << "Invalid type! Try again: ";
        }
    }

    return a;
}