#ifndef functionsForTests_h
#define functionsForTests_h

int mapFunction(int el) {
    return (2 * el);
}

bool whereFunction(int el) {
    if (el % 2 == 0) return true;
    return false;
}

int reduceFunction(int a, int b) {
    return (a + b);
}

#endif