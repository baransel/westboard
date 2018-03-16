#ifndef MCTSMRPLAYER_CPP
#define MCTSMRPLAYER_CPP

#include "MctsMRPlayer.h"

namespace MctsMR
{
    MctsMRPlayer::MctsMRPlayer(std::string n, Generic::Game* g, double mt, double c, unsigned int l) : MctsPlayer(n, g, mt, c)
    {
        this->setLevel(l);
    }

    MctsMRPlayer::MctsMRPlayer(Generic::Game* g, double mt, double c, unsigned int l) : MctsPlayer("Mcts-MR", g, mt, c)
    {
        this->setLevel(l);
    }
    
    void MctsMRPlayer::setLevel(unsigned int l)
    {
        this->level = l;
    }
    
    unsigned int MctsMRPlayer::getLevel()
    {
        return this->level;
    }

    Generic::State* MctsMRPlayer::mctsSimulation(Generic::State * walker)
    {
        Generic::State * tmpState;
        
        walker->expand();
        
        while(!walker->isTerminal())
        {
            this->checkTime();
            bool isMax;
            double newScore;
            
            if( walker->getActiveSide() == this->getSide())
            {
                isMax = true;
                newScore = Mcts::__loseScore;
            }
            else
            {
                isMax = false;
                newScore = Mcts::__winScore;
            }
            
            double* tmpScore = NULL;
            unsigned int selectedChild = rand() % walker->getCountOfChildren();
            
            for(unsigned int i=0; i < walker->getCountOfChildren(); i++)
            {
                tmpState = walker->getChild(i);
                tmpScore = this->minimaxRolloutScore(tmpState,this->getLevel()-1,!isMax);
                
                if(tmpScore != NULL)
                {
                    if(isMax && *tmpScore > newScore)
                    {
                        newScore = *tmpScore;
                        selectedChild = i;
                    }
                    else if(!isMax && *tmpScore < newScore)
                    {
                        newScore = *tmpScore;
                        selectedChild = i;
                    }
                    else
                        delete tmpScore;
                }
            }
            
            walker = walker->getChild(selectedChild);
            
            walker->expand();
        }
        
        return walker;
    }
    
    double* MctsMRPlayer::minimaxRolloutScore(Generic::State* w, unsigned int level, bool max)
    {
        double score;
        double* ret = NULL;
        double* tmpRet;
        Generic::State* tmpState;
        
        //check for end
        if(w->isTerminal())
        {
            ret = new double;
            *ret = this->getGoalScore(w);
            return ret;
        }
        
        //if no result
        if(level == 0)
            return NULL;
        
        if(max)
            score = Mcts::__loseScore;
        else
            score = Mcts::__winScore;
        
        for(unsigned int i=0; i < w->getCountOfChildren(); i++)
        {
            this->checkTime();
            tmpState=w->getChild(i);
            tmpState->expand();
            tmpRet = this->minimaxRolloutScore(tmpState,level-1,!max);
            if( tmpRet != NULL )
            {
                if( max && score < this->getGoalScore(tmpState) )
                {
                    score = this->getGoalScore(tmpState);
                    delete ret;
                    ret = tmpRet;
                }
                else if( !max && score > this->getGoalScore(tmpState) )
                {
                    score = this->getGoalScore(tmpState);
                    delete ret;
                    ret = tmpRet;
                }
                else
                    delete tmpRet;
            }
        }
        
        return ret;
    }
}

#endif /* MCTSMRPLAYER_CPP */