#ifndef NMCSPODPLAYER_CPP
#define NMCSPODPLAYER_CPP

#include "NmcsPODPlayer.h"

namespace NmcsPOD
{
    NmcsPODPlayer::NmcsPODPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : NmcsPlayer(n, g, mt, c, l)
    {
    }

    NmcsPODPlayer::NmcsPODPlayer(Generic::Game* g, double mt, double c, unsigned int l) : NmcsPlayer("NmcsPOD", g, mt, c, l)
    {
    }
    
    Generic::State* NmcsPODPlayer::mctsSimulation(Generic::State * walker, unsigned int max)
    {
        walker->expand();
        
        unsigned int length = 0;
        while(!walker->isTerminal())
        {
            if(length == max)
                return NULL;
            
            length++;
            this->checkTime();
            walker = walker->getChild(rand() % walker->getCountOfChildren());
            walker->expand();
        }
        
        return walker;
    }
    
    unsigned int NmcsPODPlayer::mctsBackPropagation(Mcts::Node* expandedNode, Generic::State* walker)
    {
        unsigned int length = 0;
        
        Generic::State* w = walker;
        while(w->getId() != expandedNode->getReferenceState()->getId())
        {
            length++;
            w = w->getParent();
        }
        
        expandedNode->addScore(this->getGoalScore(walker));
        
        return length;
    }
    
    unsigned int NmcsPODPlayer::nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level, unsigned int max)
    {
        this->checkTime();
        walker->expand();
        
        if(level == 0)
        {
            walker = this->mctsSimulation(walker, max);
            
            this->checkTime();
            
            return this->mctsBackPropagation(expandedNode, walker);
        }
        else if(walker->isTerminal())
        {
            return this->mctsBackPropagation(expandedNode, walker);
        }
        else
        {
            unsigned int ret = max;
            unsigned int tmpRet = 0;
            for(unsigned int i=0; i < walker->getCountOfChildren(); i++)
            {
                this->checkTime();
                tmpRet = this->nestedSimulation(expandedNode,walker->getChild(i),level-1, ret - 1);
                if( tmpRet < ret)
                {
                    ret = tmpRet;
                }
            }
            return ret;
        }
    }
}

#endif /* NMCSPODPLAYER_CPP */