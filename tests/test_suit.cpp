#include <gtest/gtest.h>
#include "Suit.h"

TEST(SuitTest, pretty)
{
    Suit spade(Suit::suits::SPADE);
    EXPECT_EQ(spade.pretty(), "♠");
    Suit heart(Suit::suits::HEART);
    EXPECT_EQ(heart.pretty(), "♥");
    Suit club(Suit::suits::CLUB);
    EXPECT_EQ(club.pretty(), "♣");
    Suit diamond(Suit::suits::DIAMOND);
    EXPECT_EQ(diamond.pretty(), "♦");
}