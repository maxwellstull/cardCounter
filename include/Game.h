#pragma once 
#include "Dealer.h"
#include "Counter.h"
#include "Deck.h"
#include <vector>
#include <memory>
#include <unordered_map>

class Game
{
private:
    std::shared_ptr<Dealer> _dealer;
    std::vector<std::shared_ptr<Player>> players;
    Deck shoe;
    std::unordered_map<std::string,int> pot;

public:
    Game();
    void add_player(std::shared_ptr<Player> p)
    {
        players.push_back(p);
    }
    void add_dealer(std::shared_ptr<Dealer> d)
    {
        players.insert(players.begin(), d);
        _dealer = d;
    }
    void round();

};