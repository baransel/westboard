#ifndef LNMCSDPLAYER_CPP
#define LNMCSDPLAYER_CPP

#include "LnmcsdPlayer.h"

namespace Lnmcsd
{
    LnmcsdPlayer::LnmcsdPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : LnmcsPlayer(n, g, mt, c, l)
    {
    }

    LnmcsdPlayer::LnmcsdPlayer(Generic::Game* g, double mt, double c, unsigned int l) : LnmcsPlayer("Lnmcsd", g, mt, c, l)
    {
    }
    
    unsigned int LnmcsdPlayer::mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker)
    {
        unsigned int length = 0;
        
        Generic::State* w = walker;
        //while(w->getId() != expandedNode->getReferenceState()->getId())
        while(w != expandedNode->getReferenceState())
        {
            length++;
            w = w->getParent();
        }
        
        expandedNode->addScore(this->getGoalScore(walker)/length);
        
        return length;
    }

}

#endif /* LNMCSDPLAYER_CPP */