#ifndef NMCSCOWPLAYER_CPP
#define NMCSCOWPLAYER_CPP

#include "NmcsCOWPlayer.h"

namespace NmcsCOW
{
    NmcsCOWPlayer::NmcsCOWPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : NmcsPlayer(n, g, mt, c, l)
    {
    }

    NmcsCOWPlayer::NmcsCOWPlayer(Generic::Game* g, double mt, double c, unsigned int l) : NmcsPlayer("NmcsCOW", g, mt, c, l)
    {
    }
    
    unsigned int NmcsCOWPlayer::mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker)
    {
        Generic::State* w = walker;
        while(w->getId() != expandedNode->getReferenceState()->getId())
        {
            w = w->getParent();
        }
        
        expandedNode->addScore(this->getGoalScore(walker));
        
        if(this->getGoalScore(walker) == Mcts::__winScore)
            return 1;
        else
            return 0;
    }
    
    unsigned int NmcsCOWPlayer::nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level)
    {
        this->checkTime();
        walker->expand();
        
        if(level == 0)
        {
            walker = this->mctsSimulation(walker);
            
            this->checkTime();
            
            
            return this->mctsBackPropagation(expandedNode, walker);
        }
        else if(walker->isTerminal())
        {
            return this->mctsBackPropagation(expandedNode, walker);
        }
        else
        {
            unsigned int ret = 0;
            unsigned int tmpRet = 0;
            for(unsigned int i=0; i < walker->getCountOfChildren(); i++)
            {
                this->checkTime();
                tmpRet = this->nestedSimulation(expandedNode,walker->getChild(i),level-1);
                if( tmpRet == 1)
                {
                    ret = tmpRet;
                    break;
                }
            }
            return ret;
        }
    }
}

#endif /* NMCSCOWPLAYER_CPP */