#include "Card.h"
#include "Suit.h"

Card::Card(int rank, Suit::suits suit) : _rank(rank), _suit(suit)
{

}

std::string Card::pretty()
{
    std::vector<std::string> ranks = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    return ranks[_rank-1] + _suit.pretty();
}
int Card::get_value()
{
    if (_rank > 10)
    {
        return 10;
    }
    else
    {
        return _rank;
    }
}