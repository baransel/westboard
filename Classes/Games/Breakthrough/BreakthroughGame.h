#ifndef BREAKTHROUGHGAME_H
#define	BREAKTHROUGHGAME_H

#include "../../Game.h"
#include "BreakthroughState.h"

namespace Breakthrough
{
    class BreakthroughGame : public Generic::Game
    {
    public:
        BreakthroughGame(unsigned int bs = 5);
        
        virtual ~BreakthroughGame();
        
        void reset();

    private:
    };
    
    class MisereBreakthroughGame : public BreakthroughGame
    {
    public:
        MisereBreakthroughGame(unsigned int bs = 5);
        
        unsigned int getWinner(Generic::State* s = NULL);
        
        unsigned int getLoser(Generic::State* s = NULL);
    };
}

#endif	/* BREAKTHROUGHGAME_H */

