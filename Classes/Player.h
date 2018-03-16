#ifndef PLAYER_H
#define	PLAYER_H

#include <sys/time.h>
#include "Game.h"

namespace Generic
{
    class Player
    {
    public:
        Player(std::string n, Game* g, double mt);

        virtual ~Player();

        virtual void reset(bool full = true);

        std::string getName();

        double getTimeLimit();

        void setTimeLimit(double mt);

        unsigned int getSide();

        void setSide(unsigned int s);

        unsigned getWinCount();

        void incWinCount();

        unsigned getDrawCount();

        void incDrawCount();

        unsigned getLoseCount();

        void incLoseCount();

        void clearCounts();

        Game* getGame();
        
        void setThinkTime(double t);
        
        double getThinkTime();
        
        void setThinkCount(unsigned int c);
        
        void incThinkCount();
        
        unsigned int getThinkCount();
        
        void setStartTime();
        
        timeval getStartTime();
        
        void setLastCheckTime();
        
        timeval getLastCheckTime();
        
        bool checkTime();
        
        virtual void move() = 0;
        

    private:
        std::string name;
        Game * game;
        timeval startTime;
        timeval lastCheckTime;
        double timeLimit;
        double thinkTime;
        unsigned int thinkCount;
        unsigned int side;
        unsigned int winCount;
        unsigned int drawCount;
        unsigned int loseCount;

        void setName(std::string n);
    };
}

#endif	/* PLAYER_H */

