#pragma once
#include "game.h"
#include "player.h"
#include "visuals.h"

class Roulette : public Game
{
    friend class RouletteTest;
    private:
        //variables
            //player
        Player* player;
            //array of bets
        int bets[50];
            //chips:
        int one, five, ten, twentyFive, oneHundread, fiveHundread, oneThousand;
            //probabilities, rounded to 3 decimal places, these don't change:
        const double single = 0.026, row_dozen = 0.316, block = 0.474;

        //inherited functions
        void placeBet(int bet, int betIndex);
        int payoutWin(int winningNum);
        bool calculateOutcome() override;
        //roulette specific functions
        void calculateChips();
        void clearScreen();
        void clearBets();
        void clearCin(istream& in);
        void bettingOnSingles(ostream& out);
        void bettingOnRowDozen(ostream& out);
        void bettingOnRedBlack(ostream& out);
        void bettingOnOddEven(ostream& out);
        void bettingOnHalfs(ostream& out);
        double calculateTotalProbability();
        int spinWheel(bool playerWon);

    public:
        //public functions
        Roulette(Player& player);
        bool play(ostream& out) override;
        void outputMenu(ostream& out) override;
        void showChips(ostream& out);
        
};
