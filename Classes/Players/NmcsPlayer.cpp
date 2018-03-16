#ifndef NMCSPLAYER_CPP
#define NMCSPLAYER_CPP

#include "NmcsPlayer.h"

namespace Nmcs
{
    NmcsPlayer::NmcsPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : MctsPlayer(n, g, mt, c)
    {
        this->setLevel(l);
    }

    NmcsPlayer::NmcsPlayer(Generic::Game* g, double mt, double c, unsigned int l) : MctsPlayer("Nmcs", g, mt, c)
    {
        this->setLevel(l);
    }
    
    void NmcsPlayer::setLevel(unsigned int l)
    {
        this->level = l;
    }
    
    unsigned int NmcsPlayer::getLevel()
    {
        return this->level;
    }
    
    bool NmcsPlayer::search(Mcts::Node* curNode)
    {
        //if already fully expanded no need to search
        if(curNode->isFullyExpanded())
            return false;

        //get max uct node
        Mcts::Node* selectedNode = this->mctsSelection(curNode);
        
        this->checkTime();
        
        //get new node
        Mcts::Node* expandedNode = this->mctsExpansion(selectedNode);
        
        //if already explored, no unexplored state
        if(expandedNode == NULL)
            return false;
        
        this->checkTime();
        
        //do simulation and backpropagation
        this->nestedSimulation(expandedNode, expandedNode->getReferenceState(), this->getLevel());
                
        return true;
    }
    
    unsigned int NmcsPlayer::nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level)
    {
        this->checkTime();
        walker->expand();
        
        if(level == 0)
        {
            walker = this->mctsSimulation(walker);
            
            this->checkTime();
            
            this->mctsBackPropagation(expandedNode, walker);
        }
        else if(walker->isTerminal())
        {
            this->mctsBackPropagation(expandedNode, walker);
        }
        else
        {
            for(unsigned int i=0; i < walker->getCountOfChildren(); i++)
            {
                this->checkTime();
                this->nestedSimulation(expandedNode,walker->getChild(i),level-1);
            }
        }
        
        return 0;
    }
}

#endif /* NMCSPLAYER_CPP */