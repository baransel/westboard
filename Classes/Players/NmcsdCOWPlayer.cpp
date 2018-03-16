#ifndef NMCSDCOWPLAYER_CPP
#define NMCSDCOWPLAYER_CPP

#include "NmcsdCOWPlayer.h"

namespace NmcsdCOW
{
    NmcsdCOWPlayer::NmcsdCOWPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : NmcsCOWPlayer(n, g, mt, c, l)
    {
    }

    NmcsdCOWPlayer::NmcsdCOWPlayer(Generic::Game* g, double mt, double c, unsigned int l) : NmcsCOWPlayer("NmcsdCOW", g, mt, c, l)
    {
    }
    
    unsigned int NmcsdCOWPlayer::mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker)
    {
        unsigned int length = 0;
        
        Generic::State* w = walker;
        while(w->getId() != expandedNode->getReferenceState()->getId())
        {
            length++;
            w = w->getParent();
        }
        
        expandedNode->addScore(this->getGoalScore(walker)/length);
        
        if(this->getGoalScore(walker) == Mcts::__winScore)
            return 1;
        else
            return 0;
    }
    
    
}

#endif /* NMCSDCOWPLAYER_CPP */