#include "Player.h"

Player::Player(std::string name)
{
    _name = name;

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

action Player::ask()
{
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
        default:{
            return action::STAND;
        }
    }
}

float Player::get_bet()
{
    return 0;
}

std::string Player::pretty_hand()
{
    return _hand.pretty();
}