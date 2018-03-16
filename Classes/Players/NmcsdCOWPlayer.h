#ifndef NMCSDCOWPLAYER_H
#define NMCSDCOWPLAYER_H

#include "NmcsCOWPlayer.h"

namespace NmcsdCOW
{
    class NmcsdCOWPlayer : public NmcsCOW::NmcsCOWPlayer
    {
    public:
        NmcsdCOWPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        NmcsdCOWPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
    protected:
        
        virtual unsigned int mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker);
    };
}

#endif /* NMCSDCOWPLAYER_H */

