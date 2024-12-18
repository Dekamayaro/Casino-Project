#pragma once

#include "../headers/player.h"

#include <string>
#include <functional>
#include <ostream>

using namespace std;

class Drink {
    protected:
        string name;
        int price;
        function<void(Player&)> effect;
    public:
        Drink(const string& name_, const int& price_, function<void(Player&)> effect_)
            : name(name_), price(price_), effect(effect_) {}

        virtual void affectPlayer(Player& player) const {
            effect(player);
        }

        const string& getName() const {
            return name;
        }

        const int& getPrice() const {
            return price;
        }
};