#include "../headers/blackjack.h"
#include "../headers/card.h"
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

/**
 * Constructor
*/

Blackjack::Blackjack(Player& player) {
    name = "Blackjack";
    this->player = &player;
    srand(time(0));
}

/*
* Destructor for the Blackjack class
*/
Blackjack::~Blackjack(){
    for (unsigned int i = 0; i < playerHand.size(); i++) {
        delete playerHand.at(i);
    }
    for (unsigned int i = 0; i < dealerHand.size(); i++) {
        delete dealerHand.at(i);
    }
    dealerHand.clear();
    playerHand.clear();
}

/*
* The play() function provides a menu-driven interface for the Blackjack game, allowing the player
* to perform various actions, including placing bets, drawing cards, and quitting the game.
* The player's wallet is adjusted based on their bets and the outcome of each round.
* 
* @param out The output stream used to display messages (e.g., std::cout).
* @return A boolean indicating the status of the last game played (true = won, false = lost)
*/
bool Blackjack::play(ostream& out) {
    int choice;
    bool playerTurn = true;
    bool playerBusted = false;
    bool playerWins = false;
    bool betPlaced = false;
    double betAmount = 0;

    // Display in-game menu and get player's choice
    choice = getValidInput(1, 2, cin, out, [this](ostream& out) { outputMenu(out); });
    clearScreen(out);

    while (true) {
        // Reset variables for each round
        playerTurn = true;
        playerBusted = false;
        playerWins = false;
        betPlaced = false;
        betAmount = 0;

        if(player->getWallet() == 0){
            string output = "Insufficient Funds\nLooks like you're out of chips! Time to hit the ATM or call it a day. Better luck next time!\n";
            ColorOutput::colorizeConsoleOutput(RED, output);
            return false;
        }

        if (choice == 1) {
            betAmount = getValidInput(0, player->getWallet(), cin, out, [this](ostream& out) { bettingMenu(out); });
            clearScreen(out);
            if (betAmount == 0) {
                return false;
            }
            placeBet(betAmount);
            betPlaced = true;
        } else {
            return false; // Player chose to quit
        }

        if (betPlaced) {
            // Initial draw: player and dealer both get two cards each
            arrangeCards(playerScore);
            drawCardWithDelay(true, out);
            drawCardWithDelay(true, out);
            drawCardWithDelay(false, out);
            drawCardWithDelay(false, out);

            // Player's turn
            while (playerTurn) {
                displayTable(out);

                if (playerScore == 21) {
                    playerTurn = false;
                } else {
                    choice = getValidInput(1, 2, cin, out, [this](ostream& out) { ingameMenu(out); });

                    if (choice == 1) {
                        drawCardWithDelay(true, out);
                        if (playerScore > 21) {
                            playerBusted = true;
                            playerTurn = false;
                        }
                    } else {
                        playerTurn = false;
                    }
                }
            }

            // Dealer's turn
            if (!playerBusted) {
                while (dealerScore < 16) {
                    drawCardWithDelay(false, out);
                    displayTable(out);
                    if (dealerScore > 21) {
                        break;
                    }
                }
            }

            // Display final hands and scores
            displayTable(out);

            // Determine the outcome
            playerWins = calculateOutcome();

            // Payout the winner
            if (playerWins) {
                payoutWin(betAmount * 2);
            } else {
                ostringstream oss ;
                oss << fixed << setprecision(0) << betAmount;
                string output = "You lost $" + oss.str() + "\n";
                ColorOutput::colorizeConsoleOutput(RED, output);
            }

            // End the round
            endOfRound();
            playerScore = 0;
            dealerScore = 0;

            // Display in-game menu again for the next round
            choice = getValidInput(1, 2, cin, out, [this](ostream& out) { newGameMenu(out); });
            clearScreen(out);
            if (choice == 2) {
                return playerWins;
            }
        }
    }
}

void Blackjack::drawCardWithDelay(bool isPlayerTurn, ostream& out) {
    drawCard(isPlayerTurn);
    this_thread::sleep_for(chrono::milliseconds(1500)); // Increased delay
    displayTable(out);
}

bool Blackjack::calcCardBenefit(int score, int card){
    //being 5 to 9 away from 21 is bad bc you're still far away from 21,
    //but also can go over 21 if you draw again
    if((card + score > 21) || ((21 - (card + score) > 4) && (21 - (card + score) < 10))){
        //Ace
        if(card == 11){
            return 0 || calcCardBenefit(score, 1);
        }else{
            return 0;
        }
    }

    return 1;
}

void Blackjack::arrangeCards(int score){
    for(int i = 2; i < 12; i++){
        if(calcCardBenefit(score, i)){
            goodCards.push_back(i);
            /*since in blackjack there are 4 cards with the
            value 10, if i is 10, we need to put 4 cards into
            goodCards, otherwise, just put one*/
            if(i == 10){
                for(int j = 0; j < 3; j++){
                    goodCards.push_back(10);
                }
            }
        } else{
            badCards.push_back(i);
            /*since in blackjack there are 4 cards with the
            value 10, if i is 10, we need to put 4 cards into
            badCards, otherwise, just put one*/
            if(i == 10){
                for(int j = 0; j < 3; j++){
                    badCards.push_back(10);
                }
            }
        }
    }
}

