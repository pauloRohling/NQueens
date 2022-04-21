#ifndef UTIL_H
#define UTIL_H

#include "Constants.h"
#include <time.h>
#include <windows.h>
#include <random>

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int randSeed(int seed = time(nullptr)) {
    srand(seed);
    return seed;
}

void cleanScreen() {
    system("cls");
}

void pauseScreen() {
    system("pause");
}

#endif