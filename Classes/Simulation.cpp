#ifndef SIMULATION_CPP
#define	SIMULATION_CPP

#include "Simulation.h"

Simulation::Simulation(Generic::Game* g)
{
    this->game = g;
    this->setVerbose(false);
}

Generic::Game* Simulation::getGame()
{
    return this->game;
}

void Simulation::setRepeatCount(unsigned int r)
{
    this->repeatCount = r;
}

unsigned int Simulation::getRepeatCount()
{
    return this->repeatCount;
}

void Simulation::setVerbose(bool v)
{
    this->verbose = v;
}

bool Simulation::getVerbose()
{
    return this->verbose;
}

void Simulation::addPlayer(Generic::Player* p)
{
    this->players.push_back(p);
}

bool Simulation::run()
{
    //full reset players
    for(std::vector<Generic::Player*>::iterator p = this->players.begin(); p != this->players.end(); p++)
    {
        (*p)->reset();
    }

    for(unsigned int count = 0; count < this->getRepeatCount(); count++)
    {
        //reset game
        this->game->reset();

        //expand current (initially root) state
        this->game->getCurrentState()->expand();

        while( ! this->game->getCurrentState()->isTerminal() )
        {
            //check for each player turns
            for(std::vector<Generic::Player*>::iterator p = players.begin(); p != players.end(); p++)
            {
                //check player turn
                if( this->game->getTurn() == (*p)->getSide() )
                {
                    //do move
                    (*p)->move();

                    //if verbose, print information about new state
                    if(this->getVerbose())
                    {
                        std::cout.precision(6);
                        std::cout << std::endl
                                  << "----------------------------------------" << std::endl
                                  << "Player " << (*p)->getName() << " has moved." << std::endl
                                  << "Think Time(s) : " << std::fixed << (*p)->getThinkTime() << " (Max: " << (*p)->getTimeLimit() << ")" << std::endl
                                  << "Think Count : " << (*p)->getThinkCount() << std::endl;
                        std::cout << "Current state id : " << this->game->getCurrentState()->getId() << "\t"
                                  << "Possible Action Count : " << this->game->getCurrentState()->getCountOfChildren() << std::endl;

                        this->game->getCurrentState()->print();
                        std::cout << "----------------------------------------" << std::endl;
                    }

                    break;
                }
            }
        }

        //game finished, calculate player statistics
        for(std::vector<Generic::Player*>::iterator p = this->players.begin(); p != this->players.end(); p++)
        {
            if( (*p)->getSide() == this->game->getWinner() )
                (*p)->incWinCount();
            else if( (*p)->getSide() == this->game->getLoser() )
                (*p)->incLoseCount();
            else
                (*p)->incDrawCount();
        }

        if(this->getVerbose())
        {
            std::cout << "----------------------------------------" << std::endl
                      << "Game finished. " << std::endl;
            this->game->getCurrentState()->print();
            std::cout << "----------------------------------------" << std::endl;
        }

        //swap user sides
        this->swapSides();

        //soft reset player
        for(std::vector<Generic::Player*>::iterator p = this->players.begin(); p != this->players.end(); p++)
        {
            (*p)->reset(false);
        }

    }

    //all games finished
    return true;
}

void Simulation::printStatistics()
{
    for(std::vector<Generic::Player*>::iterator p = this->players.begin(); p != this->players.end(); p++)
    {
        std::cout << (*p)->getName() << " : Win( " << (*p)->getWinCount() << ") : Lose(" << (*p)->getLoseCount() << ") : Draw(" << (*p)->getDrawCount() << ")" << std::endl;
    }
}

Simulation::~Simulation()
{
}

void Simulation::swapSides()
{
    std::vector<Generic::Player*>::iterator prev = this->players.begin();
    unsigned int tempSide = (*prev)->getSide();
    std::vector<Generic::Player*>::iterator cur = prev+1;

    while( cur != this->players.end() )
    {
        (*prev)->setSide((*cur)->getSide());
        prev = cur++;
    }
    (*prev)->setSide(tempSide);
}

#endif	/* SIMULATION_CPP */