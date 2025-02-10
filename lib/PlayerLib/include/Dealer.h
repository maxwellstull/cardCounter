#pragma once
#include "Player.h"
class Dealer : public Player {
public:
    Dealer(std::string name, strategies strat) : Player(name, strat) {}
    Card get_dealer_upcard() {return get_upcard();}
};