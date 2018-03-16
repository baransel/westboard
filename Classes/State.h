#ifndef STATE_H
#define	STATE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Settings.h"
#include "PlayerHolder.h"

namespace Generic
{
    class Game;
    
    class State
    {
    public:
        State(Game* g, unsigned int bs);
        
        State(State* p);

        virtual ~State();
        
        int getId();

        bool isTerminal();

        virtual State* getParent();
        
        unsigned int getCountOfChildren();

        State* getChild(unsigned int i);

        void purgeStatesExcept(State* s);

        void print();
        
        std::vector<std::string> getPrint();
        
        unsigned int getBoardSize();
        
        void setBoard(unsigned int i, unsigned int j, unsigned int v);
        
        unsigned int getBoard(unsigned int i, unsigned int j);
        
        unsigned int getActiveSide();
        
        unsigned int nextSide();
        
        unsigned int getWinner();
        
        unsigned int getLoser();
        
        Game* getReferenceGame();

        virtual bool checkForTerminal() = 0;
        virtual void expand() = 0;
        
    private:
        Game* referenceGame;
        unsigned int id;
        bool terminal;
        State* parent;
        unsigned int activeSide;
        unsigned int winner;
        bool expanded;
        unsigned int **board;
        unsigned int boardSize;

        void setReferenceGame(Game* g);
        
        void setId(unsigned int i);

        void setParent(State* s);

    protected:
        
        std::vector<State*> children;
        
        void setTerminal(bool s = true);
        
        void setExpanded(bool s = true);
        
        bool isExpanded();
        
        void setWinner(unsigned int w);
        
        virtual void initializeBoard();
    };
}
#endif	/* STATE_H */

