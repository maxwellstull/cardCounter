#include "Game.h"
#include <iostream>
#include "resources.h"
Game::Game() : shoe(1)
{

}

void Game::round()
{
    shoe.reset();

    //betting
    bool first = true;
    for( auto player : players)
    {
        if (first) 
        {
            first = false;
            continue;
        }
        pot[player->get_name()] = player->get_bet();

    }
    //initial deal
    for(int i=0; i < 2; i++)
    {
        for (auto player : players)
        {
            player->deal(shoe.draw());
        }
    }

    first = true;
    action player_action;
    for( auto player : players)
    {
        if (first) 
        {
            first = false;
            continue;
        }
        bool stand = false;
        while(!stand)
        {
            player_action = player->ask();
            switch(player_action)
            {
                case(action::STAND):
                {
                    stand = true;
                    break;
                }
                case(action::HIT):
                {
                    player->deal(shoe.draw());
                    break;
                }
            }
        }
    }

    while(_dealer->ask() != action::STAND)
    {
        _dealer->deal(shoe.draw());
    }
    int dealer_score = _dealer->final();
    std::cout << "Dealer: " <<dealer_score << std::endl;
    first = true;
    for( auto player : players)
    {
        if (first) 
        {
            first = false;
            continue;
        }
        int player_score = player->final();
        std::cout << "Player " << player->get_name() << ": " << player_score<<" "<<player->pretty_hand()<<std::endl;
    }
}