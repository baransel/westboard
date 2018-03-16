#ifndef KNIGHTTHROUGHGAME_H
#define	KNIGHTTHROUGHGAME_H

#include "../../Game.h"
#include "KnightthroughState.h"

namespace Knightthrough
{
    class KnightthroughGame : public Generic::Game
    {
    public:
        KnightthroughGame(unsigned int bs = 5);
        
        virtual ~KnightthroughGame();
        
        void reset();

    private:
    };
    
    class MisereKnightthroughGame : public KnightthroughGame
    {
    public:
        MisereKnightthroughGame(unsigned int bs = 5);
        
        unsigned int getWinner(Generic::State* s = NULL);
        
        unsigned int getLoser(Generic::State* s = NULL);
    };
}

#endif	/* KNIGHTTHROUGHGAME_H */

