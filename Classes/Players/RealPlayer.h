#ifndef REALPLAYER_H
#define	REALPLAYER_H

#include "../Player.h"
#include "../Game.h"
#include <sys/ioctl.h>
#include "../../utf8/utf8.h"

namespace Real
{
    class RealPlayer : public Generic::Player
    {
    public:
        RealPlayer(std::string n, Generic::Game* g, unsigned int mt);

        RealPlayer(Generic::Game* g, unsigned int mt);

        ~RealPlayer();

        void move();
    private:

    };
}

#endif	/* REALPLAYER_H */

