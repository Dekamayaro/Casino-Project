#include "gtest/gtest.h"
#include "../headers/slots.h"
#include "../headers/roulette.h"
#include "../headers/blackjack.h"
#include "../headers/runner.h"
#include "../headers/bar.h"
#include "../headers/player.h"
#include <sstream>
#include <iostream>

using namespace std;

class RouletteTest : public ::testing::Test {
    protected:
        bool betsIsAllZero(Roulette testRoulette)
        {
            for(int i = 0; i < 50; i++)
            {
                if(0 != testRoulette.bets[i])
                    return false;
            }

            return true;
        }

        int getOne(Roulette testRoulette)
        {
            return testRoulette.one;
        }

        int getTen(Roulette testRoulette)
        {
            return testRoulette.ten;
        }
        
        int getFive(Roulette testRoulette)
        {
            return testRoulette.five;
        }
        
        int getTwentyFive(Roulette testRoulette)
        {
            return testRoulette.twentyFive;
        }
        
        int getOneHundread(Roulette testRoulette)
        {
            return testRoulette.oneHundread;
        }
        
        int getFiveHundread(Roulette testRoulette)
        {
            return testRoulette.fiveHundread;
        }
        
        int getOneTHousand(Roulette testRoulette)
        {
            return testRoulette.oneThousand;
        }

        void testPlaceBet(Roulette testRoulette, int bet, int index)
        {
            testRoulette.placeBet(bet, index);
        }

        int getBetAmount(Roulette testRoulette, int index)
        {
            return testRoulette.bets[index];
        }
};

TEST_F(RouletteTest, testingConstructor) 
{
    Player testPlayer;
    Roulette testRoulette(testPlayer);
    EXPECT_EQ(true, betsIsAllZero(testRoulette));
}

TEST_F(RouletteTest, testingCalculateChips_five) 
{
    Player testPlayer;
    testPlayer.setWallet(1641);
    Roulette testRoulette(testPlayer);
    
    EXPECT_EQ(1, getOne(testRoulette));
    EXPECT_EQ(1, getFive(testRoulette));
    EXPECT_EQ(1, getOneHundread(testRoulette));
    EXPECT_EQ(1, getOneTHousand(testRoulette));
    EXPECT_EQ(1, getTen(testRoulette));
    EXPECT_EQ(1, getFive(testRoulette));
    EXPECT_EQ(1, getTwentyFive(testRoulette));
}

TEST_F(RouletteTest, testPlaceBet_Good_Bet)
{
    Player testPlayer;
    testPlayer.setWallet(1641);
    Roulette testRoulette(testPlayer);

    testPlaceBet(testRoulette, 500 ,37);
    
    EXPECT_EQ(500, getBetAmount(testRoulette,37));
}

TEST_F(RouletteTest, testing_showChips_Colors)
{
    Player testPlayer;
    testPlayer.setWallet(3699);
    Roulette testRoulette(testPlayer);
    
    std::stringstream ss;
    testRoulette.showChips(cout);
    testRoulette.showChips(ss);
    EXPECT_EQ(ss.str(), "\033[40;37mone: 4\033[0m \033[40;31mfive: 0\033[0m \033[40;34mten: 2\033[0m \033[40;32mtwenty-five: 3\033[0m \033[40;36mone hundread: 1\033[0m \033[40;35mfive hundread: 1\033[0m \033[40;33mone thousand: 3\033[0m\n");
}
