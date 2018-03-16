#ifndef NMCSCOWPLAYER_H
#define NMCSCOWPLAYER_H

#include "NmcsPlayer.h"

namespace NmcsCOW
{
    class NmcsCOWPlayer : public Nmcs::NmcsPlayer
    {
    public:
        NmcsCOWPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        NmcsCOWPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
    protected:
        
        virtual unsigned int mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker);
        
        virtual unsigned int nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level);
    };
}

#endif /* NMCSCOWPLAYER_H */

