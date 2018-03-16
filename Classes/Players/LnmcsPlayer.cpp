#ifndef LNMCSPLAYER_CPP
#define LNMCSPLAYER_CPP

#include "LnmcsPlayer.h"

namespace Lnmcs
{
    LnmcsPlayer::LnmcsPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : MctsPlayer(n, g, mt, c)
    {
        this->setLevel(l);
    }

    LnmcsPlayer::LnmcsPlayer(Generic::Game* g, double mt, double c, unsigned int l) : MctsPlayer("Lnmcs", g, mt, c)
    {
        this->setLevel(l);
    }
    
    void LnmcsPlayer::setLevel(unsigned int l)
    {
        this->level = l;
    }
    
    unsigned int LnmcsPlayer::getLevel()
    {
        return this->level;
    }
    
    bool LnmcsPlayer::search(Mcts::Node* curNode)
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
        
        //do standart simulation
        Generic::State* walker = this->mctsSimulation(expandedNode->getReferenceState());
        
        //go up for nesting
        unsigned int up = 0;
        while(up < this->getLevel() && walker != expandedNode->getReferenceState() && walker->getParent() != NULL)
        {
            up++;
            walker = walker->getParent();
        }
        
        //do simulation and backpropagation
        this->nestedSimulation(expandedNode, walker, up);
                
        return true;
    }
    
    unsigned int LnmcsPlayer::nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level)
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

#endif /* LNMCSPLAYER_CPP */