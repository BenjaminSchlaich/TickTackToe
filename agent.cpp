
#include "agent.hpp"
#include "minimax.hpp"
#include "util.hpp"

int Human::selectMove(Game &g)
{
    cout << "Select a " << MAGENTA << "move" << RESET_COLOR << ": " << endl;

    size_t i;

    cin >> i;

    return i;
}

int PerfectPlayer::selectMove(Game &g)
{
    return minimaxMove(g);
}
