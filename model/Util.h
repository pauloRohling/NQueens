#ifndef UTIL_H
#define UTIL_H

#include "Constants.h"
#include <time.h>
#include <windows.h>
#include <random>

int fat(int number) {
    return (number > 1) ? fat(number - 1) * number : 1;
}

int combination2(int number) {
    return fat(number) / (2 * (fat(number - 2)));
}

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