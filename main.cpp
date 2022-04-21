#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>

#include "model/Board.h"
#include "model/Util.h"
#include "model/Clock.h"
#include "model/HillClimbing.h"
#include "model/FileManager.h"

using namespace std;

void simulateParity() {
    Clock clock;

    cout << "Using PARITY implementation. Please wait..." << endl;
    clock.tick();

    HillClimbing<N> hillClimbing;
    Board board = hillClimbing.getBoard();
    int iterations, newState, state = board.attacks;

    board.print("INITIAL STATE");

    for (iterations = 0; true; iterations++) {
        board = hillClimbing.calculateNextStateForParity();

        board.print();

        newState = board.attacks;

        if (newState == 0) {
            board.print("SOLUTION");
            break;
        }
        if (state == newState) {
            hillClimbing.randomizeOneQueenForParity();
            hillClimbing.getBoard().print();
        }

        state = newState;
    };

    double endTime = clock.tock();

    cout << "TIME SPENT: " << endTime << endl;
    cout << "ITERATIONS: " << iterations << endl;

    cout << "Completed" << endl;
}

void simulateRandom() {
    Clock clock;

    cout << "Using RANDOM implementation. Please wait..." << endl;
    clock.tick();

    HillClimbing<N> hillClimbing;
    Board board = hillClimbing.getBoard();
    int iterations, newState, state = board.attacks;

    board.print("INITIAL STATE");

    for (iterations = 0; true; iterations++) {
        board = hillClimbing.calculateNextStateForRandom();

        board.print();

        newState = board.attacks;

        if (newState == 0) {
            board.print("SOLUTION");
            break;
        }
        if (state == newState) {
            hillClimbing.randomizeOneQueenForRandom();
            hillClimbing.getBoard().print();
        }

        state = newState;
    };

    double endTime = clock.tock();

    cout << "TIME SPENT: " << endTime << endl;
    cout << "ITERATIONS: " << iterations << endl;

    cout << "Completed" << endl;
}

void generateData() {
    Clock clock;
    stringstream logFile;
    logFile << "ID;TIME;ITERATIONS;IMPLEMENTATION" << "\n";

    for (int implementation = RANDOM; implementation <= PARITY; implementation++) {
        cout << "Using implementation " << implementation + 1 << ". Please wait..." << endl;
        for (int simulation = 0; simulation < SIMULATIONS; simulation++) {
            clock.tick();

            HillClimbing<N> hillClimbing;
            Board board = hillClimbing.getBoard();
            int iterations, newState, state = board.attacks;

            for (iterations = 0; true; iterations++) {
                if (implementation == RANDOM)
                    board = hillClimbing.calculateNextStateForRandom();
                else
                    board = hillClimbing.calculateNextStateForParity();
                    
                newState = board.attacks;

                if (newState == 0)
                    break;
                if (state == newState)
                    (implementation == RANDOM) ? hillClimbing.randomizeOneQueenForRandom() : hillClimbing.randomizeOneQueenForParity();

                state = newState;
            };

            double endTime = clock.tock();
            logFile << simulation << ";" << endTime << ";" << iterations << ";" << implementation << "\n";
        }
    }

    createOutputFile(logFile.str(), "log");

    cout << "Completed" << endl;
}

int main() {
    randSeed(1); // 1650384373
    cleanScreen();

    // generateData();
    simulateRandom();
    // simulateParity();

    return 0;
}