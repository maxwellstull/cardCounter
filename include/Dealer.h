#pragma once
#include "Player.h"
class Dealer : public Player {
public:
    Dealer(std::string name) : Player(name) {}
};