#ifndef NMCSDPODPLAYER_CPP
#define NMCSDPODPLAYER_CPP

#include "NmcsdPODPlayer.h"

namespace NmcsdPOD
{
    NmcsdPODPlayer::NmcsdPODPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : NmcsPODPlayer(n, g, mt, c, l)
    {
    }

    NmcsdPODPlayer::NmcsdPODPlayer(Generic::Game* g, double mt, double c, unsigned int l) : NmcsPODPlayer("NmcsdPOD", g, mt, c, l)
    {
    }
    
    unsigned int NmcsdPODPlayer::mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker)
    {
        unsigned int length = 0;
        
        Generic::State* w = walker;
        while(w->getId() != expandedNode->getReferenceState()->getId())
        {
            length++;
            w = w->getParent();
        }
        
        expandedNode->addScore(this->getGoalScore(walker)/length);
        
        return length;
    }
}

#endif /* NMCSDPODPLAYER_CPP */