#ifndef NMCSPLAYER_H
#define NMCSPLAYER_H

#include "MctsPlayer.h"

namespace Nmcs
{
    class NmcsPlayer : public Mcts::MctsPlayer
    {
    public:
        NmcsPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        NmcsPlayer(Generic::Game* g, double mt, double c, unsigned int l);
        
        unsigned int getLevel();
        
        virtual bool search(Mcts::Node* curNode);
        
    protected:
        
        virtual unsigned int nestedSimulation(Mcts::Node* expandedNode, Generic::State* walker, unsigned int level);
        
    private:
        unsigned int level;
        
        void setLevel(unsigned int l);
    };
}

#endif /* NMCSPLAYER_H */

