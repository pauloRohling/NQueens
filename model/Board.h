#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <windows.h>

#include "Util.h"

using namespace std;

class Board {

private:
    vector<vector<bool>> board;

public:
    unsigned int size;
    unsigned int attacks;

    Board() { }

    Board(unsigned int N) {
        this->size = N;
        this->reset();
        this->attacks = this->calculateBoardQuality();
    }

    ~Board() {
        this->board.clear();
    }

    int calculateBoardQuality() {
        this->attacks = this->getLineOrColumnAttacks() + this->getDiagonalAttacks() + 
            this->getReverseDiagonalAttacks(this->board);
        return this->attacks;
    }

    void reset() {
        this->board.clear();
        vector<bool> line(this->size, false);
        vector<vector<bool>> matrix(this->size, line);
        this->board = matrix;
        this->placeQueens();
    }

    void placeQueens() {
        for (int i = 0; i < this->size; i++)
            this->board[i][i] = QUEEN;
    }

    void print(const string title = "BOARD") {
        cout << title << endl << "ATTACKS: " << this->attacks << endl;

        for (int i = 0; i < this->size; i++) {
            for (int j = 0; j < this->size; j++) {
                if (this->board[i][j] == QUEEN) {
                    setConsoleColor(BLUE);
                    cout << this->board[i][j];
                    setConsoleColor(WHITE);
                    cout << " ";
                } else {
                    cout << this->board[i][j] << " ";
                }
            }
            cout << endl;
        }
        setConsoleColor(WHITE);
        cout << endl << endl;
    }

    typename vector<vector<bool>>::reference operator[](int i) {
        return this->board[i];
    }

    typename vector<vector<bool>>::const_reference operator[](int i) const {
        return this->board[i];
    }

private:
    int getLineOrColumnAttacks() {
        int attacks = 0;

        for (int i = 0; i < this->size; i++) {
            int queens = 0;
            for (int j = 0; j < this->size; j++)
                if (this->board[i][j] == QUEEN)
                    queens++;
            attacks += combination2(queens);

            queens = 0;
            for (int j = 0; j < this->size; j++)
                if (this->board[j][i] == QUEEN)
                    queens++;
            attacks += combination2(queens);
        }

        return attacks;
    }

    int getReverseDiagonalAttacks(vector<vector<bool>> board) {
        int attacks = 0;
        vector<vector<bool>> diagonals((2 * this->size) - 1);

        for (int i = 0; i < this->size; i++)
            for (int j = 0; j < this->size; j++)
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

    int getDiagonalAttacks() {
        vector<bool> line(this->size, false);
        vector<vector<bool>> newBoard(this->size, line);

        for (int i = 0; i < this->size; i++)
            for (int j = this->size - 1; j >= 0; j--)
                newBoard[i][this->size - j - 1] = this->board[i][j];

        return getReverseDiagonalAttacks(newBoard);
    }

};

#endif
