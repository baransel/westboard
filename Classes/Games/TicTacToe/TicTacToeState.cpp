#ifndef TICTACTOESTATE_CPP
#define	TICTACTOESTATE_CPP

#include "TicTacToeState.h"
#include "../../Game.h"

namespace TicTacToe
{
    TicTacToeState::TicTacToeState(Generic::Game* g, unsigned int bs) : State(g, bs)
    {
        this->setExpanded(false);

        //prepare board
        this->initializeBoard();
    }

    TicTacToeState::TicTacToeState(TicTacToeState* p) : State(p)
    {
        this->setExpanded(false);

        //prepare board
        this->initializeBoard();

    }

    TicTacToeState::~TicTacToeState()
    {
    }

    bool TicTacToeState::checkForTerminal()
    {
        this->expand();

        bool ret = this->checkForTerminalInDioganal()
                || this->checkForTerminalInReverseDioganal()
                || this->checkForTerminalInRows()
                || this->checkForTerminalInColumns()
                || this->getCountOfChildren() == 0;

        this->setTerminal(ret);
        return this->isTerminal();
    }

    void TicTacToeState::expand()
    {
        if(!this->isExpanded())
        {
            TicTacToeState* tempState;

            //allocate children for max
            this->children.reserve(this->getBoardSize() * this->getBoardSize());

            for(unsigned int i=0; i < this->getBoardSize(); i++ )
            {
                for (unsigned int j=0; j < this->getBoardSize(); j++)
                {
                    if(this->getBoard(i,j) == Generic::__nul)
                    {
                        tempState = new TicTacToeState(this);
                        tempState->setBoard(i,j, this->getActiveSide());
                        this->children.push_back(tempState);
                    }
                }
            }

            //reduces size of the children vector
            std::vector<State*>(this->children.begin(), this->children.end()).swap(this->children);

            this->setExpanded();
            this->checkForTerminal();
        }
    }
    
    void TicTacToeState::initializeBoard()
    {
        Generic::State::initializeBoard();

        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            for (unsigned int j=0; j < this->getBoardSize(); j++)
            {
                //set board same as parent
                if(this->getParent() == NULL)
                    this->setBoard(i,j,Generic::__nul);
                else
                    this->setBoard(i,j,this->getParent()->getBoard(i,j));
            }
        }
    }

    bool TicTacToeState::checkForTerminalInRows()
    {
        bool ret = false;
        unsigned int winner = this->getWinner();

        //check for each row
        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            unsigned int prev = this->getBoard(i,0);
            for (unsigned int j=0; j < this->getBoardSize(); j++)
            {
                if( prev != Generic::__nul && this->getBoard(i,j) == prev )
                {
                    ret = true;
                    winner = prev;
                    prev = this->getBoard(i,j);
                    continue;
                }
                else
                {
                    ret = false;
                    break;
                }
            }

            if(ret)
            {
                this->setWinner(winner);
                break;
            }
        }

        return ret;
    }

    bool TicTacToeState::checkForTerminalInColumns()
    {
        bool ret = false;
        unsigned int winner = this->getWinner();

        //check for each columns
        for(unsigned int j=0; j < this->getBoardSize(); j++ )
        {
            unsigned int prev = this->getBoard(0,j);
            for (unsigned int i=0; i < this->getBoardSize(); i++)
            {
                if( prev != Generic::__nul && this->getBoard(i,j) == prev )
                {
                    ret = true;
                    winner = prev;
                    prev = this->getBoard(i,j);
                    continue;
                }
                else
                {
                    ret = false;
                    break;
                }
            }

            if(ret)
            {
                this->setWinner(winner);
                break;
            }
        }

        return ret;
    }

    bool TicTacToeState::checkForTerminalInDioganal()
    {
        bool ret = false;
        unsigned int winner = this->getWinner();

        //check for diagonal
        unsigned int prev = this->getBoard(0,0);
        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            if( prev != Generic::__nul && this->getBoard(i,i) == prev )
            {
                ret = true;
                winner = prev;
                continue;
            }
            else
            {
                ret = false;
                winner = this->getWinner();
                break;
            }
        }

        this->setWinner(winner);
        return ret;
    }

    bool TicTacToeState::checkForTerminalInReverseDioganal()
    {
        bool ret = false;
        unsigned int winner = this->getWinner();

        //check for diagonal
        unsigned int prev = this->getBoard(0,this->getBoardSize()-1);
        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            if( prev != Generic::__nul && this->getBoard(i,this->getBoardSize()-1-i) == prev )
            {
                ret = true;
                winner = prev;
                continue;
            }
            else
            {
                ret = false;
                winner = this->getWinner();
                break;
            }
        }

        this->setWinner(winner);
        return ret;
    }
}

#endif	/* TICTACTOESTATE_CPP */