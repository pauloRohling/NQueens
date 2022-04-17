#ifndef UTIL_H
#define UTIL_H

int fat(int number) {
    if (number > 1)
        return fat(number - 1) * number;
    return 1;
}

int combination2(int number) {
    return fat(number) / (2 * (fat(number - 2)));
}

void cleanScreen() {
    system("cls");
}

#endif