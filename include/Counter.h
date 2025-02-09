#pragma once 
#include "Better.h"

class Counter : public Better 
{
private:
    int _count = 0;
public:
    void count(Card card);

};