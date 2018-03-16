#ifndef SIMULATION_H
#define	SIMULATION_H

#include "Games/TicTacToe/TicTacToeGame.h"
#include "Games/Breakthrough/BreakthroughGame.h"
#include "Games/Knightthrough/KnightthroughGame.h"
#include "Players/RandomPlayer.h"
#include "Players/RealPlayer.h"
#include "Players/MctsPlayer.h"
#include "Players/MctsMRPlayer.h"
#include "Players/NmcsPlayer.h"
#include "Players/NmcsdPlayer.h"
#include "Players/NmcsCOWPlayer.h"
#include "Players/NmcsPODPlayer.h"
#include "Players/NmcsdCOWPlayer.h"
#include "Players/NmcsdPODPlayer.h"
#include "Players/LnmcsPlayer.h"
#include "Players/LnmcsdPlayer.h"

class Simulation
{
public:
    Simulation(Generic::Game* g);
    
    Generic::Game* getGame();
    
    void setRepeatCount(unsigned int r);
    
    unsigned int getRepeatCount();
    
    void setVerbose(bool v = true);
    
    bool getVerbose();
    
    void addPlayer(Generic::Player* p);
    
    bool run();
    
    void printStatistics();
    
    virtual ~Simulation();
    
private:
    unsigned int repeatCount;
    Generic::Game* game;
    std::vector<Generic::Player*> players;
    bool verbose;
    
    void swapSides();
};

#endif	/* SIMULATION_H */