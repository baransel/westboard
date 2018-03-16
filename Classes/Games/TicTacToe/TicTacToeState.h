#ifndef TICTACTOESTATE_H
#define	TICTACTOESTATE_H

#include "../../State.h"

namespace TicTacToe
{
    class TicTacToeState : public Generic::State
    {
    public:
        TicTacToeState(Generic::Game* g, unsigned int bs);
        
        TicTacToeState(TicTacToeState* p);

        virtual ~TicTacToeState();
        
        bool checkForTerminal();
        
        void expand();
        
    private:
        
        void initializeBoard();
        
        bool checkForTerminalInRows();
        
        bool checkForTerminalInColumns();
        
        bool checkForTerminalInDioganal();
        
        bool checkForTerminalInReverseDioganal();
    };
}
#endif	/* TICTACTOESTATE_H */