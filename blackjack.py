import random
from enum import Enum

BLACKJACK_ODDS = 1.5

class Actions(Enum):
    HIT = 0,
    STAND = 1,

class Strategies(Enum):
    HIT_16 = 0,
    HIT_17 = 1,
    HIT_18 = 2,
    LET_DEALER_BUST = 3,
    COUNT = 4,
    PERFECT_BASIC_HARD = 5,

class ResultTracker:
    def __init__(self):
        self.score_wins = 0
        self.score_losses = 0
        self.dealer_bust_win = 0
        self.bust_loss = 0
        self.blackjack = 0
    def __repr__(self):
        total_wins = self.score_wins + self.dealer_bust_win + self.blackjack
        total_loss = self.score_losses + self.bust_loss

        return "{wins}/{ls}    [BJ: {bj} S:{sw} DB:{db}] / [L:{sl} B:{bl}]".format(wins=total_wins, sw=self.score_wins, db=self.dealer_bust_win, ls=total_loss, sl = self.score_losses, bl=self.bust_loss, bj = self.blackjack)

class Card:
    def __init__(self, value, suit, deck_id):
        self.value = value
        self.suit = suit
        self.deck_id = deck_id
    def __repr__(self):
        return str(self.value) + str(self.suit)
    def get_value(self):
        if self.value.isnumeric():
            return int(self.value)
        elif self.value == "A":
            return "A"
        else:
            return 10
        
class Hand:
    def __init__(self):
        self.hand = []
        self.sum_low = 0
        self.sum_high = 0
        self.aces = 0

    def add_card(self, card):
        self.hand.append(card)
        if(card.value == "A"):
            self.aces += 1
        self.calc_hand_sum()
    def calc_hand_sum(self):
        self.sum_low = 0
        self.sum_high = 0
        if self.aces == 0: # the easy way
            sum = 0
            for card in self.hand:
                sum += card.get_value()
            self.sum_low = sum 
            self.sum_high = sum
        else:   
            ace_ct = self.aces
            # 1: 1, 11
            # 2: 2, 12, 22
            # 3: 3, 13, 23, 33
            # 4: 4, 14, 24, 34, 44
            sum_low = 0
            sum_high = 0
            for card in self.hand:
                val = card.get_value()
                if val != "A":
                    sum_low += int(val)
                    sum_high += int(val)
                else:
                    # amount of aces dont matter, if there is N aces it'll only be N and 10+N as our options
                    pass
            sum_low += 1*self.aces
            sum_high += 10 + (1*self.aces)
            self.sum_low = sum_low
            self.sum_high = sum_high

    def reset(self):
        self.hand = []
        self.sum_low = 0
        self.sum_high = 0
        self.aces = 0

    def ask(self):
        if self.sum_low < 17:
            return Actions.HIT
        else:
            return Actions.STAND
    def final(self):
        if self.sum_high == 21:
            return 21
        if self.sum_low == 21:
            return 21
        if self.sum_high < 21:
            return self.sum_high
        else:
            if self.sum_low > 21:
                return -1
            else:
                return self.sum_low
    def __repr__(self):
        return str(self.hand)

    
class Deck:
    def __init__(self, decks=6):
        suits = ["♠","♥","♣","♦"]
        values = ["2","3","4","5","6","7","8","9","10","J","Q","K","A"]
        self.deck = []
        self.split_card_idx = 0
        for deck_id in range(0, decks):
            for suit in suits:
                for value in values:
                    cardy = Card(value, suit, deck_id)
                    self.deck.append(cardy)
        self.dealt = []
    def shuffle(self):
        random.shuffle(self.deck)
    def draw(self):
        val = self.deck.pop(0)
        self.dealt.append(val)
        self.split_card_idx -= 1
        return val
    def reset(self):
        self.deck.extend(self.dealt)
        self.dealt = []

class Player:
    def __init__(self, name, strategy):
        self.hand = Hand()
        self.name = name
        self.results = ResultTracker()
        self.strategy = strategy
    def deal(self, card):
        self.hand.add_card(card)
    def ask(self, dealer_upcard):
        if self.hand.sum_high == 21:
            return Actions.STAND
        match(self.strategy):
            case Strategies.HIT_16:
                if self.hand.sum_low <= 16:
                    return Actions.HIT
                else:
                    return Actions.STAND
            case Strategies.HIT_17:
                if self.hand.sum_low <= 17:
                    return Actions.HIT
                else:
                    return Actions.STAND
            case Strategies.HIT_18:
                if self.hand.sum_low <= 18:
                    return Actions.HIT
                else:
                    return Actions.STAND
            case Strategies.PERFECT_BASIC_HARD:
                total = self.hand.sum_low
                if self.hand.aces == 0: # hard totals
                    if total >= 17:
                        return Actions.STAND
                    elif total == 11:
                        return Actions.HIT
                    elif dealer_upcard <= 6 and total >= 13:
                        return Actions.STAND
                    elif dealer_upcard <= 6 and dealer_upcard >= 4 and total == 12:
                        return Actions.STAND
                    elif dealer_upcard <= 9 and total == 10:
                        return Actions.HIT
                    elif dealer_upcard <= 6 and dealer_upcard >= 3 and total == 9:
                        return Actions.HIT
                else:
                    if total >= 17:
                        return Actions.STAND 
                    else:
                        return Actions.HIT


