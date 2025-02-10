#pragma once
#include "Hand.h"
#include "resources.h"
#include "ResultTracker.h"
class Player
{
private:
    std::string _name;
    Hand _hand;
    strategies _strat = strategies::HIT_16;
    ResultTracker results;
    float _cash;
public:
    Player(std::string name, strategies strat);
    void deal(Card card);
    action ask(Card dealer_upcard);
    int final();
    void reset();
    std::string get_name() {return _name;}
    float get_bet();
    std::string pretty_hand();
    Card get_upcard() {return _hand.get_upcard();}
    void get_winnings(float amount);
    void withdraw(float amount);    
    int get_hand_length() {return _hand.length();}

    void score_win() {results.score_win();}
    void score_loss() {results.score_loss();}
    void dealer_bust_win() {results.dealer_bust_win();}
    void bust_loss() {results.bust_loss() ;}
    void blackjack() {results.blackjack();}
    std::string pretty_results() {return results.pretty();}
};