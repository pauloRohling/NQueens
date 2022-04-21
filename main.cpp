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

int main() {
    cleanScreen();

    Clock clock;
    int seed = randSeed(1); // 1650384373
    stringstream logFile;
    logFile << "ID;TIME;ITERATIONS;IMPLEMENTATION" << "\n";

    for (int implementation = RANDOM; implementation <= PARITY; implementation++) {
        cout << "Using implementation " << implementation + 1 << ". Please wait..." << endl;
        for (int simulation = 0; simulation < SIMULATIONS; simulation++) {
            clock.tick();

            HillClimbing<8> hillClimbing;
            Board board = hillClimbing.getBoard();
            int iterations, newState, state = board.attacks;

            for (iterations = 0; true; iterations++) {
                board = (implementation == RANDOM) ? hillClimbing.calculateNextStateForRandom() : hillClimbing.calculateNextStateForParity();
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

    return 0;
}



// int main() {
//     cleanScreen();

//     Clock clock;
//     int seed = randSeed(1); // 1650384373
//     stringstream logFile;
//     logFile << "ID;SEED;TIME;ITERATIONS" << "\n";

//     for (int i = 0; i < SIMULATIONS; i++) {
//         clock.tick();

//         HillClimbing<8> hillClimbing;
//         Board board = hillClimbing.getBoard();
//         int iterations, newState, state = board.attacks;

//         board.print("INITIAL BOARD");

//         for (iterations = 0; true; iterations++) {
//             board = hillClimbing.calculateNextState2();
//             newState = board.attacks;

//             if (newState == 0) {
//                 board.print("SOLUTION BOARD");
//                 break;
//             } else if (state == newState) {
//                 hillClimbing.randomizeOneQueen();
//             } else {
//                 board.print("UPDATED BOARD");
//             }

//             state = newState;
//         };

//         double endTime = clock.tock();
        
//         cout << "SEED: " << seed << endl;
//         cout << "TIME SPENT: " << endTime << endl;
//         cout << "ITERATIONS: " << iterations << endl;
//         cout << endl << endl;

//         logFile << ID << ";" << seed << ";" << endTime << ";" << iterations << "\n";
//     }

//     createOutputFile(logFile.str(), "log" + to_string(ID));
    
//     pauseScreen();
//     return 0;
// }