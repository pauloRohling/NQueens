#include <iostream>
#include <vector>
#include <time.h>

#include "model/Board.h"
#include "model/Util.h"
#include "model/Clock.h"
#include "model/HillClimbing.h"

using namespace std;

int main() {
    cleanScreen();

    int seed = randSeed(); // 1650384373

    Clock clock;

    HillClimbing<8> hillClimbing;
    Board board = hillClimbing.getBoard();
    int iterations, newState, state = board.attacks;

    board.print("INITIAL BOARD");
    cout << "---------------" << endl << endl;

    for (iterations = 0; true; iterations++) {
        board = hillClimbing.calculateNextState();
        newState = board.attacks;

        if (newState == 0) {
            cout << "---------------" << endl << endl;
            board.print("SOLUTION BOARD");
            break;
        } else if (state == newState) {
            hillClimbing.randomizeOneQueen();
        } else {
            board.print("UPDATED BOARD");
        }

        state = newState;
    };
    
    cout << "TIME SPENT: " << clock.tock() << endl;
    cout << "ITERATIONS: " << iterations << endl;
    cout << "SEED: " << seed;

    cout << endl << endl;
    pauseScreen();
    return 0;
}
