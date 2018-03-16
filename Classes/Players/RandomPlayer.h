#ifndef RANDOMPLAYER_H
#define	RANDOMPLAYER_H

#include "../Player.h"
#include <sys/time.h>
#include <cstdlib>

namespace Random
{
    class RandomPlayer : public Generic::Player
    {
    public:
        RandomPlayer(std::string n, Generic::Game* g, unsigned int mt);

        RandomPlayer(Generic::Game* g, unsigned int mt);

        virtual ~RandomPlayer();

        void move();

    private:

    };
}

#endif	/* RANDOMPLAYER_H */

