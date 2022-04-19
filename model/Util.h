#ifndef UTIL_H
#define UTIL_H

int fat(int number) {
    return (number > 1) ? fat(number - 1) * number : 1;
}

int combination2(int number) {
    return fat(number) / (2 * (fat(number - 2)));
}

void cleanScreen() {
    system("cls");
}

void pauseScreen() {
    system("pause");
}

#endif