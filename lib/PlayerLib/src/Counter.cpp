#include "Counter.h"

void Counter::count(Card card)
{
    if(card.is_ace())
    {
        _count -= 1;
    }
    else if(card.get_value() == 10)
    {
        _count -= 1;
    }
    else if(card.get_value() <= 6)
    {
        _count += 1;
    }
}