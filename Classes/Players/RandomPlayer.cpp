#ifndef RANDOMPLAYER_CPP
#define	RANDOMPLAYER_CPP

#include "RandomPlayer.h"

namespace Random
{
    RandomPlayer::RandomPlayer(std::string n, Generic::Game* g, unsigned int mt) : Generic::Player(n, g, mt)
    {
        timeval t1;
        gettimeofday(&t1,NULL);
        srand(t1.tv_usec * t1.tv_sec);
    }

    RandomPlayer::RandomPlayer(Generic::Game* g, unsigned int mt) : Generic::Player("Random", g, mt)
    {
        timeval t1;
        gettimeofday(&t1,NULL);
        srand(t1.tv_usec * t1.tv_sec);
    }

    RandomPlayer::~RandomPlayer()
    {
    }

    void RandomPlayer::move()
    {
        if(this->getSide() == this->getGame()->getTurn())
        {
            //it should be expanded, but check it anyway
            this->getGame()->getCurrentState()->expand();

            //go to next state by random
            this->getGame()->setCurrentState(
                this->getGame()->getCurrentState()->getChild(
                    rand() % this->getGame()->getCurrentState()->getCountOfChildren()
                )
            );

            //expand it
            this->getGame()->getCurrentState()->expand();
        }
    }
}

#endif	/* RANDOMPLAYER_CPP */