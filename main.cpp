#include <iostream>
#include "Card.h"
#include "Suit.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Game.h"
int main()
{
    Game game;

    std::shared_ptr<Dealer> d1 = std::make_shared<Dealer>("Chud", strategies::HIT_17);
    std::shared_ptr<Player> p1 = std::make_shared<Player>("Dale, Hit 16",strategies::HIT_16);
    std::shared_ptr<Player> p2 = std::make_shared<Player>("Geoff, Hit 17",strategies::HIT_17);
    std::shared_ptr<Player> p3 = std::make_shared<Player>("Jeff, Hit 18",strategies::HIT_18);
    std::shared_ptr<Player> p4 = std::make_shared<Player>("Anderdingus, Perfect Basic Hard",strategies::PERFECT_BASIC_HARD);

    game.add_dealer(d1);
    game.add_player(p1);
    game.add_player(p2);
    game.add_player(p3);
    game.add_player(p4);

    for(int i =0; i < 1000000; i++)
    {    
        if (i % 1000==0)
        {
            std::cout << i << std::endl;
        }
        game.round();
    }

    std::cout<<p1->get_name()<<std::endl<<" "<<p1->pretty_results()<<std::endl;
    std::cout<<p2->get_name()<<std::endl<<" "<<p2->pretty_results()<<std::endl;
    std::cout<<p3->get_name()<<std::endl<<" "<<p3->pretty_results()<<std::endl;
    std::cout<<p4->get_name()<<std::endl<<" "<<p4->pretty_results()<<std::endl;

    return 0;
}