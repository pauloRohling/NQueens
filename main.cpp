#include <iostream>
#include <vector>
#include <time.h>

#include "model/Board.h"
#include "model/Util.h"
#include "model/Clock.h"

using namespace std;

void randomizeOneQueen(vector<vector<bool>> &board) {
    int randomColumn = rand() % 8;

    for (int i = 0; i < N; i++)
        board[i][randomColumn] = 0;

    board[rand() % 8][randomColumn] = QUEEN;
}

int getLineOrColumnAttacks(const vector<vector<bool>> &board) {
    int attacks = 0;

    for (int i = 0; i < N; i++) {
        int queens = 0;
        for (int j = 0; j < N; j++)
            if (board[i][j] == QUEEN)
                queens++;
        attacks += combination2(queens);

        queens = 0;
        for (int j = 0; j < N; j++)
            if (board[j][i] == QUEEN)
                queens++;
        attacks += combination2(queens);
    }

    return attacks;
}

int getReverseDiagonalAttacks(const vector<vector<bool>> &board) {
    int attacks = 0;
    vector<vector<bool>> diagonals((2 * N) - 1);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            diagonals[i + j].push_back(board[j][i]);

    for (int i = 0; i < diagonals.size(); i++) {
        int queens = 0;
        for (int j = 0; j < diagonals[i].size(); j++)
            if (diagonals[i][j] == QUEEN)
                queens++;
        attacks += combination2(queens);
    }

    return attacks;
}

int getDiagonalAttacks(const vector<vector<bool>> &board) {
    vector<bool> line(N, 0);
    vector<vector<bool>> newBoard(N, line);

    for (int i = 0; i < N; i++)
        for (int j = N - 1; j >= 0; j--)
            newBoard[i][N - j - 1] = board[i][j];

    return getReverseDiagonalAttacks(newBoard);
}

int calculateQualityOfState(const vector<vector<bool>> &board) {
    return getLineOrColumnAttacks(board) + getDiagonalAttacks(board) + getReverseDiagonalAttacks(board);
}

vector<vector<bool>> calculateNextState(vector<vector<bool>> board) {
    int optimizedState = calculateQualityOfState(board);
    vector<vector<bool>> optimizedBoard = board;

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (board[i][j] != QUEEN) {
                // Zerando a rainha nesta coluna
                int queenPosition;

                for (int k = 0; k < N; k++) {
                    if (board[k][j] == QUEEN) {
                        board[k][j] = 0;
                        queenPosition = k;
                    }
                }

                // Verificando melhoria
                board[i][j] = QUEEN;
                int newState = calculateQualityOfState(board);

                if (newState < optimizedState) {
                    optimizedBoard = board;
                    optimizedState = newState;
                }

                board[i][j] = 0;
                board[queenPosition][j] = QUEEN;
            }
        }
    }

    return optimizedBoard;
}


int main() {
    // 1650384373
    int seed = time(nullptr); 
    srand(seed);
    cleanScreen();

    Clock* clock = new Clock();
    clock->tick();

    vector<vector<bool>> board = generateNewBoard();
    int iterations = 0;

    // Initial State
    int state = calculateQualityOfState(board), newState;
    cout << "INITIAL BOARD" << endl;
    cout << "ATTACKS: " << state << endl;
    printBoard(board);
    cout << "---------------" << endl << endl;

    do {
        board = calculateNextState(board);
        newState = calculateQualityOfState(board);

        if (newState == 0) {
            cout << "---------------" << endl << endl;
            cout << "SOLUTION BOARD" << endl;
            cout << "ATTACKS: " << newState << endl;
            printBoard(board);
            break;
        } else if (state == newState) {
            randomizeOneQueen(board);
        } else {
            cout << "UPDATED BOARD" << endl;
            cout << "ATTACKS: " << newState << endl;
            printBoard(board);
        }

        state = newState;
        iterations++;

    } while (true);
    
    cout << "TIME SPENT: " << clock->tock() << endl;
    cout << "ITERATIONS: " << iterations << endl;
    cout << "SEED: " << seed;

    deleteBoard(board);

    cout << endl << endl;
    pauseScreen();
    return 0;
}
