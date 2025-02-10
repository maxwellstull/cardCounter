#include "Suit.h"

Suit::Suit(suits suit)
{
    _suit = suit;
}

std::string Suit::pretty()
{
    return suit_txt[_suit-1];
}