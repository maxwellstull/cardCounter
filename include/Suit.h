#pragma once
#include <string>
#include <vector>

class Suit
{
public:
enum suits {
    SPADE=1,
    HEART=2,
    CLUB=3,
    DIAMOND=4
};
private:
    suits _suit;
    std::vector<std::string> suit_txt = {"♠","♥","♣","♦"};
public:
    Suit(suits suit);
    std::string pretty();
};