#ifndef LNMCSDPLAYER_H
#define LNMCSDPLAYER_H

#include "LnmcsPlayer.h"

namespace Lnmcsd
{
    class LnmcsdPlayer : public Lnmcs::LnmcsPlayer
    {
    public:
        LnmcsdPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        LnmcsdPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
    protected:
        
        virtual unsigned int mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker);
        
    };
}

#endif /* LNMCSDPLAYER_H */

