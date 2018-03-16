#include "Classes/Simulation.h"
#include "Classes/Settings.h"
#include <iomanip>

void sets()
{
    std::unordered_map<unsigned int, std::unordered_map<unsigned int,std::string> > _prompt;
    std::unordered_map<unsigned int, unsigned int> _column;
    
    unsigned int a=0;
    unsigned int b=0;
    _column[a] = 24;
    _prompt[a][b++] = "Game";
    _prompt[a][b++] = "TicTacToe";
    _prompt[a][b++] = "Misere TicTactoe";
    _prompt[a][b++] = "Breakthrough";
    _prompt[a][b++] = "Misere Breakthrough";
    _prompt[a][b++] = "Knightthrough";
    _prompt[a][b++] = "Misere Knightthrough";
    
    a++; b=0;
    _column[a] = 13;
    _prompt[a][b++] = "Repeat count";
    
    a++; b=0;
    _column[a] = 11;
    _prompt[a][b++] = "Think Time";
    
#ifdef MCTSPLAYER_H
    a++; b=0;
    _column[a] = 15;
    _prompt[a][b++] = "UCT c constant";
#endif
    
    a++; b=0;
    _column[a] = 14;
    _prompt[a][b++] = "Player";
    _prompt[a][b++] = "Random";
    _prompt[a][b++] = "Real";
    _prompt[a][b++] = "Mcts";
    _prompt[a][b++] = "Mcts-MR 1";
    _prompt[a][b++] = "Mcts-MR 2";
    _prompt[a][b++] = "Nmcs 1";
    _prompt[a][b++] = "Nmcs 2";
    _prompt[a][b++] = "Nmcsd 1";
    _prompt[a][b++] = "Nmcsd 2";
    _prompt[a][b++] = "NmcsCOW 1";
    _prompt[a][b++] = "NmcsCOW 2";
    _prompt[a][b++] = "NmcsPOD 1";
    _prompt[a][b++] = "NmcsPOD 2";
    _prompt[a][b++] = "NmcsdCOW 1";
    _prompt[a][b++] = "NmcsdCOW 2";
    _prompt[a][b++] = "NmcsdPOD 1";
    _prompt[a][b++] = "NmcsdPOD 2";
    _prompt[a][b++] = "Lnmcs 1";
    _prompt[a][b++] = "Lnmcs 2";
    _prompt[a][b++] = "Lnmcsd 1";
    _prompt[a][b++] = "Lnmcsd 2";
    
    a++; b=0;
    _column[a] = 8;
    _prompt[a][b++] = "Verbose";
    _prompt[a][b++] = "yes";
    _prompt[a][b++] = "no";
    
    if (isatty(STDIN_FILENO))
    {
        bool cont = true;
        std::cout << std::left;
        for( unsigned int j=0; cont; j++)
        {
            cont = false;
            for(unsigned int i=0; _prompt.count(i) > 0; i++)
            {
                unsigned int w = _column[i];
                if(_prompt[i].count(j) > 0)
                {
                    if(j>0)
                    {
                        std::cout << std::right << std::setw(2) << j << std::left << ".";
                        w-=3;
                    }
                    
                    std::cout << std::setw(w) << _prompt[i][j] << "|";
                    
                    cont = true;
                }
                else
                {
                    std::cout << std::setw(w) << "" << "|";
                }
            }
            std::cout << std::endl;
        }
    }
    
}


/*
 * 
 */
