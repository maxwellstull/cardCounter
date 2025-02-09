#include "Deck.h"
#include "Suit.h"
#include <random>
#include <algorithm>

Deck::Deck(int decks)
{
    _decks = decks;
    generate_deck();
}

void Deck::generate_deck()
{
    for(int deck_num = 0; deck_num < _decks; deck_num++)
    {
        for(int suit_num = 0; suit_num < 4; suit_num++)
        {
            for(int rank_num = 1; rank_num < 14; rank_num++)
            _deck.push_back(Card(rank_num, Suit::suits(suit_num)));
        }
    }
}

std::string Deck::pretty()
{
    std::string retval = "";
    for (Card card : _deck)
    {
        retval += card.pretty() + ", ";
    }
    return retval;
}

void Deck::shuffle()
{
//    std::random_device rd;
//    std::default_random_engine gen(rd);
    std::random_device rd;
    std::mt19937 engine(rd());
    std::shuffle(std::begin(_deck), std::end(_deck), engine);
}

void Deck::reset()
{
    _deck.insert(_deck.end(), _dealt.begin(), _dealt.end());
    shuffle();
}

Card Deck::draw()
{
    Card retval = _deck.back();
    _deck.pop_back();
    _dealt.push_back(retval);
    return retval;
}