
#pragma once

#include <vector>
#include <iostream>

/*
    The STATUS can have two meanings:
        1. For a value of Game.field[i][j], this is the player who occupies the field, or initially neutral
        2. For Game.getStatus(), this is the winner of the game, or neutral if it is unfinished yet.
*/
enum STATUS
{
    NEUTRAL = 0,
    CROSS = 1,
    CIRCLE = 2
};

class Game
{
    friend std::ostream &operator<<(std::ostream &os, Game &g);

    public:

    Game();

    // returns a list of moves that can be made.
    std::vector<int> getMoves();

    // returns whether the game is running or cross/circle won.
    STATUS getStatus();

    // returns whose turn it is (CROSS/CIRCLE)
    STATUS getTurn();

    // make the move getMoves().at(moveIndex)
    void makeMove(int moveIndex);

    // undo the last move
    void undoMove();

    private:

    int count;
    char field[9];
    int moves[9];
};

std::ostream &operator<<(std::ostream &os, STATUS s);

std::ostream &operator<<(std::ostream &os, Game &g);
