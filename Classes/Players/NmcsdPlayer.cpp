#ifndef NMCSDPLAYER_CPP
#define NMCSDPLAYER_CPP

#include "NmcsdPlayer.h"

namespace Nmcsd
{
    NmcsdPlayer::NmcsdPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : NmcsPlayer(n, g, mt, c, l)
    {
    }

    NmcsdPlayer::NmcsdPlayer(Generic::Game* g, double mt, double c, unsigned int l) : NmcsPlayer("Nmcsd", g, mt, c, l)
    {
    }
    
    unsigned int NmcsdPlayer::mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker)
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

#endif /* NMCSDPLAYER_CPP */