#ifndef STATE_CPP
#define	STATE_CPP

#include "State.h"
#include "Game.h"

namespace Generic
{
    State::State(Game* g, unsigned int bs)
    {
        this->setReferenceGame(g);
        this->setId(g->useStateIdCounter());
        this->setParent(NULL);
        this->activeSide = g->getStarterPlayer();
        this->boardSize = bs;
        this->setWinner(__nul);
    }

    State::State(State* p)
    {
        if( p == NULL)
            throw "Null parent given to state";

        this->setReferenceGame(p->getReferenceGame());
        this->setId(p->getReferenceGame()->useStateIdCounter());
        this->setParent(p);
        this->activeSide = p->nextSide();
        this->boardSize = p->getBoardSize();
        this->setWinner(__nul);
    }

    State::~State()
    {
        //unallocate board
        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            delete[] this->board[i];
        }
        delete[] this->board;

        for( std::vector<State*>::iterator i = children.begin(); i != children.end(); i++ )
        {
            delete *i;
        }
    }

    int State::getId()
    {
        return this->id;
    }

    bool State::isTerminal()
    {
        return this->terminal;
    }

    State* State::getParent()
    {
        return this->parent;
    }

    unsigned int State::getCountOfChildren()
    {
        return this->children.size();
    }

    State* State::getChild(unsigned int i)
    {
        return this->children[i];
    }

    void State::purgeStatesExcept(State* s)
    {
        if(this->getCountOfChildren() > 0)
        {
            std::vector<State*>::iterator it = this->children.begin();

            while(it != this->children.end())
            {
                if( (*it)->getId() != s->getId())
                {
                    delete *it;
                    it = this->children.erase(it);
                }
                else
                    it++;
            }

            //reduces size of the vector
            std::vector<State*>(this->children.begin(), this->children.end()).swap(this->children);
        }
    }

    void State::print()
    {
        std::vector<std::string> p = this->getPrint();
        for(int i = 0; i < p.size(); i++)
            std::cout << p[i] << std::endl;
    }

    std::vector<std::string> State::getPrint()
    {
        std::vector<std::string> ret;
        std::string tmp = __printBoardLeftTopCorner;

        for(unsigned int j=0; j<this->getBoardSize()-1; j++)
            tmp += __printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardTopSectionBreak;
        tmp += __printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardRightTopCorner;
        ret.push_back(tmp);

        for(unsigned int i=0; i<this->getBoardSize(); i++)
        {
            tmp = __printBoardVerticalLine;

            for(unsigned int j=0; j<this->getBoardSize(); j++)
            {
                tmp += this->getReferenceGame()->getPlayerSettings(this->getBoard(i,j))->getPrintMark();

                tmp += __printBoardVerticalLine;
            }
            ret.push_back(tmp);

            if(i != this->getBoardSize()-1)
            {
                tmp = __printBoardLeftSectionBreak;

                for(unsigned int j=0; j<this->getBoardSize()-1; j++)
                    tmp += __printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardMiddleSectionBreak;
                tmp += __printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardRightSectionBreak;

                ret.push_back(tmp);
            }
        }

        tmp = __printBoardLeftBottomCorner;

        for(unsigned int j=0; j<this->getBoardSize()-1; j++)
            tmp += __printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardBottomSectionBreak;
        tmp += __printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardHorizantalLine+__printBoardRightBottomCorner;

        ret.push_back(tmp);

        return ret;
    }

    unsigned int State::getBoardSize()
    {
        return this->boardSize;
    }

    void State::setBoard(unsigned int i, unsigned int j, unsigned int v)
    {
        this->board[i][j] = v;
    }

    unsigned int State::getBoard(unsigned int i, unsigned int j)
    {
        return this->board[i][j];
    }

    unsigned int State::getActiveSide()
    {
        return this->activeSide;
    }

    unsigned int State::nextSide()
    {
        //return (this->getActiveSide() +  % ( __playerShift + this->playerCount ));
        //return (((this->getActiveSide() - __playerShift) + 1) % this->playerCount) + __playerShift;
        return (((this->getActiveSide() - this->getReferenceGame()->getPlayerShift()) + 1) % this->getReferenceGame()->getPlayerCount()) + this->getReferenceGame()->getPlayerShift();
    }

    unsigned int State::getWinner()
    {
        return this->winner;
    }

    unsigned int State::getLoser()
    {
        if( this->winner == __nul)
            return __nul;
        else
            return (((this->winner - this->getReferenceGame()->getPlayerShift()) + 1) % this->getReferenceGame()->getPlayerCount()) + this->getReferenceGame()->getPlayerShift();
    }

    void State::setReferenceGame(Game* g)
    {
        this->referenceGame = g;
    }

    void State::setId(unsigned int i)
    {
        this->id = i;
    }

    void State::setParent(State* s)
    {
        this->parent = s;
    }

    Game* State::getReferenceGame()
    {
        return this->referenceGame;
    }

    void State::setTerminal(bool s)
    {
        this->terminal = s;
    }

    void State::setExpanded(bool s)
    {
        this->expanded = s;
    }

    bool State::isExpanded()
    {
        return this->expanded;
    }

    void State::setWinner(unsigned int w)
    {
        this->winner = w;
    }

    void State::initializeBoard()
    {
        //allocate first dimension of board
        this->board = new unsigned int*[this->getBoardSize()];
        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            //allocate row of board
            this->board[i] = new unsigned int[this->getBoardSize()];
        }
    }
}

#endif	/* STATE_CPP */