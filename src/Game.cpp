#include "Game.h"
#include <iostream>
#include "resources.h"
Game::Game() : shoe(2)
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
    Card dealer_upcard = _dealer->get_dealer_upcard();
    //players play
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
            player_action = player->ask(dealer_upcard);
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
                case(action::DOUBLE_HIT):
                {
                    player->withdraw(pot[player->get_name()]);
                    pot[player->get_name()] *= 2;
                    player->deal(shoe.draw());
                    stand=true;
                    break;
                }
                default:
                {
                    stand=true;
                    break;
                }
            }
        }
    }

    while(_dealer->ask(dealer_upcard) != action::STAND)
    {
        _dealer->deal(shoe.draw());
    }
    int dealer_score = _dealer->final();
//    std::cout << "Dealer: " <<dealer_score<<" "<<_dealer->pretty_hand() << std::endl;
    first = true;
    for( auto player : players)
    {
        if (first) 
        {
            first = false;
            continue;
        }
        int player_score = player->final();
//        std::cout << "Player " << player->get_name() << ": " << player_score<<" "<<player->pretty_hand()<<std::endl;
        if (player_score == 21 && player->get_hand_length() == 2)
        {
            //blackjack
            player->blackjack();
            player->get_winnings(pot[player->get_name()] * (1. + 1.5));
        }
        else if(player_score == -1)
        {
            player->bust_loss();
        }
        else if(dealer_score == -1)
        {
            player->dealer_bust_win();
            player->get_winnings(pot[player->get_name()] * 2.);
        }
        else
        {
            if (player_score > dealer_score)
            {
                player->score_win();
                player->get_winnings(pot[player->get_name()] * 2.);
            }
            else
            {
                player->score_loss();
            }
        }
        player->reset();
    }

    _dealer->reset();
}