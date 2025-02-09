#include "Better.h"

Better::Better(std::string name, float cash) : Player(name)
{
    _cash = cash;
}
float Better::get_bet()
{
    float bet = 100.;
    _cash -= bet;
    return bet;
}
void Better::get_winnings(float amnt)
{
    _cash += amnt;
}