#ifndef BREAKTHROUGHSTATE_H
#define	BREAKTHROUGHSTATE_H

#include "../../State.h"

namespace Breakthrough
{
    class BreakthroughState : public Generic::State
    {
    public:
        BreakthroughState(Generic::Game* g, unsigned int bs);
        
        BreakthroughState(BreakthroughState* p);

        virtual ~BreakthroughState();
        
        bool checkForTerminal();
        
        void expand();
        
    private:
        std::unordered_map<unsigned int, unsigned int> piecesCount;
        
        void incPiecesCount(unsigned int key);
        
        void decPiecesCount(unsigned int key);
        
        unsigned int getPiecesCount(unsigned int key);
        
        void initializeBoard();
        
        bool checkForTerminalInBlackRow();
        
        bool checkForTerminalInWhiteRow();
        
        bool checkForTerminalInPiecesCount();
    };
}

#endif	/* BREAKTHROUGHSTATE_H */