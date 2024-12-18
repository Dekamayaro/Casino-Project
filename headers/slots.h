#pragma once

#include "../headers/game.h"
#include "../headers/player.h"
#include "../headers/ColorOutput.h"
#include <vector>
#include <random>

struct Symbol {
    string name;
    int value;
    int color;

    Symbol(string _name, int _value, int _color) : name(_name), value(_value), color(_color) {}

    bool operator==(const Symbol& param) const {
        return (this->name == param.name);
    }
};

class Slots : public Game {
    friend class SlotsTest;

    private:
        bool DEBUG_BOOL;
        const double SECOND_WHEEL_MULTIPLIER = 0.02;
        const double THIRD_WHEEL_MULTIPLIER = 0.01;
        double threshold = 0.20;
        double difficulty = 0.005;

        Player& player; //non-const reference
        vector<Symbol> wheelResults;
        mt19937 rng;

        int minInputVal = 1;
        int maxInputVal = 3;
        int minBettingVal = 1;
        int maxBettingVal = 1000;
        int betAmount;
    public:
        Slots(Player& _player, unsigned int seed = 0, bool _DEBUG = false) : DEBUG_BOOL(_DEBUG), player(_player) {
            name = "Slots";
            betAmount = 0;
            if(seed == 0) {
                random_device rd;
                rng.seed(rd());

                if(DEBUG_BOOL) { cout << "Seed: " << rd() << endl; }

            } else {
                rng.seed(seed);

                if(DEBUG_BOOL) { cout << "Seed: " << seed << endl; }
            }
        }

        bool play(ostream& out) override;
    private:
        void outputMenu(ostream& out) override;
        void placeBet(double bet);
        void payoutWin(double amnt);
        bool calculateOutcome() override;

        void generateWheelAlg(const std::vector<Symbol> &columnOne, const std::vector<Symbol> &columnTwo, const std::vector<Symbol> &columnThree);
        bool spinWheel(ostream& out);
        void outputWheel(ostream& out);
        void simuWheelRolling(const vector<string>& lightPatterns, const string& topBorder, const string& bottomBorder);
        void outputFinalWheel(const string& topBorder, const string& bottomBorder);
        void bettingMenu(ostream& out);
        bool isJackpot();

    public: // FOR TESTING
        const vector<Symbol>& getWheel() const {
            return wheelResults;
        }
};
