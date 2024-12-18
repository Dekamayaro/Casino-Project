#include "gtest/gtest.h"
#include "../headers/slots.h"
#include "../headers/blackjack.h"
#include "../headers/runner.h"
#include "../headers/bar.h"
#include "../headers/player.h"
#include <sstream>
#include <iostream>

class TestClass : public ::testing::Test {
    protected:
        Runner* testRunner;

        void SetUp() override {
            testRunner = new Runner();
        }

        void TearDown() override {
            delete testRunner;
            testRunner = nullptr;
        }

        const Player& getUserForTests() const {
            return testRunner->player;
        }

        void setDifficultyForTests(int diff) const {
            testRunner->setDifficulty(diff);
        }

        int validateChoiceForTests(std::istream& in, std::ostream& out, int min, int max) {
            int returnVal = testRunner->getValidInput(in, out, min, max);
            return returnVal;
        }
};

TEST_F(TestClass, testing_setDifficulty_Easy) {
    setDifficultyForTests(1);
    EXPECT_NEAR(getUserForTests().getLuck(), 1.2, 0.01);
    EXPECT_NEAR(getUserForTests().getWallet(), 5000, 0.01);
}

TEST_F(TestClass, testing_setDifficulty_Normal) {
    setDifficultyForTests(2);
    EXPECT_NEAR(getUserForTests().getLuck(), 1.0, 0.01);
    EXPECT_NEAR(getUserForTests().getWallet(), 10000, 0.01);
}

TEST_F(TestClass, testing_setDifficulty_Hard) {
    setDifficultyForTests(3);
    EXPECT_NEAR(getUserForTests().getLuck(), 0.8, 0.01);
    EXPECT_NEAR(getUserForTests().getWallet(), 15000, 0.01);
}

TEST_F(TestClass, testing_validateChoice) {
    std::stringstream input("0\n6\n3\n");
    std::stringstream output;
    int res = validateChoiceForTests(input, output, 1, 5); // choice values = 0, 0, 6, 3
    EXPECT_EQ(res, 3);
    EXPECT_EQ(output.str(), "Invalid choice. Please enter a value between 1 & 5.\nInvalid choice. Please enter a value between 1 & 5.\nInvalid choice. Please enter a value between 1 & 5.\n");
}