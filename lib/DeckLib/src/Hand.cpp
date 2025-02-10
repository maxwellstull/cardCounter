#include "resources.h"
#include "Hand.h"

Hand::Hand()
{

}

void Hand::add_card(Card card)
{
    hand.push_back(card);
    if(card.is_ace())
    {
        aces += 1;
    }
    else
    {
        non_ace_total += card.get_value();
    }
    calculate_hand_sum();
}

void Hand::calculate_hand_sum()
{
    sum_low = 0;
    sum_high = 0;
    if(aces == 0)
    {
        int sum = 0;
        for(Card card : hand)
        {
            sum += card.get_value();
        }
        sum_low = sum;
        sum_high = sum;
    }
    else
    {
        int value = 0;
        for(Card card : hand)
        {
            value = card.get_value();
            if(value != 1)
            {
                sum_low += value;
                sum_high += value;
            }
        }
        sum_low += aces;
        sum_high += 10 + aces;
    }
}

void Hand::reset()
{
    hand.clear();
    sum_low = 0;
    sum_high = 0;
    aces = 0;
    non_ace_total = 0;
}

int Hand::final()
{
    if (sum_high <= 21)
    {
        return sum_high;
    }
    else
    {
        if( sum_low > 21)
        {
            return -1;
        }
        else 
        {
            return sum_low;
        }
    }
}

std::string Hand::pretty()
{
    std::string retval = "[";
    for(Card card : hand)
    {
        retval += card.pretty() + ",";
    }
    retval += ']';
    return retval;
}