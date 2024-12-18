#pragma once

#include "../headers/drink.h"
#include "../headers/player.h"
#include <iostream>
#include <vector>
#include <ostream>

using namespace std;

class Bar {
    friend class BarTestClass;

    private:
        Player& player;
        vector<Drink> drinks;
    public:
        Bar(Player& _player) : player(_player) {
            setUpDrinks();
        };
        void enterBar(ostream&);
    private:
        void setUpDrinks();
        void purchase(ostream& out, int);
        const Drink& serveDrink(int) const;
        void display(ostream& out);
};
