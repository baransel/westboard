#ifndef BREAKTHROUGHGAME_CPP
#define	BREAKTHROUGHGAME_CPP

#include "BreakthroughGame.h"

namespace Breakthrough
{
    BreakthroughGame::BreakthroughGame(unsigned int bs) : Game(bs, 2)
    {
        this->reset();

        //add w and b players
        this->addPlayer("w");
        this->addPlayer("b");
    }

    BreakthroughGame::~BreakthroughGame()
    {
    }

    void BreakthroughGame::reset()
    {
        Generic::Game::reset();
        this->setRootState(new BreakthroughState(this, this->getBoardSize()));
        this->setCurrentState(this->getRootState());
    }
    
    MisereBreakthroughGame::MisereBreakthroughGame(unsigned int bs) : BreakthroughGame(bs)
    {
    }
    
    unsigned int MisereBreakthroughGame::getWinner(Generic::State* s)
    {
        return BreakthroughGame::getLoser(s);
    }

    unsigned int MisereBreakthroughGame::getLoser(Generic::State* s)
    {
        return BreakthroughGame::getWinner(s);
    }
}
#endif	/* BREAKTHROUGHGAME_CPP */
