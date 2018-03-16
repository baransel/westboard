#ifndef NMCSDPODPLAYER_H
#define NMCSDPODPLAYER_H

#include "NmcsPODPlayer.h"

namespace NmcsdPOD
{
    class NmcsdPODPlayer : public NmcsPOD::NmcsPODPlayer
    {
    public:
        NmcsdPODPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        NmcsdPODPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
    protected:
        
        virtual unsigned int mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker);
        
    };
}

#endif /* NMCSDPODPLAYER_H */

