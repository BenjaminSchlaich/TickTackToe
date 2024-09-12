
#include "minimax.hpp"

// first int: the index of the move. second int: the value of the move. max: the player to be maximised
int minimax(Game &g, STATUS max, int move = -1)
{
    if(move >= 0)
        g.makeMove(move);

    STATUS s = g.getStatus();

    if(s != NEUTRAL)
        return s == max ? 1 : -1;

    auto mvs = g.getMoves();

    if(mvs.size() == 0)
    {
        g.undoMove();

        return  0;
    }
    
    bool isMaxTurn = g.getTurn() == max;
    
    int best = isMaxTurn ? -1 : 1;
    int mv = -1;

    for(int i=0; i<mvs.size(); i++)
    {
        int value = minimax(g, max, i);

        if((isMaxTurn && value > best) || (!isMaxTurn && value < best))
        {
            best = value;
            mv = i;
        }
    }

    if(move >= 0)
    {
        g.undoMove();
        return best;
    }
    else
        return mv;
}

int minimaxMove(Game &g)
{
    return minimax(g, g.getTurn());
}
