#include <iostream>
#include "Card.h"
#include "Suit.h"
#include "Deck.h"
#include "Player.h"
#include "Better.h"
#include "Dealer.h"
#include "Game.h"
int main()
{
    std::cout << "Hello, World!" << std::endl;

//    Card card(13,Suit::suits::SPADE);
//    std::cout << card.pretty() << std::endl;

//    Deck deck(1);

//    std::cout << deck.pretty();

    Game game;

    std::shared_ptr<Dealer> d1 = std::make_shared<Dealer>("Chud");
    std::shared_ptr<Player> p1 = std::make_shared<Better>("Dale",1000);
    std::shared_ptr<Player> p2 = std::make_shared<Better>("Geoff",1000);

    game.add_dealer(d1);
    game.add_player(p1);
    game.add_player(p2);

    game.round();

    return 0;
}