int main(int argc, char** argv)
{
    sets();
    Simulation* sim;
    unsigned int input;
    double inputc;
    double inputd;
    
    if (isatty(STDIN_FILENO))
        std::cout << std::endl
                  << "Choose game: ";
    
    std::cin >> input;
    
    switch(input)
    {
        case 1:
            sim = new Simulation(new TicTacToe::TicTacToeGame());
            break;
        case 2:
            sim = new Simulation(new TicTacToe::MisereTicTacToeGame());
            break;
        case 3:
            sim = new Simulation(new Breakthrough::BreakthroughGame());
            break;
        case 4:
            sim = new Simulation(new Breakthrough::MisereBreakthroughGame());
            break;
        case 5:
            sim = new Simulation(new Knightthrough::KnightthroughGame());
            break;
        case 6:
            sim = new Simulation(new Knightthrough::MisereKnightthroughGame());
            break;
        default:
            std::cout << std::endl << "Wrong input" << std::endl;
            return 1;
    }

    if (isatty(STDIN_FILENO))
        std::cout << std::endl << "Enter repeat count: ";
    
    std::cin >> input;
    
    sim->setRepeatCount(input);
    
    if (isatty(STDIN_FILENO))
        std::cout << std::endl << "Enter think time: ";
    
    std::cin >> inputd;
    
#ifdef MCTSPLAYER_H
    if (isatty(STDIN_FILENO))
        std::cout << std::endl << "UCT c constant: ";
    
    std::cin >> inputc;
    
    if(inputc == 0)
        inputc = Mcts::__c;
#endif
    
    for(unsigned int i = 0; i < sim->getGame()->getMaxPlayerCount(); i++)
    {
        if (isatty(STDIN_FILENO))
            std::cout << std::endl
                      << "Choose player or enter 0 : ";

        std::cin >> input;

        switch(input)
        {
            case 1:
                sim->addPlayer(new Random::RandomPlayer("Random", sim->getGame(), inputd));
                break;
            case 2:
                sim->addPlayer(new Real::RealPlayer("Real", sim->getGame(), inputd));
                break;
            case 3:
                sim->addPlayer(new Mcts::MctsPlayer("Mcts", sim->getGame(), inputd, inputc));
                break;
            case 4:
                sim->addPlayer(new MctsMR::MctsMRPlayer("Mcts-MR1", sim->getGame(), inputd, inputc, 1));
                break;
            case 5:
                sim->addPlayer(new MctsMR::MctsMRPlayer("Mcts-MR2", sim->getGame(), inputd, inputc, 2));
                break;
            case 6:
                sim->addPlayer(new Nmcs::NmcsPlayer("Nmcs1", sim->getGame(), inputd, inputc, 1));
                break;
            case 7:
                sim->addPlayer(new Nmcs::NmcsPlayer("Nmcs2", sim->getGame(), inputd, inputc, 2));
                break;
            case 8:
                sim->addPlayer(new Nmcsd::NmcsdPlayer("Nmcsd1", sim->getGame(), inputd, inputc, 1));
                break;
            case 9:
                sim->addPlayer(new Nmcsd::NmcsdPlayer("Nmcsd2", sim->getGame(), inputd, inputc, 2));
                break;
            case 10:
                sim->addPlayer(new NmcsCOW::NmcsCOWPlayer("NmcsCOW1", sim->getGame(), inputd, inputc, 1));
                break;
            case 11:
                sim->addPlayer(new NmcsCOW::NmcsCOWPlayer("NmcsCOW2", sim->getGame(), inputd, inputc, 2));
                break;
            case 12:
                sim->addPlayer(new NmcsPOD::NmcsPODPlayer("NmcsPOD1", sim->getGame(), inputd, inputc, 1));
                break;
            case 13:
                sim->addPlayer(new NmcsPOD::NmcsPODPlayer("NmcsPOD2", sim->getGame(), inputd, inputc, 2));
                break;
            case 14:
                sim->addPlayer(new NmcsdCOW::NmcsdCOWPlayer("NmcsdCOW1", sim->getGame(), inputd, inputc, 1));
                break;
            case 15:
                sim->addPlayer(new NmcsdCOW::NmcsdCOWPlayer("NmcsdCOW2", sim->getGame(), inputd, inputc, 2));
                break;
            case 16:
                sim->addPlayer(new NmcsdPOD::NmcsdPODPlayer("NmcsdPOD1", sim->getGame(), inputd, inputc, 1));
                break;
            case 17:
                sim->addPlayer(new NmcsdPOD::NmcsdPODPlayer("NmcsdPOD2", sim->getGame(), inputd, inputc, 2));
                break;
            case 18:
                sim->addPlayer(new Lnmcs::LnmcsPlayer("Lnmcs1", sim->getGame(), inputd, inputc, 1));
                break;
            case 19:
                sim->addPlayer(new Lnmcs::LnmcsPlayer("Lnmcs2", sim->getGame(), inputd, inputc, 2));
                break;
            case 20:
                sim->addPlayer(new Lnmcsd::LnmcsdPlayer("Lnmcsd1", sim->getGame(), inputd, inputc, 1));
                break;
            case 21:
                sim->addPlayer(new Lnmcsd::LnmcsdPlayer("Lnmcsd2", sim->getGame(), inputd, inputc, 2));
                break;
            default:
                std::cout << std::endl << "Wrong input" << std::endl;
                return 1;
        }
    }
    
    if (isatty(STDIN_FILENO))
        std::cout << std::endl << "Verbose: ";
    
    std::cin >> input;
    
    if(input == 1)
        sim->setVerbose();
    
    if(sim->run())
        sim->printStatistics();
    else
        std::cerr << std::endl << "Run failed" << std::endl;
    
    delete sim;
    
    return 0;
}