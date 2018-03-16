#ifndef NMCSDPLAYER_H
#define NMCSDPLAYER_H

#include "NmcsPlayer.h"

namespace Nmcsd
{
    class NmcsdPlayer : public Nmcs::NmcsPlayer
    {
    public:
        NmcsdPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        NmcsdPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
    protected:
        
        virtual unsigned int mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker);
        
    };
}

#endif /* NMCSDPLAYER_H */

