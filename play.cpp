
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

bool printAndCheck(Game &g)
{
    goUpLines(9);

    cout << g << endl; 

    if(g.getStatus() != NEUTRAL)
    {
        cout << endl << "Player " << g.getStatus() << " won the game." << endl;
        return false;
    }
    else if(g.getMoves().empty())
    {
        cout << "There are no more moves left. It's a tie!" << endl;
        return false;
    }
    else
        return true;
}

void playHumanVSHuman()
{
    Game g;

    Human human;

    while(true)
    {
        if(!printAndCheck(g))
            return;

        int m = human.selectMove(g);

        g.makeMove(m);
        
        goUpLines(9);
    }
}

void playHumanVSCom(bool startHuman = true)
{
    Game g;

    Human human;

    PerfectPlayer com;

    int m;

    while(true)
    {
        if(!printAndCheck(g))
            return;

        if(startHuman)
            m = human.selectMove(g);
        else
            m = com.selectMove(g);

        g.makeMove(m);
        
        if(!printAndCheck(g))
            return;

        if(startHuman)
            m = com.selectMove(g);
        else
            m = human.selectMove(g);

        g.makeMove(m);
    }
}

/**
 * compile:
 * src="play.cpp agent.cpp minimax.cpp ticktacktoe.cpp"
 * opt="-std=c++2b -Wall -Werror -ferror-limit=1 -o ticktacktoe"
 * build="clang++ $opt $src"
 */
int main(int argc, char *argv[])
{
    srand(time(nullptr));

    char c = argv[1][0];

    switch(c)
    {
        case '0':
            playHumanVSCom();
            break;
        case '1':
            playHumanVSCom(false);
            break;
        default:
            playHumanVSHuman();
    }
}
