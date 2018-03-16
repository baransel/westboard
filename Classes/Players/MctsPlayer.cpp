#ifndef MCTSPLAYER_CPP
#define MCTSPLAYER_CPP

#include "MctsPlayer.h"

namespace Mcts
{
    Node::Node()
    {
        this->parent = NULL;
        this->referenceState = NULL;
        this->c = __c;
        this->setId(0);
        this->reset();
    }

    Node::Node(Node* p, Generic::State* s, double c)
    {
        this->parent = p;
        this->referenceState = s;
        this->c = c;
        this->setId(this->referenceState->getId());
        this->reset();
    }

    Node::~Node()
    {
    }

    void Node::reset()
    {
        this->winScoreCounter = 0;
        this->simScoreCounter = 0;
        this->fullyExpandedChildCount = 0;
    }

    unsigned int Node::getId()
    {
        return this->id;
    }

    Generic::State* Node::getReferenceState()
    {
        return this->referenceState;
    }

    void Node::incFullyExpandedChildCount()
    {
        this->fullyExpandedChildCount++;
        this->checkFullyExpandedChildCount(true);
    }

    void Node::checkFullyExpandedChildCount(bool inc)
    {
        if( this->isFullyExpanded() && this->parent != NULL)
            if(inc)
                this->parent->incFullyExpandedChildCount();
            else
                this->parent->checkFullyExpandedChildCount();
    }

    unsigned int Node::getFullyExpandedChildCount()
    {
        return this->fullyExpandedChildCount;
    }

    bool Node::isFullyExpanded()
    {
        if(this->getReferenceState() != NULL)
            return this->getFullyExpandedChildCount() == this->getReferenceState()->getCountOfChildren();
        else
            true;
    }

    void Node::addScore(double s)
    {
        this->winScoreCounter += s;
        this->simScoreCounter++;
        if(this->parent != NULL)
            this->parent->addScore(s);
        this->calculateUct();
    }

    double Node::getScore()
    {
        if (this->simScoreCounter == 0)
            return __loseScore;
        else
            return this->getWinScoreCount() / this->getSimScoreCount();
    }

    double Node::getWinScoreCount()
    {
        return this->winScoreCounter;
    }
    int Node::getSimScoreCount()
    {
        return this->simScoreCounter;
    }

    double Node::getUct()
    {
        return this->uct;
    }

    void Node::calculateUct()
    {
        int parentSimScoreCounter;

        //if root node, parent uct is 0
        if(parent == NULL)
            parentSimScoreCounter = 0;
        else
        {
            //calculate parent uct
            parent->calculateUct();
            parentSimScoreCounter = this->parent->getSimScoreCount();
        }

        //a new node must be at highest level
        if (this->simScoreCounter == 0)
            this->uct = 999;
        else
            this->uct = this->getScore() + this->c * sqrt(log(parentSimScoreCounter)/this->getSimScoreCount());
    }
    
    void Node::setId(unsigned int i)
    {
        this->id = i;
    }
    
    MctsPlayer::MctsPlayer(std::string n, Generic::Game* g, double mt, double c) : Generic::Player(n, g, mt)
    {
        this->c = c;
    }

    MctsPlayer::MctsPlayer(Generic::Game* g, double mt, double c) : Generic::Player("Mcts", g, mt)
    {
        this->c = c;
    }

    MctsPlayer::~MctsPlayer()
    {
    }

    void MctsPlayer::reset(bool full)
    {
        this->thinkTree.clear();
        Generic::Player::reset(full);
    }

    void MctsPlayer::move()
    {            
        if(this->getSide() == this->getGame()->getTurn())
        {
            Node* selectedNode = NULL;
            
            //it should be expanded, but check it anyway
            this->getGame()->getCurrentState()->expand();

            //check if current state is terminal
            if( this->getGame()->getCurrentState()->isTerminal() )
                return;
            
            this->setStartTime();
            
            try
            {
                //think
                this->think();
            }
            catch(timeval t)
            {
                //time limit reached, nothing to do
            }

            selectedNode = this->selectMove();

            if( selectedNode == NULL )
            {
                this->getGame()->getCurrentState()->expand();
                unsigned int optionCount = this->getGame()->getCurrentState()->getCountOfChildren();
                
                //play random
                if( optionCount > 0)
                {
                    this->getGame()->setCurrentState(this->getGame()->getCurrentState()->getChild(rand() % optionCount));
                }
            }
            else
            {
                //game move
                this->getGame()->setCurrentState(selectedNode->getReferenceState());

                //expand it
                this->getGame()->getCurrentState()->expand();
            }
        }
    }
    
    void MctsPlayer::think()
    {
        Node* curNode = this->getCurrentNode();
        
        this->setThinkCount(0);
        bool continueToSearch = true;

        while( this->checkTime() && continueToSearch )
        {
            continueToSearch = this->search(curNode);
            this->incThinkCount();
        }
    }
    
    Node* MctsPlayer::selectMove()
    {
        double maxScore = -99999;
        Node* maxScoreNode = NULL;

        //get child with maximum score
        for(unsigned int i = 0; i < this->getGame()->getCurrentState()->getCountOfChildren(); i++)
        {
            Node* tmpNode;
            
            //check node is exist in our think tree
            if ( this->thinkTree.count(this->getGame()->getCurrentState()->getChild(i)->getId()) == 1 )
            {
                tmpNode = &(this->thinkTree[this->getGame()->getCurrentState()->getChild(i)->getId()]);
                //if new high score
                if( maxScore < tmpNode->getScore() )
                {
                    //delete old high score from think tree
                    this->cutFromThinkTree(maxScoreNode);

                    //save new high score
                    maxScore = tmpNode->getScore();
                    maxScoreNode = tmpNode;
                }
                else
                {
                    //delete from think tree
                    this->cutFromThinkTree(tmpNode);
                }
            }
        }
        
        return maxScoreNode;
    }

