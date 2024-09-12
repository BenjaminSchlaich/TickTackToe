
#pragma once

#include "ticktacktoe.hpp"

#include <iostream>

using namespace std;

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
