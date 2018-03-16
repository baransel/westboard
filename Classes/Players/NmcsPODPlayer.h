#ifndef NMCSPODPLAYER_H
#define NMCSPODPLAYER_H

#include "NmcsPlayer.h"

namespace NmcsPOD
{
    class NmcsPODPlayer : public Nmcs::NmcsPlayer
    {
    public:
        NmcsPODPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        NmcsPODPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
    protected:
        
        virtual Generic::State* mctsSimulation(Generic::State* walker, unsigned int max);
        
        virtual unsigned int mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker);
        
        virtual unsigned int nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level, unsigned int max = -1);
    };
}

#endif /* NMCSPODPLAYER_H */

