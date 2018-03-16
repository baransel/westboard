#ifndef TICTACTOEGAME_CPP
#define	TICTACTOEGAME_CPP

#include "TicTacToeGame.h"

namespace TicTacToe
{
    TicTacToeGame::TicTacToeGame(unsigned int bs) : Game(bs, 2)
    {
        this->reset();

        //add X and O players
        this->addPlayer("X");
        this->addPlayer("O");
    }

    TicTacToeGame::~TicTacToeGame()
    {
    }

    void TicTacToeGame::reset()
    {
        Generic::Game::reset();
        this->setRootState(new TicTacToeState(this, this->getBoardSize()));
        this->setCurrentState(this->getRootState());
    }
    
    MisereTicTacToeGame::MisereTicTacToeGame(unsigned int bs) : TicTacToeGame(bs)
    {
    }
    
    unsigned int MisereTicTacToeGame::getWinner(Generic::State* s)
    {
        return TicTacToeGame::getLoser(s);
    }

    unsigned int MisereTicTacToeGame::getLoser(Generic::State* s)
    {
        return TicTacToeGame::getWinner(s);
    }
}

#endif	/* TICTACTOEGAME_CPP */