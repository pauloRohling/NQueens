#include <iostream>
#include <vector>
#include <time.h>
#include "model/Board.h"
#include "model/Util.h"

using namespace std;

int getLineOrColumnAttacks(const vector<vector<int>> &board) {
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

int getReverseDiagonalAttacks(const vector<vector<int>> &board) {
    int attacks = 0;
    vector<vector<int>> diagonals((2 * N) - 1);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            diagonals[i + j].push_back(board[j][i]);
 
    for (int i = 0; i < diagonals.size(); i++) {
        int queens = 0;
        for (int j = 0; j < diagonals[i].size(); j++) {
            if (diagonals[i][j] == QUEEN)
                queens++;
        }
        attacks += combination2(queens);
    }
    return attacks;
}

int getDiagonalAttacks(const vector<vector<int>> &board) {
    vector<int> line(N, 0);
    vector<vector<int>> newBoard(N, line);

    for (int i = 0; i < N; i++)
        for (int j = N - 1; j >= 0; j--)
            newBoard[i][N - j - 1] = board[i][j];

    return getReverseDiagonalAttacks(newBoard);
}

int calculateState(const vector<vector<int>> &board) {
    return getLineOrColumnAttacks(board) + getDiagonalAttacks(board) + getReverseDiagonalAttacks(board);
}


vector<vector<int>> columnOptimization(vector<vector<int>> board) {
    int optimizedState = calculateState(board);
    vector<vector<int>> optimizedBoard = board;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[j][i] != QUEEN) {
                // Zerando a rainha nesta coluna
                int queenPosition;
                for (int k = 0; k < N; k++)
                    if (board[k][i] == QUEEN) {
                        board[k][i] = 0;
                        queenPosition = k;
                    }

                // Verificando melhoria
                board[j][i] = QUEEN;
                int newState = calculateState(board);
                if (newState < optimizedState) {
                    optimizedBoard = board;
                    optimizedState = newState;
                }
                board[j][i] = 0;
                board[queenPosition][i] = QUEEN;
            }
        }
    }

    return optimizedBoard;
}

void randomizeOneQueen(vector<vector<int>> &board) {
    int randomColumn = rand() % 8;
    for (int i = 0; i < N; i++)
        board[i][randomColumn] = 0;
    board[rand() % 8][randomColumn] = QUEEN;
}


int main() {
    srand(1);
    cleanScreen();
    vector<vector<int>> board = generateNewBoard();

    // Initial State
    int state = calculateState(board), newState;
    cout << "INITIAL BOARD" << endl;
    cout << "ATTACKS: " << state << endl;
    printBoard(board);
    cout << "----------------------------------------------------------" << endl << endl << endl;

    do {
        board = columnOptimization(board);
        newState = calculateState(board);

        if (newState == 0) {
            cout << endl << "----------------------------------------------------------" << endl;
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
    } while (true);

    deleteBoard(board);
    return 0;
}