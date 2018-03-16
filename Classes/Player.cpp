#ifndef PLAYER_CPP
#define	PLAYER_CPP

#include "Player.h"

namespace Generic
{
    double __timeMultiplier = 1.363636;
    
    Player::Player(std::string n, Game* g, double mt)
    {
        this->setName(n);
        this->setSide(g->addPlayer());
        this->setTimeLimit(mt);
        this->reset();
        this->game = g;
    }

    Player::~Player()
    {
    }

    void Player::reset(bool full)
    {
        if(full)
            this->clearCounts();
    }

    std::string Player::getName()
    {
        return this->name;
    }

    double Player::getTimeLimit()
    {
        return this->timeLimit;
    }

    void Player::setTimeLimit(double mt)
    {
        this->timeLimit = mt * __timeMultiplier;
    }

    unsigned int Player::getSide()
    {
        return this->side;
    }

    void Player::setSide(unsigned int s)
    {
        this->side = s;
    }

    unsigned Player::getWinCount()
    {
        return this->winCount;
    }

    void Player::incWinCount()
    {
        this->winCount++;
    }

    unsigned Player::getDrawCount()
    {
        return this->drawCount;
    }

    void Player::incDrawCount()
    {
        this->drawCount++;
    }

    unsigned Player::getLoseCount()
    {
        return this->loseCount;
    }

    void Player::incLoseCount()
    {
        this->loseCount++;
    }

    void Player::clearCounts()
    {
        this->winCount = 0;
        this->drawCount = 0;
        this->loseCount = 0;
        this->setThinkTime(0);
        this->setThinkCount(0);
    }

    Game* Player::getGame()
    {
        return this->game;
    }

    void Player::setName(std::string n)
    {
        this->name = n;
    }
    
    void Player::setThinkTime(double t)
    {
        this->thinkTime = t;
    }
    
    double Player::getThinkTime()
    {
        return this->thinkTime;
    }
    
    void Player::setThinkCount(unsigned int c)
    {
        this->thinkCount = c;
    }
    
    void Player::incThinkCount()
    {
        this->thinkCount++;
    }
        
    unsigned int Player::getThinkCount()
    {
        return this->thinkCount;
    }
    
    void Player::setStartTime()
    {
        gettimeofday(&(this->startTime),NULL);
    }
    
    timeval Player::getStartTime()
    {
        return this->startTime;
    }
    
    void Player::setLastCheckTime()
    {
        gettimeofday(&(this->lastCheckTime),NULL);
    }
    
    timeval Player::getLastCheckTime()
    {
        return this->lastCheckTime;
    }
    
    bool Player::checkTime()
    {
        this->setLastCheckTime();
        this->setThinkTime( (this->getLastCheckTime().tv_sec - this->getStartTime().tv_sec) + ( this->getLastCheckTime().tv_usec - this->getStartTime().tv_usec) / (double)1000000 );
        
        if (this->getThinkTime() > this->getTimeLimit())
            throw this->getLastCheckTime();
        
        return true;
    }
}

#endif	/* PLAYER_CPP */