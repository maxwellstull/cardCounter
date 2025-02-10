#pragma once 
#include "Card.h"
#include "Suit.h"
#include <algorithm>
#include <random>

class Deck
{
private:
    std::vector<Card> _deck;
    std::vector<Card> _dealt;
    int _decks;
    std::mt19937 engine;
public:
    Deck(int decks);
    std::string pretty();
    void reset();
    void shuffle();
    Card draw();
private:
    void generate_deck();
    
};