#ifndef KNIGHTTHROUGHGAME_CPP
#define	KNIGHTTHROUGHGAME_CPP

#include "KnightthroughGame.h"

namespace Knightthrough
{
    KnightthroughGame::KnightthroughGame(unsigned int bs) : Game(bs, 2)
    {
        this->reset();

        //add w and b players
        this->addPlayer("w");
        this->addPlayer("b");
    }

    KnightthroughGame::~KnightthroughGame()
    {
    }

    void KnightthroughGame::reset()
    {
        Generic::Game::reset();
        this->setRootState(new KnightthroughState(this, this->getBoardSize()));
        this->setCurrentState(this->getRootState());
    }
    
    MisereKnightthroughGame::MisereKnightthroughGame(unsigned int bs) : KnightthroughGame(bs)
    {
    }
    
    unsigned int MisereKnightthroughGame::getWinner(Generic::State* s)
    {
        return KnightthroughGame::getLoser(s);
    }

    unsigned int MisereKnightthroughGame::getLoser(Generic::State* s)
    {
        return KnightthroughGame::getWinner(s);
    }
}
#endif	/* KNIGHTTHROUGHGAME_CPP */
