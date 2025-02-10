#include <gtest/gtest.h>
#include <string>
#include "Card.h"
#include "Suit.h"

TEST(CardTest, isAce)
{
    Card card(1, Suit::suits::SPADE);
    EXPECT_TRUE(card.is_ace());
    Card card2(2, Suit::suits::SPADE);
    EXPECT_FALSE(card2.is_ace());
}
TEST(CardTest, getValue)
{
    Card card(1, Suit::suits::SPADE);
    EXPECT_EQ(card.get_value(), 1);
    Card card2(5, Suit::suits::SPADE);
    EXPECT_EQ(card2.get_value(), 5);
    Card card3(12, Suit::suits::SPADE);
    EXPECT_EQ(card3.get_value(), 10);
}
TEST(CardTest, pretty)
{
    Card card(1, Suit::suits::SPADE);
    std::string expected = "A♠";
    EXPECT_EQ(card.pretty(), expected);
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}