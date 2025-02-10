#pragma once 
#include <string>
#include <iomanip>
#include <sstream>
class ResultTracker
{
private:
    int score_wins = 0;
    int score_losses =0;
    int dealer_bust_wins=0;
    int bust_losses =0;
    int blackjacks=0;
public:
    ResultTracker() {}
    std::string pretty()
    {
        int total_wins = score_wins + dealer_bust_wins + blackjacks;
        int total_losses = score_losses + bust_losses;
        float perc = 100.*((float)total_wins)/((float)(total_losses+total_wins));
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << perc << "% (";
        oss << total_wins << "/" << total_losses << ")";
        
        oss << " [BJ: " << blackjacks << " SW: " << score_wins << " DB: " << dealer_bust_wins <<"]";
        oss << "[SL: " << score_losses << " BL: " << bust_losses << "]";
        std::string retval = oss.str();
        return retval;
    }
    void score_win() {score_wins +=1;}
    void score_loss() {score_losses+=1;}
    void dealer_bust_win() {dealer_bust_wins+=1;}
    void bust_loss() {bust_losses +=1;}
    void blackjack() {blackjacks+=1;}
};