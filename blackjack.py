import random
from enum import Enum



class Actions(Enum):
    HIT = 0,
    STAND = 1,

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
        return val
    def reset(self):
        self.deck.extend(self.dealt)
        self.dealt = []

    
class Player:
    def __init__(self, name):
        self.hand = Hand()
        self.name = name
        self.losses = 0
        self.wins = 0
        self.active = False
#        self.hand_sum = 0
    def deal(self, card):
        self.hand.add_card(card)
    def ask(self):
        return self.hand.ask()
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

class Dealer(Player):
    pass

class Game():
    def __init__(self, shoe):
        self.dealer = None
        self.players = []
        self.shoe = shoe
    def add_player(self, player):
        self.players.append(player)
    def add_dealer(self, dealer):
        self.players.insert(0, dealer)
        self.dealer = dealer
    def round(self):
        # Initial deal
        for _ in range(0, 2):
            for player in self.players:
                player.deal(self.shoe.draw())
        # Players
        for player in self.players[1:]:
            while(player.ask() != Actions.STAND):
                player.deal(self.shoe.draw())
        # Dealer
        while self.dealer.ask() != Actions.STAND:
            self.dealer.deal(self.shoe.draw())
        
        dealer_score = self.dealer.final()
        for player in self.players[1:]:
            player_score = player.final()
            if player_score == -1:
                #print(player.name, "loses (busts)")
                player.losses += 1
            elif dealer_score == -1:
                #print(player.name, "wins (dealer busts)")
                player.wins += 1
            else:
                if player_score > dealer_score:
                    #print(player.name, "wins (score)")
                    player.wins += 1
                else:
                    #print(player.name, "loses (score)")
                    player.losses += 1
        #print(self.players)
        for player in self.players:
            player.reset()
        self.shoe.reset()


def main():
    shoe = Deck(2)
    shoe.shuffle()

    game = Game(shoe)

    d = Dealer("Chud")
    p1 = Player("Anderdingle")
    p2 = Player("Geoff")
    game.add_player(p1)
    game.add_player(p2)
    game.add_dealer(d)

    for _ in range(0, 1000000):
        game.round()
    print(p1.name, "Wins: ", p1.wins, " Losses: ", p1.losses)
    print(p2.name, "Wins: ", p2.wins, " Losses: ", p2.losses)

#    print(d.hand, p1.hand, p2.hand)

if __name__ == "__main__":
    main()