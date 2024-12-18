#include "gtest/gtest.h"
#include "../headers/player.h"
#include "../headers/runner.h"
#include "../headers/bar.h"
#include "../headers/drink.h"
#include "../headers/drinks.h"
#include "../headers/roulette.h"
#include "../headers/game.h"
#include "../headers/card.h"
// #include ""
// #include ""
// #include ""

TEST(PlayerTest, testing_default_constructor)
{
    Player testPlayer;
    EXPECT_EQ(testPlayer.getName(), "Player 1");
    EXPECT_NEAR(testPlayer.getLuck(), 1.0, 0.01);

}

TEST(PlayerTest, testing_setLuck)
{
    Player testPlayer;
    testPlayer.setLuck(3.75);
    EXPECT_NEAR(testPlayer.getLuck(), 3.75, 0.01);
}

TEST(PlayerTest, testing_setName)
{
    Player testPlayer;
    testPlayer.setName("George");
    EXPECT_EQ(testPlayer.getName(), "George");
}

TEST(PlayerTest, testing_changeWallet){
    Player testPlayer;
    testPlayer.setWallet(5);
    testPlayer.changeWallet(2);
    EXPECT_NEAR(testPlayer.getWallet(), 7, 0.01);
}

TEST(PlayerTest, testing_changeWallet_neg){
    Player testPlayer;
    testPlayer.setWallet(5);
    testPlayer.changeWallet(-2);
    EXPECT_NEAR(testPlayer.getWallet(), 3, 0.01);
}

/**
 * Player Buff/Debuff Tests
 */ 

TEST(PlayerTest, testing_applyBuff)
{
    Player testPlayer;
    testPlayer.applyBuff(0.5);
    EXPECT_EQ(testPlayer.getLuck(), 1.5);
}

TEST(PlayerTest, testing_applyBuff_neg)
{
    Player testPlayer;
    testPlayer.applyBuff(-0.5);
    EXPECT_EQ(testPlayer.getLuck(), 1.5);
}

TEST(PlayerTest, testing_applyBuff_excessive)
{
    Player testPlayer;
    EXPECT_THROW(testPlayer.applyBuff(3);, std::runtime_error);
}

TEST(PlayerTest, testing_applyDebuff)
{
    Player testPlayer;
    testPlayer.applyDebuff(0.5);
    EXPECT_EQ(testPlayer.getLuck(), 0.5);
}

TEST(PlayerTest, testing_applyDebuff_neg)
{
    Player testPlayer;
    testPlayer.applyDebuff(-0.5);
    EXPECT_EQ(testPlayer.getLuck(), 0.5);
}

TEST(PlayerTest, testing_applyDebuff_excessive)
{
    Player testPlayer;
    EXPECT_THROW(testPlayer.applyDebuff(3);, std::runtime_error);
}

/*Card tests*/

TEST(CardTest, testing_default_constructor)
{
    Card testCard;
    EXPECT_EQ(testCard.getSuit(), 'c');
    EXPECT_EQ(testCard.getRank(), 2);
}

TEST(CardTest, testing_param_constructor)
{
    Card testCard('s', 13);
    EXPECT_EQ(testCard.getSuit(), 's');
    EXPECT_EQ(testCard.getRank(), 13);
}

TEST(CardTest, testing_output_stream)
{
    Card testCard('s', 13);
    std::stringstream ss;
    ss << testCard;
    EXPECT_EQ(ss.str(), "[K \033[30m\u2660\033[0m]");
}
