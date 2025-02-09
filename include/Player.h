#pragma once
#include "Hand.h"
#include "resources.h"

class Player
{
private:
    std::string _name;
    Hand _hand;
    strategies _strat = strategies::HIT_16;
public:
    Player(std::string name);
    void deal(Card card);
    action ask();
    int final();
    void reset();
    std::string get_name() {return _name;}
    float get_bet();
    std::string pretty_hand();
    

};