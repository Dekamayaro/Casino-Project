#include "gtest/gtest.h"
#include "../headers/slots.h"
#include "../headers/player.h"
#include <sstream>
#include <iostream>

using namespace std;

class SlotsTest : public ::testing::Test {
    protected:
        istringstream input;
        Player testPlayer;
        Slots* slotsGame;

        void SetUp() override {
            testPlayer.setWallet(1000.00);
            // seed set to zero, debugging enabled
            slotsGame = new Slots(testPlayer, 0, true);
        }

        void TearDown() override {
            delete slotsGame;
            slotsGame = nullptr;
        }

        void setWheelForTests(const vector<Symbol>& wheelResults) {
            slotsGame->wheelResults = wheelResults;
        }

        bool calcOutcomeForTests() {
            return slotsGame->calculateOutcome();
        }

        void setBetForTests(double amount) {
            slotsGame->betAmount = amount;
        }
};

TEST_F(SlotsTest, TestQuit) {
    input.str("3\n");
    cin.rdbuf(input.rdbuf());

    bool res = slotsGame->play(cout);

    EXPECT_FALSE(res);
}

TEST_F(SlotsTest, mockJackpot) {
    vector<Symbol> jackpotVector = {
        Symbol("7", 7, WHITE),
        Symbol("7", 7, WHITE),
        Symbol("7", 7, WHITE)
    };

    setWheelForTests(jackpotVector);

    bool res = calcOutcomeForTests();

    EXPECT_TRUE(res);
}

TEST_F(SlotsTest, mockJackpotLoss) {
    vector<Symbol> jackpotVector = {
        Symbol("7", 7, WHITE),
        Symbol("Cherry", 7, WHITE),
        Symbol("Bomb", 7, WHITE)
    };

    setWheelForTests(jackpotVector);

    bool res = calcOutcomeForTests();

    EXPECT_FALSE(res);
}

TEST_F(SlotsTest, mockJackpotWalletTest) {
        vector<Symbol> jackpotVector = {
        Symbol("7", 7, WHITE),
        Symbol("7", 7, WHITE),
        Symbol("7", 7, WHITE)
    };
    setWheelForTests(jackpotVector);
    setBetForTests(100);

    bool res = calcOutcomeForTests();
    ASSERT_TRUE(res);

    double expectedAmount = (100 * 100) + 1000; // +1000 from SetUp()
    ASSERT_NEAR(expectedAmount, testPlayer.getWallet(), 0.001);
}

TEST_F(SlotsTest, TestLossWithSeed99AndWallet) {
    TearDown();
    slotsGame = new Slots(testPlayer, 99, true);
    
    input.str("1\n100\n2\n3\n");
    cin.rdbuf(input.rdbuf());

    bool res = slotsGame->play(cout);

    EXPECT_FALSE(res);
    EXPECT_NEAR(testPlayer.getWallet(), 900.0, 0.0001);
}

TEST_F(SlotsTest, TestLossWithSeed3476638650) {
    TearDown();
    slotsGame = new Slots(testPlayer, 3476638650, true);
    
    input.str("1\n500\n2\n3\n");
    cin.rdbuf(input.rdbuf());

    bool res = slotsGame->play(cout);

    EXPECT_FALSE(res);
}

