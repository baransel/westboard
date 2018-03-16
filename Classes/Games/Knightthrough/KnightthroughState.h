#ifndef KNIGHTTHROUGHSTATE_H
#define	KNIGHTTHROUGHSTATE_H

#include "../../State.h"

namespace Knightthrough
{
    class KnightthroughState : public Generic::State
    {
    public:
        KnightthroughState(Generic::Game* g, unsigned int bs);
        
        KnightthroughState(KnightthroughState* p);

        virtual ~KnightthroughState();
        
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

#endif	/* KNIGHTTHROUGHSTATE_H */