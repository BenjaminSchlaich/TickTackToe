
#include "minimax.hpp"

#include <random>

// first int: the index of the move. second int: the value of the move. max: the player to be maximised
int minimax(Game &g, STATUS max, bool start = true)
{
    STATUS status = g.getStatus();

    if(status != NEUTRAL)
        return status == max ? 1 : -1;

    auto moves = g.getMoves();

    if(moves.empty())
        return 0;

    bool maxNow = g.getTurn() == max;

    int best = maxNow ? -1 : 1;
    int bestMove = 0;

    int k = 1;

    for(int move: moves)
    {
        g.makeMove(move);

        int value = minimax(g, max, false);

        g.undoMove();

        if((maxNow && value > best) || (!maxNow && value < best))
        {
            best = value;
            bestMove = move;
        }

        if(((maxNow && value == best) || (!maxNow && value < best)) && (rand() % k++ == 0))
        {
            best = value;
            bestMove = move;
        }
    }

    if(start)
        return bestMove;
    else
        return best;
}

int minimaxMove(Game &g)
{
    return minimax(g, g.getTurn());
}
