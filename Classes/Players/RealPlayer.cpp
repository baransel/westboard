#ifndef REALPLAYER_CPP
#define	REALPLAYER_CPP

#include "RealPlayer.h"

namespace Real
{
    RealPlayer::RealPlayer(std::string n, Generic::Game* g, unsigned int mt) : Generic::Player(n, g, mt)
    {
    }

    RealPlayer::RealPlayer(Generic::Game* g, unsigned int mt) : Generic::Player("Real", g, mt)
    {
    }

    RealPlayer::~RealPlayer()
    {
    }

    void RealPlayer::move()
    {
        if(this->getSide() == this->getGame()->getTurn())
        {
            //it should be expanded, but check it anyway
            this->getGame()->getCurrentState()->expand();

            //print current state
            this->getGame()->getCurrentState()->print();

            //print possible states
            std::cout << "Possible moves :" << std::endl;

            std::vector< std::vector<std::string> > s;
            s.reserve(this->getGame()->getCurrentState()->getCountOfChildren());

            std::vector<std::string> tempVector;
            unsigned int maxStateHeight = 0;
            unsigned int maxStateWidth = 0;

            for(unsigned int i=0; i < this->getGame()->getCurrentState()->getCountOfChildren(); i++)
            {
                tempVector = this->getGame()->getCurrentState()->getChild(i)->getPrint();
                s.push_back(tempVector);
                //s[i] = tempVector;
                if(maxStateHeight < tempVector.size())
                    maxStateHeight = tempVector.size();
                if(maxStateWidth < utf8::distance(tempVector.front().begin(), tempVector.front().end()))
                    maxStateWidth = utf8::distance(tempVector.front().begin(), tempVector.front().end());
            }

            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

            unsigned int statePerRow = w.ws_col / (maxStateWidth + 1);

            unsigned int r = 0;
            do
            {
                for(unsigned int j = 0; j < maxStateHeight; j++)
                {
                    for(unsigned int i = r*statePerRow; i < ((r+1)*statePerRow) && i < s.size(); i++)
                    {
                        if( j < s[i].size() )
                            std::cout << s[i][j] << " ";
                        else
                            std::cout << s[0][0] << " ";
                    }

                    std::cout << std::endl;
                }
                r++;
            } while(r < s.size()/ (float)statePerRow);

            std::cout << "Please select: ";

            unsigned int choice;
            std::cin >> choice;

            this->getGame()->setCurrentState(
                this->getGame()->getCurrentState()->getChild(
                    choice
                )
            );

            //expand it
            this->getGame()->getCurrentState()->expand();

        }
    }
}

#endif	/* REALPLAYER_CPP */