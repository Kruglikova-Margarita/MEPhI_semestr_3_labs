#include <iostream>

void printMenu() {
    printf("\033[1;96m\nMenu\033[0m\n");
    printf("\033[1;96m 1 - allocate memory for a new object\033[0m\n");
    printf("\033[1;96m 2 - delete an object\033[0m\n");
    printf("\033[1;96m-1 - end the program\033[0m\n");
}

void printMenuArrayOrNot() {
    printf("\033[1;94m\nYou can allocate memory for:\033[0m\n");
    printf("\033[1;94m1 - single object\033[0m\n");
    printf("\033[1;94m2 - array\033[0m\n");
}

void printMenuOfTypes() {
    printf("\033[1;94m\nYou can allocate object(s) of this types:\033[0m\n");
    printf("\033[1;94m1 - char   (1 byte)\033[0m\n");
    printf("\033[1;94m2 - int    (4 bytes)\033[0m\n");
    printf("\033[1;94m3 - double (8 bytes)\033[0m\n");
}