/*
* Draws a card for the player or dealer, based on the luck of the player
* @param isPlayerTurn a boolean that is true if it is the player's turn, false if it is the dealer's turn
*/
void Blackjack::drawCard(bool isPlayerTurn){
    int cardChosenValue;
    int cardChosen;
    double luck;
    //reverses the luck for the dealer
    if(isPlayerTurn){
        luck = player->getLuck();
    } else{
        luck = 2 - player->getLuck();
    }

    if(std::rand() % 200 < luck * 100 || badCards.size() == 0){
        //picks a random card from the good cards
        cardChosen = goodCards.at(std::rand() % goodCards.size());

    } else{
        //picks a random card from the bad cards
        cardChosen = badCards.at(std::rand() % badCards.size());
    }

    //allows for ace, jack, queen, and king all be properly added into the hand
    cardChosenValue = cardChosen;
    if(cardChosen == 11){
        cardChosen = 1;
    } else if(cardChosen == 10){
        cardChosen = std::rand() % 4 + 10;
    }
    //Ace
    if(cardChosen == 1){
        if(isPlayerTurn){
            playerHasAce++;
        } else{
            dealerHasAce++;
        }
    }

    //randomly generates a suit for the card and adds it to the hand
    int suit = std::rand() % 4;
    if(isPlayerTurn){
        if(suit == 0){
            playerHand.push_back(new Card('c',cardChosen));
        } else if(suit == 1){
            playerHand.push_back(new Card('d',cardChosen));
        } else if(suit == 2){
            playerHand.push_back(new Card('h',cardChosen));
        } else{
            playerHand.push_back(new Card('s',cardChosen));
        }
    }
    else{
        if(suit == 0){
            dealerHand.push_back(new Card('c',cardChosen));
        } else if(suit == 1){
            dealerHand.push_back(new Card('d',cardChosen));
        } else if(suit == 2){
            dealerHand.push_back(new Card('h',cardChosen));
        } else{
            dealerHand.push_back(new Card('s',cardChosen));
        }
    }

    //updates the score
    if(isPlayerTurn){
        playerScore += cardChosenValue;
        if (playerScore > 21 && playerHasAce > 0){
            playerScore -= 10;
            playerHasAce--;
        }
    } else{
        dealerScore += cardChosenValue;
        if (dealerScore > 21 && dealerHasAce > 0){
            dealerScore -= 10;
            dealerHasAce--;
        }
    }
}

bool Blackjack::calculateOutcome() {
    if(playerScore > 21){
        return false;
    }
    else if(dealerScore > 21){
        return true;
    }
    else if(playerScore > dealerScore){
        return true;
    }
    else if(playerScore == dealerScore){
        return true;
    }
    else{
        return false;
    }
}

/*
* Deletes all the cards in the vectors and resets the scores
*/
void Blackjack::endOfRound(){
    playerHasAce = 0;
    dealerHasAce = 0;
    playerScore = 0;
    dealerScore = 0;
    goodCards.clear();
    badCards.clear();
    for (unsigned int i = 0; i < playerHand.size(); i++) {
        delete playerHand.at(i);
    }
    for (unsigned int i = 0; i < dealerHand.size(); i++) {
        delete dealerHand.at(i);
    }
    dealerHand.clear();
    playerHand.clear();
}

// Output and formating functions
void Blackjack::outputMenu(ostream& out) {
    out << endl << "=== Blackjack ===" << endl;
    out << "1. Place Bet" << endl;
    out << "2. Quit" << endl;
}

void Blackjack::bettingMenu(ostream& out) {
    out << "Enter the amount you want to bet. Enter `0` if you want to leave" << endl;
}

void Blackjack::placeBet(double bet) {
    player->purchase(bet);
    ostringstream oss;
    oss << fixed << setprecision(0) << bet;
    string output = "You placed a Bet of $" + oss.str() + "\n";
    ColorOutput::colorizeConsoleOutput(YELLOW, output);
}

void Blackjack::payoutWin(double amnt) {
    player->setWallet(player->getWallet() + amnt);
    ostringstream oss;
    oss << fixed << setprecision(0) << amnt;
    string output = "Congratulations! You won $" + oss.str() + "\n";
    ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, output);

    oss.str(""); // Clear the stringstream
    oss << fixed << setprecision(0) << player->getWallet();
    string newBalOutput = "You have a new balance of $" + oss.str() + "\n";
    ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, newBalOutput);
}

void Blackjack::ingameMenu(ostream& out) {
    out << "1. Hit" << endl;
    out << "2. Stand" << endl;
}

void Blackjack::clearScreen(ostream& out) {
    out << "\33[2J\033[H";  //clears screen and moves cursor to top left
}

/*
* Displays the current state of the game, including the player's and dealer's hands, scores, and the table layout.
* @param out The output stream used to display the game state (e.g., std::cout).
*/
void Blackjack::displayTable(ostream& out){
    clearScreen(out);
    out << "+-----------------+-----------------+" << endl;
    out << "|     \033[34mPlayer\033[0m      |     \033[31mDealer\033[0m      |" << endl;
    out << "+-----------------+-----------------+" << endl;

    size_t maxSize = max(playerHand.size(), dealerHand.size());
    for (size_t i = 0; i < maxSize; ++i) {
        out << "| ";
        
        if (i < playerHand.size()){
            if (playerHand[i]->getRank() == 10){
                out << setw(10) << *playerHand[i];
            }
            else {
                out << setw(11) << *playerHand[i];
            }
        } else {
            out << setw(15) << " ";
        }
        out << " | ";
        if (i < dealerHand.size()) {
            if (dealerHand[i]->getRank() == 10){
                out << setw(10) << *dealerHand[i];
            }
            else {
                out << setw(11) << *dealerHand[i];
            }
        } else {
            out << setw(15) << " ";
        }
        out << " |" << endl;
    }

    out << "+-----------------+-----------------+" << endl;
    out << "| Player Score: " << setw(2) << playerScore;
   
    out << "| Dealer Score: " << setw(2) << dealerScore; 
    
    out << "|" << endl;
    out << "+-----------------+-----------------+" << endl;
}

void Blackjack::newGameMenu(ostream& out) {
    out << "Do you want to play another round? (1: Yes, 2: No)" << endl;
}