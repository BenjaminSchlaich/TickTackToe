
#pragma once

#include "ticktacktoe.hpp"

#include <iostream>
#include <random>
#include <AIToolbox/MDP/Algorithms/QLearning.hpp>

class Agent
{
    public:

    virtual int selectMove(Game &g) = 0;
};

class Human: Agent
{
    public:

    int selectMove(Game &g);
};

class PerfectPlayer: Agent
{
    public:

    int selectMove(Game &g);
};

class RandomPlayer: Agent
{
    public:

    int selectMove(Game &g);

    private:

    std::random_device rd;
    std::mt19937_64 prng = std::mt19937_64(rd());
};

class QLearningAgent : Agent
{
    public:

    QLearningAgent(int trainingEpisodes = 100000);

    int selectMove(Game &g);

    private:

    AIToolbox::MDP::QLearning qlLearner = AIToolbox::MDP::QLearning(19683, 9, 0.99, 0.1);
};
