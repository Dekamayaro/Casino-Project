#include "gtest/gtest.h"
#include "../headers/slots.h"
#include "../headers/blackjack.h"
#include "../headers/runner.h"
#include "../headers/bar.h"
#include "../headers/player.h"
#include <sstream>
#include <iostream>

using namespace std;

class BlackjackTest : public ::testing::Test {
    protected:
        istringstream input;
        Player testPlayer;
        Blackjack* blackjackGame;

    void SetUp() override {
        testPlayer.setWallet(1000.00);
        blackjackGame = new Blackjack(testPlayer);
    }

    void TearDown() override {
        delete blackjackGame;
        blackjackGame = nullptr;
    }

    void setPlayerScoreForTests(int score) {
        blackjackGame->playerScore = score;
    }

    void setDealerScoreForTests(int score) {
        blackjackGame->dealerScore = score;
    }

    void addGoodCardForTests(int card) {
        blackjackGame->goodCards.push_back(card);
    }

    bool calcOutcomeForTests() {
        return blackjackGame->calculateOutcome();
    }

    void arrangeCardsForTests(int card) {
        blackjackGame->arrangeCards(card);
    }

    const vector<int>& getGoodCardVectorForTest() {
        return blackjackGame->goodCards;
    }

};

TEST_F(BlackjackTest, TestQuit) {
    input.str("2\n");
    cin.rdbuf(input.rdbuf());

    bool res = blackjackGame->play(cout);

    EXPECT_FALSE(res);
}

TEST_F(BlackjackTest, TestPlayerWins) {
    setPlayerScoreForTests(20);
    setDealerScoreForTests(19);

    bool res = calcOutcomeForTests();

    EXPECT_TRUE(res);
}

TEST_F(BlackjackTest, TestDealerWins) {
    setPlayerScoreForTests(20);
    setDealerScoreForTests(21);

    bool res = calcOutcomeForTests();

    EXPECT_FALSE(res);
}

TEST_F(BlackjackTest, Test100percentWin) {
    testPlayer.setLuck(2);
    
    delete blackjackGame;
    Blackjack* blackjackGame = new Blackjack(testPlayer);
    
    setPlayerScoreForTests(20);
    arrangeCardsForTests(20);

    EXPECT_EQ(getGoodCardVectorForTest().size(), 1);
    EXPECT_EQ(getGoodCardVectorForTest().at(0), 11);    
}