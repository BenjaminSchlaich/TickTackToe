
#include "agent.hpp"
#include "minimax.hpp"

int Human::selectMove(Game &g)
{
    auto ps = g.getMoves();

    cout << "Select a move from the following: " << endl;

    int moveIndex = 0;

    for(auto &p: ps)
        cout << '[' << moveIndex++ << ": " << p << ']';

    cout << endl << "(enter the index of your chosen move:) ";

    size_t i;

    cin >> i;

    return i;
}

int PerfectPlayer::selectMove(Game &g)
{
    return minimaxMove(g);
}
