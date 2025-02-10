#pragma once 
#include <string>
#include "Suit.h"

class Card 
{
private:
    int _rank;
    Suit _suit;
public:
    Card(int rank, Suit::suits suit);
    std::string pretty();
    bool is_ace() {return (_rank==1);}
    int get_value();
};