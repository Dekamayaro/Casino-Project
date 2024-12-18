#include "gtest/gtest.h"
#include "../headers/slots.h"
#include "../headers/blackjack.h"
#include "../headers/runner.h"
#include "../headers/bar.h"
#include "../headers/player.h"
#include <sstream>
#include <iostream>

class BarTestClass : public ::testing::Test {
    protected:
        Player p;
        Bar* bar;

        void SetUp() override {
            p.setWallet(10000);
            bar = new Bar(p);
        }

        void TearDown() override {
            delete bar;
            bar = nullptr;
        }

        bool isEmpty() {
            return bar->drinks.empty();
        }

        const Drink& serveDrinkForTests(int index) {
            return bar->serveDrink(index);
        }

        void purchaseForTests(int index) {
            bar->purchase(cout, index);
        }
};

TEST_F(BarTestClass, test_DrinkVector_filled) {
    TearDown();
    bar = new Bar(p);
    EXPECT_FALSE(isEmpty());
}

TEST_F(BarTestClass, test_serveDrink_Margarita) {
    Drink d = serveDrinkForTests(1);
    EXPECT_EQ(d.getName(), "Margarita"); 
    EXPECT_TRUE(d.getPrice() == 8);
}

TEST_F(BarTestClass, test_serveDrink_OldFashioned) {
    Drink d = serveDrinkForTests(2);
    EXPECT_EQ(d.getName(), "Old Fashioned"); 
    EXPECT_TRUE(d.getPrice() == 10);
}

TEST_F(BarTestClass, test_serveDrink_Martini) {
    Drink d = serveDrinkForTests(3);
    EXPECT_EQ(d.getName(), "Martini"); 
    EXPECT_TRUE(d.getPrice() == 11);
}

TEST_F(BarTestClass, test_serveDrink_MoscowMule) {
    Drink d = serveDrinkForTests(4);
    EXPECT_EQ(d.getName(), "Moscow Mule"); 
    EXPECT_TRUE(d.getPrice() == 10);
}

TEST_F(BarTestClass, test_serveDrink_GinTonic) {
    Drink d = serveDrinkForTests(5);
    EXPECT_EQ(d.getName(), "Gin and Tonic"); 
    EXPECT_TRUE(d.getPrice() == 15);
}

TEST_F(BarTestClass, test_serveDrink_Spritz) {
    Drink d = serveDrinkForTests(6);
    EXPECT_EQ(d.getName(), "Spritz"); 
    EXPECT_TRUE(d.getPrice() == 8);
}

TEST_F(BarTestClass, test_serveDrink_PinaColada) {
    Drink d = serveDrinkForTests(7);
    EXPECT_EQ(d.getName(), "Pina Colada"); 
    EXPECT_TRUE(d.getPrice() == 20);
}

TEST_F(BarTestClass, test_serveDrink_Mimosa) {
    Drink d = serveDrinkForTests(8);
    EXPECT_EQ(d.getName(), "Mimosa"); 
    EXPECT_TRUE(d.getPrice() == 50);
}

TEST_F(BarTestClass, test_drink_purchase_Margarita) {
    double amnt = p.getWallet();
    purchaseForTests(1);
    double expected = amnt - 8;

    EXPECT_NEAR(p.getWallet(), expected, 0.001); 
}

TEST_F(BarTestClass, test_drink_purchase_Mimosa) {
    double amnt = p.getWallet();
    purchaseForTests(8);
    double expected = amnt - 50;

    EXPECT_NEAR(p.getWallet(), expected, 0.001); 
}

TEST_F(BarTestClass, test_Mimosa_purchase_affects_luck) {
    double amnt = p.getLuck();
    purchaseForTests(8);

    EXPECT_TRUE(amnt != p.getLuck());
}

TEST_F(BarTestClass, test_PinaColada_purchase_affects_luck) {
    double amnt = p.getLuck();
    purchaseForTests(7);

    EXPECT_TRUE(amnt != p.getLuck());
}

TEST_F(BarTestClass, test_Margarita_purchase_affects_luck) {
    double amnt = p.getLuck();
    purchaseForTests(1);

    EXPECT_TRUE(amnt != p.getLuck());
}