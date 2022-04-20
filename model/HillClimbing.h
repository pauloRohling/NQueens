#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H

#include <iostream>
#include <vector>

#include "Board.h"
#include "Constants.h"

using namespace std;

template<unsigned int NUMBER>
class HillClimbing {

private:
    Board board;

public:
    HillClimbing() {
        Board tempBoard(NUMBER);
        this->board = tempBoard;
    }

    Board getBoard() {
        return this->board;
    }

    void randomizeOneQueen() {
        int randomColumn = rand() % this->board.size;

        for (int i = 0; i < this->board.size; i++)
            this->board[i][randomColumn] = 0;

        this->board[rand() % this->board.size][randomColumn] = QUEEN;
        this->board.calculateBoardQuality();
    }

    Board calculateNextState() {
        Board optimizedBoard = this->board;

        for (int j = 0; j < this->board.size; j++) {
            for (int i = 0; i < this->board.size; i++) {
                if (this->board[i][j] != QUEEN) {
                    int previousState = this->board.attacks;

                    int queenPosition = this->changeQueenPositionOf(j);
                    this->board[i][j] = QUEEN;

                    // Verificando melhoria
                    if (this->board.calculateBoardQuality() < optimizedBoard.attacks)
                        optimizedBoard = this->board;

                    this->board[i][j] = 0;
                    this->board[queenPosition][j] = QUEEN;
                    this->board.attacks = previousState;
                }
            }
        }

        this->board = optimizedBoard;
        this->board.calculateBoardQuality();
        return this->board;
    }


private:
    int changeQueenPositionOf(int column) {
        int queenPosition;
        for (int k = 0; k < this->board.size; k++) {
            if (this->board[k][column] == QUEEN) {
                this->board[k][column] = 0;
                queenPosition = k;
            }
        }
        return queenPosition;
    }

};

#endif
