#include "Player.h"

Player::Player(std::string name, strategies strat)
{
    _name = name;
    _strat = strat;
}
void Player::deal(Card card)
{
    _hand.add_card(card);
}

int Player::final()
{
    return _hand.final();
}
void Player::reset()
{
    _hand.reset();
}

action Player::ask(Card dealer_upcard)
{
    if (_hand.get_sum_high() == 21)
    {
        return action::STAND;
    }
    switch(_strat)
    {
        case( strategies::HIT_16):
        {
            if (_hand.get_sum_low() <= 16)
            {
                return action::HIT;
                break;
            }
            else
            {
                return action::STAND;
                break;
            }
        }
        case(strategies::HIT_17):
        {
            if(_hand.get_sum_low() <= 17)
            {
                return action::HIT;
                break;
            }
            else 
            {
                return action::STAND;
                break;
            }
        }
        case(strategies::HIT_18):
        {
            if(_hand.get_sum_low() <= 17)
            {
                return action::HIT;
                break;
            }
            else 
            {
                return action::STAND;
                break;
            }
        }
        case(strategies::PERFECT_BASIC_HARD):
        {
            int total = _hand.get_sum_low();
            int dealer_value = dealer_upcard.get_value();
            if (_hand.get_aces() == 0) //hard totals
            {
                if(total >= 17)
                {
                    return action::STAND;
                }
                else if(total == 11)
                {
                    return action::DOUBLE_HIT;
                }
                else if(dealer_value <= 6 && total >= 13)
                {
                    return action::STAND;
                }
                else if(dealer_value <= 6 && dealer_value >= 4 && total==12)
                {
                    return action::STAND;
                }
                else if(dealer_value <= 9 && total == 10)
                {
                    return action::DOUBLE_HIT;
                }
                else if(dealer_value <= 6 && dealer_value >= 3 && total == 9)
                {
                    return action::DOUBLE_HIT;
                }
                else
                {
                    return action::HIT;
                }
            }
            else 
            {
                if (total >= 17)
                {
                    return action::STAND;
                }
                else 
                {
                    return action::HIT;
                }
            }
        }
        default:{
            return action::STAND;
        }
    }
}


std::string Player::pretty_hand()
{
    return _hand.pretty();
}

float Player::get_bet()
{
    float bet = 100.;
    _cash -= bet;
    return bet;
}
void Player::get_winnings(float amount)
{
    _cash += amount;
}
void Player::withdraw(float amount)
{
    _cash -= amount;
}