    Node* MctsPlayer::getCurrentNode()
    {
        Node* tmpNode;
        unsigned int curNodeId = this->getGame()->getCurrentState()->getId();
        Node* curNode = NULL;
        if( this->thinkTree.count(curNodeId) > 0 )
            curNode = &(this->thinkTree[curNodeId]);

        if( curNode == NULL )
        {
            if( this->getGame()->getCurrentState()->getParent() == NULL )
                tmpNode = new Node(NULL, this->getGame()->getCurrentState(), this->c);
            else
                tmpNode = new Node(
                                                    &(this->thinkTree[this->getGame()->getCurrentState()->getParent()->getId()]),
                                                    this->getGame()->getCurrentState(), this->c
                );

            curNode = &(this->thinkTree[curNodeId] = *tmpNode);
            delete tmpNode;
        }
        
        return curNode;
    }
    
    double MctsPlayer::getGoalScore(Generic::State* s)
    {
        if ( s->getReferenceGame()->getWinner(s) == this->getSide() )
            return __winScore;
        else if ( s->getReferenceGame()->getLoser(s) == this->getSide() )
            return __loseScore;
        else
            return __drawScore;
    }
    
    bool MctsPlayer::search(Node* curNode)
    {
        //if already fully expanded no need to search
        if(curNode->isFullyExpanded())
            return false;

        //get max uct node
        Node* selectedNode = this->mctsSelection(curNode);
        
        this->checkTime();
        
        //get new node
        Node* expandedNode = this->mctsExpansion(selectedNode);
        
        //if already explored, no unexplored state
        if(expandedNode == NULL)
            return false;
        
        this->checkTime();
        
        //do simulation
        Generic::State* walker = this->mctsSimulation(expandedNode->getReferenceState());
        
        this->checkTime();
        
        this->mctsBackPropagation(expandedNode,walker);
        
        return true;
    }
    
    Node* MctsPlayer::mctsSelection(Node* curNode)
    {
        Node* tmpNode;

        //get current node uct
        double maxUct = curNode->getUct();
        Node* maxUctNode = curNode;
        
        //find max uct
        bool continueToSearch = true;
        while(continueToSearch)
        {
            continueToSearch = false;
            for(unsigned int i = 0; i < maxUctNode->getReferenceState()->getCountOfChildren(); i++)
            {
                if( this->thinkTree.count(maxUctNode->getReferenceState()->getChild(i)->getId()) == 1 )
                {
                    tmpNode = &(this->thinkTree[maxUctNode->getReferenceState()->getChild(i)->getId()]);
                    
                    if( maxUct < tmpNode->getUct() && !tmpNode->isFullyExpanded() )
                    {
                        maxUct = tmpNode->getUct();
                        maxUctNode = tmpNode;
                        continueToSearch = true;
                    }
                    
                    this->checkTime();
                }
            }
        }
        
        return maxUctNode;
    }

    Node* MctsPlayer::mctsExpansion(Node* selectedNode)
    {
        //get unexplored node states
        std::unordered_map<unsigned int,Generic::State*> newNodesReferences;
        unsigned int newNodesIndex = 0;

        for(unsigned int i=0; i < selectedNode->getReferenceState()->getCountOfChildren(); i++)
        {
            if( this->thinkTree.count(selectedNode->getReferenceState()->getChild(i)->getId()) == 0 )
            {
                newNodesReferences[newNodesIndex++] = selectedNode->getReferenceState()->getChild(i);
            }
        }
        
        this->checkTime();
        
        //create a random node from unexplored states
        Node* expandedNode;
        Generic::State* nodeReference;
        if( newNodesReferences.size() > 0 )
        {
            //select random
            nodeReference = newNodesReferences[rand() % newNodesIndex];
            expandedNode = new Node(selectedNode, nodeReference, this->c);
            this->thinkTree[nodeReference->getId()] = *expandedNode;
            delete expandedNode;
            expandedNode = &(this->thinkTree[nodeReference->getId()]);


            //check and set for fullyExpanded
            if(newNodesIndex == 1 && expandedNode->isFullyExpanded())
                expandedNode->checkFullyExpandedChildCount(true);
        
            this->checkTime();
            
            return expandedNode;
        }
        else
            //no unexplored state
            return NULL;
    }
    
    Generic::State* MctsPlayer::mctsSimulation(Generic::State * walker)
    {
        walker->expand();
        
        while(!walker->isTerminal())
        {
            this->checkTime();
            walker = walker->getChild(rand() % walker->getCountOfChildren());
            walker->expand();
        }
        
        return walker;
    }
    
    unsigned int MctsPlayer::mctsBackPropagation(Node* expandedNode, Generic::State* walker)
    {
        this->checkTime();
        expandedNode->addScore(this->getGoalScore(walker));
        return 0;
    }
    
    void MctsPlayer::cutFromThinkTree(Node* n)
    {
        if( n != NULL )
        {
            //get reference state
            Generic::State* ref = n->getReferenceState();

            //delete node
            this->thinkTree.erase(n->getId());

            //call for each child
            for(unsigned int i=0; i < ref->getCountOfChildren(); i++)
            {
                if(this->thinkTree.count(ref->getChild(i)->getId()) > 0)
                    this->cutFromThinkTree(&(this->thinkTree[ref->getChild(i)->getId()]));
            }
        }
    }
}

#endif /* MCTSPLAYER_CPP */