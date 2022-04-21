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

    void randomizeOneQueenForRandom() {
        int randomColumn = rand() % this->board.size;

        for (int i = 0; i < this->board.size; i++)
            this->board[i][randomColumn] = 0;

        this->board[rand() % this->board.size][randomColumn] = QUEEN;
        this->board.calculateBoardQuality();
    }

    void randomizeOneQueenForParity() {
        int randomColumn = rand() % (this->board.size - 1);

        int iQueenPosition = this->getQueenPosition(randomColumn);
        int jQueenPosition = this->getQueenPosition(randomColumn + 1);

        this->board[iQueenPosition][randomColumn] = 0;
        this->board[jQueenPosition][randomColumn + 1] = 0;

        this->board[jQueenPosition][randomColumn] = 1;
        this->board[iQueenPosition][randomColumn + 1] = 1;

        this->board.calculateBoardQuality();
    }

    Board calculateNextStateForRandom() {
        Board optimizedBoard = this->board;
        int optimizedState = optimizedBoard.attacks;

        for (int j = 0; j < this->board.size; j++) {
            for (int i = 0; i < this->board.size; i++) {
                if (this->board[i][j] != QUEEN) {
                    int previousState = this->board.attacks;
                    int queenPosition = this->getQueenPosition(j);
                    this->board[queenPosition][j] = 0;
                    this->board[i][j] = QUEEN;

                    if (this->board.calculateBoardQuality() < optimizedBoard.attacks) {
                        optimizedBoard = this->board;
                        optimizedState = optimizedBoard.attacks;
                    }

                    this->board[i][j] = 0;
                    this->board[queenPosition][j] = QUEEN;
                    this->board.attacks = previousState;
                }
            }
        }

        this->board = optimizedBoard;
        this->board.attacks = optimizedState;
        return this->board;
    }

    Board calculateNextStateForParity() {
        Board optimizedBoard = this->board;
        int optimizedState = optimizedBoard.attacks;

        for (int i = 0; i < this->board.size - 1; i++) {
            
            int iQueenPosition = this->getQueenPosition(i);
            for (int j = i + 1; j < this->board.size; j++) {
                int jQueenPosition = this->getQueenPosition(j);
                int previousState = this->board.attacks;

                this->board[iQueenPosition][i] = 0;
                this->board[jQueenPosition][j] = 0;

                this->board[jQueenPosition][i] = 1;
                this->board[iQueenPosition][j] = 1;

                if (this->board.calculateBoardQuality() < optimizedBoard.attacks) {
                    optimizedBoard = this->board;
                    optimizedState = optimizedBoard.attacks;
                }

                this->board[iQueenPosition][i] = 1;
                this->board[jQueenPosition][j] = 1;

                this->board[jQueenPosition][i] = 0;
                this->board[iQueenPosition][j] = 0;

                this->board.attacks = previousState;
            }
        }

        this->board = optimizedBoard;
        this->board.attacks = optimizedState;
        return this->board;
    }

private:
    int getQueenPosition(int column) {
        for (int i = 0; i < this->board.size; i++)
            if (this->board[i][column] == QUEEN)
                return i;

        this->board.print();
        throw invalid_argument("getQueenPosition -> Column " + to_string(column) + " does not have a queen");
    }

};

#endif
