#pragma once 
#include "Player.h"

class Counter : public Player 
{
private:
    int _count = 0;
public:
    void count(Card card);

};