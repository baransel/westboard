#ifndef LNMCSPLAYER_H
#define LNMCSPLAYER_H

#include "MctsPlayer.h"

namespace Lnmcs
{
    class LnmcsPlayer : public Mcts::MctsPlayer
    {
    public:
        LnmcsPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        LnmcsPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
        unsigned int getLevel();
        
        virtual bool search(Mcts::Node* curNode);
        
    protected:
        
        virtual unsigned int nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level);
        
    private:
        unsigned int level;
        
        void setLevel(unsigned int l);
    };
}

#endif /* LNMCSPLAYER_H */

