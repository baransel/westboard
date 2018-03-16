#ifndef KNIGHTTHROUGHSTATE_CPP
#define	KNIGHTTHROUGHSTATE_CPP

#include "KnightthroughState.h"
#include "../../Game.h"

namespace Knightthrough
{
    KnightthroughState::KnightthroughState(Generic::Game* g, unsigned int bs) : State(g, bs)
    {
        this->setExpanded(false);

        this->piecesCount[this->getReferenceGame()->getStarterPlayer()] = 0;
        this->piecesCount[this->getReferenceGame()->getStarterPlayer() + 1] = 0;

        //prepare board
        this->initializeBoard();
    }

    KnightthroughState::KnightthroughState(KnightthroughState* p) : State(p)
    {
        this->setExpanded(false);

        this->piecesCount[this->getReferenceGame()->getStarterPlayer()] = 0;
        this->piecesCount[this->getReferenceGame()->getStarterPlayer() + 1] = 0;

        //prepare board
        this->initializeBoard();
    }

    KnightthroughState::~KnightthroughState()
    {
    }

    bool KnightthroughState::checkForTerminal()
    {
        this->expand();

        bool ret = this->checkForTerminalInBlackRow()
                || this->checkForTerminalInWhiteRow()
                || this->checkForTerminalInPiecesCount()
                || this->getCountOfChildren() == 0;

        this->setTerminal(ret);
        return this->isTerminal();
    }

    void KnightthroughState::expand()
    {
        if(!this->isExpanded())
        {
            KnightthroughState* tempState;

            //allocate children for max
            this->children.reserve(this->getBoardSize() * this->getBoardSize());

            //calculate front row constant
            int frontRowAdder;
            if(this->getActiveSide() == this->getReferenceGame()->getStarterPlayer())
            {
                frontRowAdder = -1;
            }
            else
                frontRowAdder = 1;

            for(unsigned int i=0; i < this->getBoardSize(); i++ )
                for (unsigned int j=0; j < this->getBoardSize(); j++)
                {
                    if(this->getBoard(i,j) == this->getActiveSide())
                    {
                        //check for diagonal left
                        if( i+frontRowAdder >= 0
                            && i+frontRowAdder < this->getBoardSize()
                            && j > 0
                            && this->getBoard(i+frontRowAdder,j-1) == this->nextSide()
                            )
                        {
                            tempState = new KnightthroughState(this);

                            if(tempState->getBoard(i+frontRowAdder,j-1) == this->nextSide())
                                tempState->decPiecesCount(this->nextSide());

                            tempState->setBoard(i+frontRowAdder,j-1, this->getActiveSide());
                            tempState->setBoard(i,j, Generic::__nul);
                            this->children.push_back(tempState);
                        }

                        //check for front
                        if( i+frontRowAdder >= 0
                            && i+frontRowAdder < this->getBoardSize()
                            && this->getBoard(i+frontRowAdder,j) == Generic::__nul
                            )
                        {
                            tempState = new KnightthroughState(this);

                            if(tempState->getBoard(i+frontRowAdder,j) == this->nextSide())
                                tempState->decPiecesCount(this->nextSide());

                            tempState->setBoard(i+frontRowAdder,j, this->getActiveSide());
                            tempState->setBoard(i,j, Generic::__nul);
                            this->children.push_back(tempState);
                        }

                        //check for diagonal right
                        if( i+frontRowAdder >= 0
                            && i+frontRowAdder < this->getBoardSize()
                            && j < this->getBoardSize()-1
                            && this->getBoard(i+frontRowAdder,j+1) == this->nextSide()
                            )
                        {
                            tempState = new KnightthroughState(this);

                            if(tempState->getBoard(i+frontRowAdder,j+1) == this->nextSide())
                                tempState->decPiecesCount(this->nextSide());

                            tempState->setBoard(i+frontRowAdder,j+1, this->getActiveSide());
                            tempState->setBoard(i,j, Generic::__nul);
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
    
    void KnightthroughState::incPiecesCount(unsigned int key)
    {
        this->piecesCount[key]++;
    }

    void KnightthroughState::decPiecesCount(unsigned int key)
    {
        this->piecesCount[key]--;
    }

    unsigned int KnightthroughState::getPiecesCount(unsigned int key)
    {
        return this->piecesCount[key];
    }

    void KnightthroughState::initializeBoard()
    {
        Generic::State::initializeBoard();

        for(unsigned int i=0; i < this->getBoardSize(); i++ )
        {
            for (unsigned int j=0; j < this->getBoardSize(); j++)
            {
                //set board same as parent
                if(this->getParent() == NULL)
                    if(i == 0 || i==1)
                    {
                        this->setBoard(i,j,this->getReferenceGame()->getStarterPlayer()+1);
                        this->incPiecesCount(this->getReferenceGame()->getStarterPlayer()+1);
                    }
                    else if(i == this->getBoardSize()-2 || i == this->getBoardSize()-1)
                    {
                        this->setBoard(i,j,this->getReferenceGame()->getStarterPlayer());
                        this->incPiecesCount(this->getReferenceGame()->getStarterPlayer());
                    }
                    else
                        this->setBoard(i,j,Generic::__nul);
                else
                {
                    this->setBoard(i,j,((KnightthroughState*)this->getParent())->getBoard(i,j));
                    this->incPiecesCount(((KnightthroughState*)this->getParent())->getBoard(i,j));
                }
            }
        }
    }

    bool KnightthroughState::checkForTerminalInBlackRow()
    {
        //check for each column on first row
        unsigned i=0;
        for (unsigned int j=0; j < this->getBoardSize(); j++)
            if(this->getBoard(i,j) == this->getReferenceGame()->getStarterPlayer())
            {
                this->setWinner(this->getReferenceGame()->getStarterPlayer());
                return true;
            }

        return false;
    }

    bool KnightthroughState::checkForTerminalInWhiteRow()
    {
        //check for each column on last row
        unsigned i=this->getBoardSize()-1;
        for (unsigned int j=0; j < this->getBoardSize(); j++)
            if(this->getBoard(i,j) == this->getReferenceGame()->getStarterPlayer()+1)
            {
                this->setWinner(this->getReferenceGame()->getStarterPlayer()+1);
                return true;
            }

        return false;
    }

    bool KnightthroughState::checkForTerminalInPiecesCount()
    {
        if(this->getPiecesCount(this->getActiveSide()) == 0)
        {
            this->setWinner(this->nextSide());
            return true;
        }

        return false;
    }
}

#endif	/* KNIGHTTHROUGHSTATE_CPP */