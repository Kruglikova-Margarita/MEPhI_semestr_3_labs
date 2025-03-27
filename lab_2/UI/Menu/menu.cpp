#include <iostream>

using namespace std;

void printMenuOfCreatingSequence() {
    cout << "You can:\n";
    cout << "1 - enter the sequence manually\n";
    cout << "2 - generate a sequence in a chosen range\n";
}

void printMenuOfActions() {
    cout << "You can:\n";
    cout << "1 - sort sequence by BUBBLE sorting\n";
    cout << "2 - sort sequence by SHAKER sorting\n";
    cout << "3 - sort sequence by INSERTION sorting\n";
    cout << "4 - sort sequence by BINARY INSERTION sorting\n";
    cout << "5 - sort sequence by SELECTION sorting\n";
    cout << "6 - sort sequence by MERGE sorting\n";
    cout << "7 - sort sequence by SHELL sorting\n";
    cout << "8 - sort sequence by QUICK sorting\n";
    cout << "9 - append element to the sequence\n";
    cout << "10 - delete current sequence to sort and create new\n";
    cout << "0 - print menu\n";
    cout << "-1 - finish program\n";
}