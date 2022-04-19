#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <time.h>

using namespace std;

class Clock {
public:
    Clock() {}

    void tick() {
        this->start = clock();
    }

    double tock() {
        return (double(clock() - start) / (CLOCKS_PER_SEC));
    }

private:
    clock_t start;
};

#endif
