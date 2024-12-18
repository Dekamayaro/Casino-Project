#pragma once

#include <string>

using std::string;

class Player
{
    private:
        double luck;
        string name;
        double wallet;

    public:
        Player(double luck = 1.0, string name = "Player 1") : luck(luck), name(name), wallet(0) {}; // wallet and bank set to zero for safety
    
        const double getLuck() const;
        const string getName() const;
        const double getWallet() const;

        void setLuck(double newLuck);
        void setName(string newName);
        void setWallet(double newWallet);
        void changeWallet(double amount);
        void purchase(double amount);
        void applyBuff(double buff);
        void applyDebuff(double debuff);
};
