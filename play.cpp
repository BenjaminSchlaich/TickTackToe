
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
    goUpLines(100);
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

void playHumanVSQL(bool startHuman = true)
{
    Game g;

    Human human;

    QLearningAgent com;

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

void playHumanVSRandom(bool startHuman = true)
{
    Game g;

    Human human;

    RandomPlayer com;

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
 * inc="-I/Users/benjaminschlaich/Coding/C++/Libraries/AI-Toolbox-master/include -I/Users/benjaminschlaich/Coding/C++/Libraries/eigen-3.4.0 -L/Users/benjaminschlaich/Coding/C++/Libraries/AI-Toolbox-master/build"
 * opt="-std=c++2b -Wall -ferror-limit=1 -lAIToolboxMDP -o ticktacktoe"
 * build="clang++ $opt $inc $src"
 */
int main(int argc, char *argv[])
{
    srand(time(nullptr));

    char c = argv[1][0];

    while(true)
    {
        clearScreen();

        switch(c)
        {
            case '0':
                playHumanVSHuman();
                break;
            case '1':
                playHumanVSCom();
                break;
            case '2':
                playHumanVSCom(false);
                break;
            case '3':
                playHumanVSQL(false);
                break;
            case '4':
                playHumanVSRandom();
            default:
                return 0;
        }

        cout << "press any key to continue playing..." << endl;

        char c;

        cin >> c;
    }
}
