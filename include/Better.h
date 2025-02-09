#pragma once
#include "Player.h"

class Better : public Player {
private:
    float _cash;
public:
    Better(std::string name, float cash);
    float get_bet();
    void get_winnings(float amnt);
};