#        return self.hand.ask()
    def __repr__(self):
        sum = ""
        if self.hand.sum_low == self.hand.sum_high:
            sum = str(self.hand.sum_low)
        else:
            sum = str(self.hand.sum_low) + ", " + str(self.hand.sum_high)
        return self.name + "-" + str(sum) +" " + str(self.hand)
    def final(self):
        return self.hand.final()
    def reset(self):
        self.hand.reset()
class Better(Player):
    def __init__(self, name, strategy, cash):
        self.cash = cash
        super().__init__(name, strategy)
    def get_bet(self):
        bet = 500
        self.cash -= bet
        return bet
    def get_winnings(self, amnt):
        self.cash += amnt



class Dealer(Player):
    pass
#    def __init__(self, name, strategy):
#        pass


class Counter(Better):
    def __init__(self, name):
        super().__init__(name, Strategies.COUNT)
        self.count = 0
        self.cards = 0
    def count(self, card):
        self.cards += 1
        value = card.get_value()
        if value == "A":
            self.count -= 1
        elif value == 10:
            self.count -= 1
        elif value <= 6:
            self.count += 1
    def ask(self):
        pass
class Game():
    def __init__(self, shoe):
        self.dealer = None
        self.players = []
        self.shoe = shoe
        self.table = {}
    def add_player(self, player):
        self.players.append(player)
    def add_dealer(self, dealer):
        self.players.insert(0, dealer)
        self.dealer = dealer
    def round(self):
        if self.shoe.split_card_idx <= 0:
            self.shoe.split_card_idx = random.randint(int(len(self.shoe.deck)/2), len(self.shoe.deck))
            self.shoe.reset()
            self.shoe.shuffle()

        # Betting
        for player in self.players[1:]:
            self.table[player] = player.get_bet()



        # Initial deal
        for _ in range(0, 2):
            for player in self.players:
                player.deal(self.shoe.draw())

        dealer_upcard = self.dealer.hand.hand[0].get_value()
        if dealer_upcard == "A":
            dealer_upcard = 11
        # Players
        for player in self.players[1:]:
            while(player.ask(dealer_upcard) != Actions.STAND):
                player.deal(self.shoe.draw())
        # Dealer
        while self.dealer.ask(dealer_upcard) != Actions.STAND:
            self.dealer.deal(self.shoe.draw())
        
        dealer_score = self.dealer.final()
        for player in self.players[1:]:
            player_score = player.final()
            if player_score == 21 and len(player.hand.hand) == 2:
                # blackjack
                player.get_winnings(self.table[player] + (self.table[player] * (BLACKJACK_ODDS)))
                player.results.blackjack += 1
            elif player_score == -1:
                #print(player.name, "loses (busts)")
                player.results.bust_loss += 1
            elif dealer_score == -1:
                #print(player.name, "wins (dealer busts)")
                player.get_winnings(self.table[player] * 2)
                player.results.dealer_bust_win += 1
            else:
                if player_score > dealer_score:
                    #print(player.name, "wins (score)")
                    player.get_winnings(self.table[player] * 2)
                    player.results.score_wins += 1
                else:
                    #print(player.name, "loses (score)")
                    player.results.score_losses += 1
#        print(self.players)
        for player in self.players:
            player.reset()


def main():
    shoe = Deck(8)

    game = Game(shoe)
    game.shoe.shuffle()

    d = Dealer("Chud", Strategies.HIT_16)
    p1 = Better("Phil", Strategies.HIT_16, 10000)
    p2 = Better("Anderdingle", Strategies.HIT_17, 10000)
    p3 = Better("Geoff", Strategies.PERFECT_BASIC_HARD, 10000)
    game.add_player(p1)
    game.add_player(p2)
    game.add_player(p3)
    game.add_dealer(d)

    for _ in range(0, 50000):
        game.round()


    print(p1.name, p1.cash, p1.results)
    print(p2.name, p2.cash, p2.results)
    print(p3.name, p3.cash, p3.results)

if __name__ == "__main__":
    main()