#ifndef TICTACTOEGAME_H
#define	TICTACTOEGAME_H

#include "../../Game.h"
#include "TicTacToeState.h"

namespace TicTacToe
{
    class TicTacToeGame : public Generic::Game
    {
    public:
        TicTacToeGame(unsigned int bs = 3);
        
        virtual ~TicTacToeGame();
        
        void reset();

    private:
    };
    
    class MisereTicTacToeGame : public TicTacToeGame
    {
    public:
        MisereTicTacToeGame(unsigned int bs = 3);
        
        unsigned int getWinner(Generic::State* s = NULL);
        
        unsigned int getLoser(Generic::State* s = NULL);
    };
}

#endif	/* TICTACTOEGAME_H */

