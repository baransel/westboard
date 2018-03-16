#ifndef GAME_H
#define	GAME_H

#include "PlayerHolder.h"
#include "State.h"
#include "Settings.h"
#include "../utf8/utf8.h"

namespace Generic
{
    class Game
    {
    public:
        Game(unsigned int bs, unsigned int m = __defaultMaxPlayerCount , unsigned int s = __defaultPlayerShift);

        virtual ~Game();

        virtual void reset();

        State* getCurrentState();

        State* getRootState();

        void setCurrentState(State* s);

        virtual unsigned int getTurn(State* s = NULL);

        virtual unsigned int getWinner(State* s = NULL);

        virtual unsigned int getLoser(State* s = NULL);

        unsigned int useStateIdCounter();
        
        unsigned int getPlayerCount();
        
        unsigned int getMaxPlayerCount();
        
        unsigned int getPlayerShift();
        
        unsigned int getStarterPlayer();
        
        unsigned int getStateIdCounter();
        
        PlayerHolder* getPlayerSettings(unsigned int p);
        
        unsigned int addPlayer();
        
    private:
        State* rootState;
        State* currentState;
        unsigned int boardSize;
        std::unordered_map<unsigned int,PlayerHolder*> playerSettings;
        unsigned int publicPlayerCount;
        unsigned int publicPlayerCounter;
        unsigned int privatePlayerCount;
        unsigned int privatePlayerCounter;
        unsigned int maxPlayerCount;
        unsigned int playerShift;
        unsigned int starterPlayer;
        unsigned int stateIdCounter;
        
        void clean();

        void setPlayerCount(unsigned int c);
        
        void incPlayerCount();
        
        void setPrivatePlayerCount(unsigned int c);
        
        void incPrivatePlayerCount();
        
        unsigned int getPrivatePlayerCount();
        
        void setMaxPlayerCount(unsigned int c);
        
        void setPlayerShift(unsigned int c);
        
        void setPlayerCounter(unsigned int c);
        
        unsigned int incPlayerCounter();
        
        unsigned int decPlayerCounter();
        
        void setPrivatePlayerCounter(unsigned int c);
        
        void incPrivatePlayerCounter();
        
        unsigned int getPrivatePlayerCounter();
        
        void setStarterPlayer(unsigned int c);
        
        void setStateIdCounter(unsigned int c);
        
        unsigned int getPlayerCounter();
        
        unsigned int addPlayer(unsigned int id, std::string print, bool overwrite = false);
        
    protected:
        
        unsigned int addPlayer(std::string print, bool publicCall = false);
        
        unsigned int addSpecialPlayer(unsigned int id, std::string print);
        
        void setRootState(State* s);
        
        void setBoardSize(unsigned int s);
        
        unsigned int getBoardSize();
        
        virtual std::string getPrintMarkForUser(unsigned int i);
    };
}

#endif	/* GAME_H */

