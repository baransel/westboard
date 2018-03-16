#ifndef MCTSPLAYER_H
#define MCTSPLAYER_H

#include <unordered_map>
#include <cmath>
#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include "../State.h"
#include "../Game.h"
#include "../Player.h"

namespace Mcts
{
    const double __winScore = 1;
    const double __loseScore = -1;
    const double __drawScore = 0;
    const double __c = 1.414;
    
    class Node
    {
    public:
        
        Node();

        Node(Node* p, Generic::State* s, double c);

        virtual ~Node();

        void reset();

        unsigned int getId();
        
        Generic::State* getReferenceState();
        
        void incFullyExpandedChildCount();
        
        void checkFullyExpandedChildCount(bool inc = false);
        
        unsigned int getFullyExpandedChildCount();
        
        bool isFullyExpanded();

        void addScore(double s);

        double getScore();

        double getWinScoreCount();
        
        int getSimScoreCount();
        
        double getUct();

        void calculateUct();

    private:
        unsigned int id;
        double c;
        Generic::State* referenceState;
        Node* parent;
        double winScoreCounter;
        int simScoreCounter;
        double uct;
        unsigned int fullyExpandedChildCount;

        void setId(unsigned int i);
    };

    class MctsPlayer : public Generic::Player
    {
    public:
        MctsPlayer(std::string n, Generic::Game* g, double mt, double c);

        MctsPlayer(Generic::Game* g, double mt, double c);

        virtual ~MctsPlayer();
        
        virtual void reset(bool full = true);

        virtual void move();
        
    protected:
        
        std::unordered_map<unsigned int,Node> thinkTree;
        
        virtual void think();
        
        virtual Node* selectMove();
        
        virtual Node* getCurrentNode();
        
        virtual double getGoalScore(Generic::State* s);
        
        virtual bool search(Node* curNode);
        
        virtual Node* mctsSelection(Node* curNode);
        
        virtual Node* mctsExpansion(Node* selectedNode);
        
        virtual Generic::State* mctsSimulation(Generic::State* walker);
        
        virtual unsigned int mctsBackPropagation(Node* expandedNode, Generic::State* walker);
        
    private:
        double c;
        void cutFromThinkTree(Node* n);
    };
}

#endif /* MCTSPLAYER_H */

