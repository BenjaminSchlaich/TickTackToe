
#include "agent.hpp"
#include "minimax.hpp"
#include "util.hpp"

#include <AIToolbox/MDP/Policies/QGreedyPolicy.hpp>
#include <AIToolbox/MDP/Policies/EpsilonPolicy.hpp>

#include <algorithm>

using namespace std;
using namespace AIToolbox::MDP;

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

QLearningAgent::QLearningAgent(int trainingEpisodes)
{
    QGreedyPolicy gPolicy(qlLearner.getQFunction());

    EpsilonPolicy ePolicy(gPolicy, 0.1);

    Game g;

    size_t start = gameToState(g);

    std::cout << "Starting training...\n";

    RandomPlayer perfectAgent;

    size_t s, a;

    int percent = trainingEpisodes / 100;
    int progress = 0;
    
    for ( int episode = 0; episode < trainingEpisodes; ++episode )
    {
        g = Game();
        s = start;
        
        for ( int i = 0; i < 10; ++i ) {
            // Obtain an action for this state (10% random, 90% what we think is
            // best to do given the current QFunction).
            a = ePolicy.sampleAction(s);

            auto moves = g.getMoves();

            // if the proposed move is invalid, punish and abort.
            if(find(moves.begin(), moves.end(), a) == moves.end())
            {
                qlLearner.stepUpdateQ(s, a, s, -10);
                break;
            }
            
            // CONSIDER OUR OWN MOVE
            g.makeMove(a);

            STATUS status = g.getStatus();

            double rew;

            if(status == CROSS)
                rew = 1;
            else if(status == CIRCLE)
                rew = -1;
            else
                rew = 0;
            
            int s1 = gameToState(g);

            // Pass the newly collected data to QLearning, to update the
            // QFunction and improve the agent's policies.
            qlLearner.stepUpdateQ( s, a, s1, rew );

            if(status == CROSS || status == CIRCLE || g.getMoves().empty())
                break;

            s = s1;


            // NOW CONSIDER THE OPPONENTS MOVE
            g.makeMove(perfectAgent.selectMove(g));
            
            status = g.getStatus();

            if(status == CROSS)
                rew = 1;
            else if(status == CIRCLE)
                rew = -1;
            else
                rew = 0;
            
            s1 = gameToState(g);

            // Pass the newly collected data to QLearning, to update the
            // QFunction and improve the agent's policies.
            qlLearner.stepUpdateQ( s, a, s1, rew );

            if(status == CROSS || status == CIRCLE || g.getMoves().empty())
                break;

            s = s1;
        }

        if(progress++ > percent)
        {
            cout << "*";
            progress = 0;
        }
    }

    std::cout << endl << "Training over!\n";

}

int QLearningAgent::selectMove(Game &g)
{
    QGreedyPolicy p(qlLearner.getQFunction());

    int sid = gameToState(g);

    return p.sampleAction(sid);
}

int RandomPlayer::selectMove(Game &g)
{
    auto &moves = g.getMoves();

    auto d = uniform_int_distribution<int>(0, moves.size()-1);

    int sample = d(prng);

    auto it = moves.begin();

    for(int i=0; i<sample; i++)
        it++;

    return *it;
}
