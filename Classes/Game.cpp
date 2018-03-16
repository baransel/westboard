#ifndef GAME_CPP
#define	GAME_CPP

#include <type_traits>

#include "Game.h"

namespace Generic
{
    Game::Game(unsigned int bs, unsigned int m, unsigned int s)
    {
        this->setBoardSize(bs);
        this->setMaxPlayerCount(m);
        this->setPlayerShift(s);
        this->setPlayerCounter(s);
        this->setPrivatePlayerCounter(s);
        this->setStarterPlayer(s);
        this->setPlayerCount(0);
        this->setPrivatePlayerCount(0);
        this->addSpecialPlayer(__nul, " ");
        this->rootState = NULL;
        this->reset();
    }
    
    Game::~Game()
    {
        this->clean();
    }
    
    void Game::reset()
    {
        this->clean();
        this->currentState = NULL;
        this->rootState = NULL;
        this->setStateIdCounter(1);
    }

    State* Game::getCurrentState()
    {
        return this->currentState;
    }

    State* Game::getRootState()
    {
        return this->rootState;
    }

    void Game::setCurrentState(State* s)
    {
        if(this->getCurrentState() != NULL)
            this->currentState->purgeStatesExcept(s);

        this->currentState = s;
    }

    unsigned int Game::getTurn(State* s)
    {
        if( s == NULL)
            return this->getCurrentState()->getActiveSide();
        else
            return s->getActiveSide();
    }

    unsigned int Game::getWinner(State* s)
    {
        if( s == NULL)
            return this->getCurrentState()->getWinner();
        else
            return s->getWinner();
    }

    unsigned int Game::getLoser(State* s)
    {
        if( s == NULL)
            return this->getCurrentState()->getLoser();
        else
            return s->getLoser();
        
    }

    unsigned int Game::useStateIdCounter()
    {
        unsigned int ret = this->getStateIdCounter();
        this->setStateIdCounter(ret + 1 );
        return ret;
    }

    unsigned int Game::getPlayerCount()
    {
        return this->publicPlayerCount;
    }

    unsigned int Game::getMaxPlayerCount()
    {
        return this->maxPlayerCount;
    }

    unsigned int Game::getPlayerShift()
    {
        return this->playerShift;
    }

    unsigned int Game::getStarterPlayer()
    {
        return this->starterPlayer;
    }

    unsigned int Game::getStateIdCounter()
    {
        return this->stateIdCounter;
    }

    PlayerHolder* Game::getPlayerSettings(unsigned int p)
    {
        return this->playerSettings[p];
    }

    unsigned int Game::addPlayer()
    {
        return this->addPlayer(this->getPrintMarkForUser(this->getPlayerCounter()), true);
    }
    
    void Game::clean()
    {
        /*for(std::unordered_map<unsigned int,PlayerHolder*>::iterator it = this->playerSettings.begin(); it != this->playerSettings.end(); it++)
        {
            delete *i;
        }*/
        delete this->getRootState();
    }

    void Game::setPlayerCount(unsigned int c)
    {
        this->publicPlayerCount = c;
    }

    void Game::incPlayerCount()
    {
        this->publicPlayerCount++;
    }

    void Game::setPrivatePlayerCount(unsigned int c)
    {
        this->privatePlayerCount = c;
    }

    void Game::incPrivatePlayerCount()
    {
        this->privatePlayerCount++;
    }

    unsigned int Game::getPrivatePlayerCount()
    {
        return this->privatePlayerCount;
    }

    void Game::setMaxPlayerCount(unsigned int c)
    {
        this->maxPlayerCount = c;
    }

    void Game::setPlayerShift(unsigned int c)
    {
        this->playerShift = c;
    }

    void Game::setPlayerCounter(unsigned int c)
    {
        this->publicPlayerCounter = c;
    }

    unsigned int Game::incPlayerCounter()
    {
        return this->publicPlayerCounter++;
    }

    unsigned int Game::decPlayerCounter()
    {
        return --this->publicPlayerCounter;
    }

    void Game::setPrivatePlayerCounter(unsigned int c)
    {
        this->privatePlayerCounter = c;
    }

    void Game::incPrivatePlayerCounter()
    {
        this->privatePlayerCounter++;
    }

    unsigned int Game::getPrivatePlayerCounter()
    {
        return this->privatePlayerCounter;
    }

    void Game::setStarterPlayer(unsigned int c)
    {
        this->starterPlayer = c;
    }

    void Game::setStateIdCounter(unsigned int c)
    {
        this->stateIdCounter = c;
    }

    unsigned int Game::getPlayerCounter()
    {
        return this->publicPlayerCounter;
    }

    unsigned int Game::addPlayer(unsigned int id, std::string print, bool overwrite)
    {
        if( utf8::distance(print.begin(),print.end()) != 1 )
            throw "Special print character is not one chracter!";

        if( this->playerSettings.count(id) > 0 )
        {
            if(overwrite)
                this->playerSettings[id]->setPrintMark(" " + print + " ");
        }
        else
        {
            this->playerSettings[id] = new PlayerHolder(id, " " + print + " ");
        }

        return id;
    }
    
    unsigned int Game::addPlayer(std::string print, bool publicCall)
    {
        unsigned int plyrCount;
        unsigned int plyrCounter;

        if(publicCall)
        {
            plyrCount = this->getPlayerCount();
            plyrCounter = this->getPlayerCounter();
        }
        else
        {
            plyrCount = this->getPrivatePlayerCount() > this->getPlayerCount() ? this->getPrivatePlayerCount() : this->getPlayerCount();
            plyrCounter = this->getPrivatePlayerCounter();
        }

        if( plyrCount + 1 > this->getMaxPlayerCount())
            throw "Player count is exceeding max player count";
        
        this->addPlayer(plyrCounter,print);

        if(publicCall)
        {
            this->incPlayerCount();
            this->incPlayerCounter();
            this->setPrivatePlayerCounter(this->getPlayerCounter());
        }
        else
        {
            this->incPrivatePlayerCount();
            this->incPrivatePlayerCounter();
        }

        return plyrCounter;
    }

    unsigned int Game::addSpecialPlayer(unsigned int id, std::string print)
    {
        if( this->playerSettings.count(id) >= this->getPlayerShift())
            throw "Special Player count reached limit!";

        return this->addPlayer(id,print);
    }

    void Game::setRootState(State* s)
    {
        this->rootState = s;
    }

    void Game::setBoardSize(unsigned int s)
    {
        this->boardSize = s;
    }

    unsigned int Game::getBoardSize()
    {
        return this->boardSize;
    }

    std::string Game::getPrintMarkForUser(unsigned int i)
    {
        return (std::string)"" + (char)(97 + i - this->getPlayerShift());
    };
}

#endif	/* GAME_CPP */