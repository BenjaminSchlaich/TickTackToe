
#include "ticktacktoe.hpp"

#include "agent.hpp"

using namespace std;

void goUpLines(int lines)
{
    while(lines-- > 0)
        cout << "\x1b[2K" << "\x1b[A";    
}

void clearScreen()
{
    cout << "\x1b[2J";
}

/**
 * compile:
 * src="play.cpp agent.cpp minimax.cpp ticktacktoe.cpp"
 * opt="-std=c++2b -Wall -Werror -ferror-limit=1"
 * build="clang++ $opt $src"
 */
int main()
{
    Game g;

    Human human;

    PerfectPlayer com;

    while(true)
    {
        // clearScreen();

        cout << "Status of the game:" << endl << g << endl; 

        if(g.getStatus() != NEUTRAL)
            break;
        else if(g.getMoves().empty())
        {
            cout << "There are no more moves left. It's a tie!" << endl;
            return 0;
        }

        int m = human.selectMove(g);

        g.makeMove(m);

        m = com.selectMove(g);

        g.makeMove(m);

        goUpLines(11);
    }

    cout << endl << "Player " << g.getStatus() << " won the game." << endl;

    return 0;
}
