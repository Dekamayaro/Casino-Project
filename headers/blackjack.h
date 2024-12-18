#pragma once
#include "../headers/game.h"
#include "../headers/player.h"
#include "../headers/card.h"
#include "../headers/ColorOutput.h"
#include <vector>
#include <ctime>

class Blackjack : public Game {
    friend class BlackjackTest;

    public:
        Blackjack(Player& player);
        ~Blackjack();
        Blackjack& operator=(const Blackjack&) = delete;
        bool play(ostream& out) override;

    private:
        void outputMenu(ostream& out) override;
        void placeBet(double bet);
        void payoutWin(double amnt);
        bool calculateOutcome() override;

        Player* player;
        vector<int> goodCards;
        vector<int> badCards;
        vector<Card*> playerHand;
        vector<Card*> dealerHand;
        int playerHasAce = 0; //allows for multiple aces
        int dealerHasAce = 0;
        int playerScore = 0;
        int dealerScore = 0;
        void arrangeCards(int score);
        bool calcCardBenefit(int score, int card);
        void drawCard(bool playerTurn);

        void bettingMenu(ostream& out);
        void ingameMenu(ostream& out);
        void drawCardWithDelay(bool isPlayerTurn, ostream& out);
        void clearScreen(ostream& out);
        void displayTable(ostream& out);
        void newGameMenu(ostream& out);

        /*deletes everything in the vectors either for before
        the dealer's turn or after the round has ended*/
        void endOfRound();
};
