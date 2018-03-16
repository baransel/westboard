#ifndef MCTSMRPLAYER_H
#define MCTSMRPLAYER_H

#include "MctsPlayer.h"

namespace MctsMR
{
    class MctsMRPlayer : public Mcts::MctsPlayer
    {
    public:
        MctsMRPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l);

        MctsMRPlayer(Generic::Game* g, double mt, double c, unsigned int l);

        virtual Generic::State* mctsSimulation(Generic::State* walker);
        
        unsigned int getLevel();
        
    private:
        unsigned int level;
        
        void setLevel(unsigned int l);
        
        double* minimaxRolloutScore(Generic::State* w, unsigned int level, bool max);
    };
}

#endif /* MCTSMRPLAYER_H */

