#pragma once 
#include <vector>
#include "Card.h"
#include "resources.h"

class Hand 
{
private:
    std::vector<Card> hand;
    int sum_low = 0;
    int sum_high = 0;
    int aces = 0;
    int non_ace_total = 0;
public:
    Hand();
    void add_card(Card card);
    void calculate_hand_sum();
    void reset();
//    action ask();
    int final();
    int get_sum_low() {return sum_low;}
    int get_sum_high() {return sum_high;}
    std::string pretty();
};