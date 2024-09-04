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
            return 11
        else:
            return 10
    

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
    
class Player:
    def __init__(self, name):
        self.hand = []
        self.name = name
        self.active = False
        self.hand_sum = 0
    def deal(self, card):
        self.hand.append(card)
        self.hand_sum += card.get_value()
    def ask(self):
        if self.hand_sum > 17:
            return Actions.STAND
        else:
            return Actions.HIT

    def __repr__(self):
        return self.name + "-" + str(self.hand_sum) +" " + str(self.hand)


class Dealer(Player):
    pass

class Game():
    def __init__(self, shoe):
        self.players = []
        self.shoe = shoe
    def add_player(self, player):
        self.players.append(player)
    def add_dealer(self, dealer):
        self.players.insert(0, dealer)
    def loop(self):
        done = False
        while(not done):
            done = True
            for player in self.players:
                result = player.ask()
                match result:
                    case Actions.STAND:
                        pass
                    case Actions.HIT:
                        done = done & False
                        player.deal(self.shoe.draw())
            print(self.players)

def main():
    shoe = Deck(2)
    shoe.shuffle()

    game = Game(shoe)

    d = Dealer("Chud")
    p1 = Player("Carlos")
    p2 = Player("Enrique")

    game.add_player(p1)
    game.add_player(p2)
    game.add_dealer(d)

    print(game.players)

    game.loop()
    

#    print(d.hand, p1.hand, p2.hand)

if __name__ == "__main__":
    main()