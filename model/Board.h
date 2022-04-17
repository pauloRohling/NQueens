#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <random>
#include <windows.h>
#include "Constants.h"

using namespace std;

void randomizeQueens(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++)
        board[rand() % 8][i] = QUEEN;
}

vector<vector<int>> generateNewBoard() {
    vector<int> line(N, 0);
    vector<vector<int>> board(N, line);
    randomizeQueens(board);
    return board;
}

void deleteBoard(vector<vector<int>> &board) {
    board.clear();
}

void printBoard(const vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == QUEEN) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 17);
                cout << board[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << "\t";
            } else {
                cout << board[i][j] << "\t";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << endl;
}

#endif