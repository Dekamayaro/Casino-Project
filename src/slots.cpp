#include "../headers/slots.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace this_thread;

/**
 * The Play() function provides a menu-driven interface for the Slots game, allowing the player 
 * to perform various actions, including placing bets, spinning the wheel, or quitting the game. 
 * The player's wallet is adjusted based on their bets and the outcome of each spin.
 * 
 * @param out The output stream used to display messages (e.g., std::cout).
 * @return A boolean indicating the status of the last game played (true = won, false = lost)
 */
bool Slots::play(ostream& out) {
    auto slotsMenu = [this](ostream& out) { outputMenu(out); };
    bool lastGameStatus = false;

    while(true) {
        int choice = getValidInput(minInputVal, maxInputVal, cin, out, slotsMenu);

        if(choice == 3) { // QUIT
            return lastGameStatus;
        } else if(choice == 1) { // PLACE BET
            auto betMenu = [this](ostream& out) { bettingMenu(out); };

            int betAmount = getValidInput(minBettingVal, maxBettingVal, cin, out, betMenu);

            if(betAmount != 0) {
                if(player.getWallet() >= betAmount) {
                    placeBet(betAmount);
                } else {
                    out << "Insufficient funds" << endl;
                }
            }
        } else { // SPIN WHEEL
            if(betAmount != 0 && player.getWallet() >= betAmount) {
                player.purchase(betAmount);
                lastGameStatus = (spinWheel(out));
            } else {
                out << "You have not entered an amount to Bet or do not have enough funds for this bet." << endl;
            }
        }
    }
    return false;
}

/**
 * The spinWheel() function handles the core mechanics of the slot machine game. It generates random 
 * symbols for three columns, evaluates the result, and adjusts the game's difficulty 
 * threshold based on the player's success or failure.
 * 
 * @param out The output stream used to display the slot machine wheel and related messages (e.g., std::cout).
 * @return A boolean indicating the outcome of the spin (true = won, false = loss)
 */
bool Slots::spinWheel(ostream& out) {
    vector<Symbol> firstColumn = { Symbol("Cherry", 1, RED), Symbol("Bomb", 5, BLACK), 
        Symbol("7", 7, WHITE), Symbol("Dollar", 10, BRIGHT_GREEN), Symbol("Bar", 3, YELLOW), Symbol("Bell", 4, BRIGHT_YELLOW), 
            Symbol("Grape", 2, MAGENTA), Symbol("Lemon", 2, BRIGHT_YELLOW), Symbol("Orange", 2, BRIGHT_RED), Symbol("Melon", 3, GREEN), 
                Symbol("Diamond", 20, BRIGHT_CYAN), Symbol("Clover", 6, GREEN) };

    vector<Symbol> secondColumn(firstColumn);
    shuffle(secondColumn.begin(), secondColumn.end(), rng);

    vector<Symbol> thirdColumn(firstColumn);
    shuffle(thirdColumn.begin(), thirdColumn.end(), rng);

    generateWheelAlg(firstColumn, secondColumn, thirdColumn);

    if(!DEBUG_BOOL) { outputWheel(out); }

    return (calculateOutcome() ? (threshold += difficulty, true) : (threshold -= difficulty, false));
}

/**
 * The generateWheelAlg() function calculates the outcomes of the three slot machine wheels (columns) by 
 * leveraging the player's luck and the current game threshold. It determines the symbols 
 * displayed in the slot machine results and adjusts for potential matches on the second 
 * and third wheels based on specific probability rules.
 * 
 * @param columnOne @param columnTwo @param columnThree are vectors containing the symbols 
 * for their respective column of the slot machine
 */
void Slots::generateWheelAlg(const vector<Symbol> &columnOne, const vector<Symbol> &columnTwo, const vector<Symbol> &columnThree) {
    uniform_real_distribution<double> chance(0.0, 1.0);
    int random = rand() % columnOne.size(); // SEED SHOULD ONLY BE DECLARED FOR TESTING

    wheelResults.clear();
    wheelResults.push_back(columnOne.at(random));

    if((SECOND_WHEEL_MULTIPLIER * player.getLuck() * 10) > threshold) {
        if(chance(rng) <= 0.20) { // 20% chance
            wheelResults.push_back(wheelResults.at(0));
        } else {
            wheelResults.push_back(columnTwo.at(random));
        }
    } else {
        wheelResults.push_back(columnTwo.at(random));
    }

    if((THIRD_WHEEL_MULTIPLIER * player.getLuck() * 10 > threshold)) {
        if(chance(rng) <= 0.10) { // 10% chance
            wheelResults.push_back(wheelResults.at(0));
        } else {
            wheelResults.push_back(columnThree.at(random));
        }
    } else {
        wheelResults.push_back(columnThree.at(random));
    }
}

/**
 * The outputWheel() function is responsible for displaying the results of a slot machine spin. It clears 
 * the console screen multiple times to create a visual effect that simulates the spinning of the
 * slot machine wheels, gradually revealing the outcome symbol by symbol. Each symbol is 
 * colorized based on its associated color attribute for better visual feedback.
 * 
 * @param out The output stream where the results will be displayed (typically `std::cout`).
 */
void Slots::outputWheel(ostream& out) {
    const int boxWidth = 32;
    const string topBorder = "+" + string(boxWidth, '-') + "+";
    const string bottomBorder = topBorder;

    vector<string> lightPatterns = {
        "🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡",
        "🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴",
        "🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴",
        "🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡"
    };

    // Simulate slot machine rolling
    simuWheelRolling(lightPatterns, topBorder, bottomBorder);

    // print the final wheel state to console
    outputFinalWheel(topBorder, bottomBorder);

    sleep_for(milliseconds(1000));
}

void Slots::simuWheelRolling(const vector<string>& lightPatterns, const string& topBorder, const string& bottomBorder) {
    for (unsigned frame = 0; frame < 8; ++frame) {
        for(unsigned lightFrame = 0; lightFrame < 4; ++lightFrame) {
            cout << "\33[2J\033[H"; // FLUSH

            cout << endl << topBorder << endl;
            cout << "| " << lightPatterns[lightFrame % lightPatterns.size()] << " |" << endl;

            cout << endl << "    ";

            if (frame >= 1) {
                ColorOutput::colorizeConsoleOutput(wheelResults.at(0).color, wheelResults.at(0).name);
            } else {
                cout << "***";
            }

            cout << "    ";
            if (frame >= 3) {
                ColorOutput::colorizeConsoleOutput(wheelResults.at(1).color, wheelResults.at(1).name);
            } else {
                cout << "***";
            }

            cout << "    ";
            if (frame >= 5) {
                ColorOutput::colorizeConsoleOutput(wheelResults.at(2).color, wheelResults.at(2).name);
            } else {
                cout << "***";
            }

            cout << "    " << endl << endl;

            cout << "| " << lightPatterns[(lightFrame + 1) % lightPatterns.size()] << " |" << endl;
            cout << bottomBorder << endl;

            sleep_for(milliseconds(150));
        }
    }
}

void Slots::outputFinalWheel(const string& topBorder, const string& bottomBorder) {
    cout << "\33[2J\033[H"; // FLUSH
    cout << topBorder << endl;
    cout << "| 🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡 |" << endl;
    cout << endl << "    ";
    ColorOutput::colorizeConsoleOutput(wheelResults.at(0).color, wheelResults.at(0).name);
    cout << "    ";
    ColorOutput::colorizeConsoleOutput(wheelResults.at(1).color, wheelResults.at(1).name);
    cout << "    ";
    ColorOutput::colorizeConsoleOutput(wheelResults.at(2).color, wheelResults.at(2).name);
    cout << "    " << endl;
    cout << endl << "| 🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡🟡🔴🔴🟡 |" << endl;
    cout << bottomBorder << endl;
}

/**
 * The calculateOutcome() function evaluates the results of the slot machine spin by comparing the symbols in the 
 * `wheelResults` vector. It checks for a jackpot (all symbols matching) or matches between adjacent symbols 
 * across the three columns. Based on the outcome, it calculates the player's payout and updates their balance.
 * 
 * @return `true` if the player wins (either a jackpot or a smaller win), `false` otherwise.
 */
bool Slots::calculateOutcome() {
    if(isJackpot()) {
        payoutWin(betAmount * 100);
        return true;
    } else {
        int finalPoints = wheelResults.at(0) == wheelResults.at(1) ? (betAmount * wheelResults.at(0).value) : 0;
        finalPoints += wheelResults.at(1) == wheelResults.at(2) ? (betAmount * wheelResults.at(1).value) : 0;
        finalPoints += wheelResults.at(0) == wheelResults.at(2) ? (betAmount * wheelResults.at(0).value) : 0;

        if(finalPoints == 0) {
            return false;
        } else {
            payoutWin(finalPoints);
            return true;
        }
    }
    return false;
}

/**
 * Pays the player the respective amount, with a congratulatory message and informs the player of their new balance
 * 
 * @param amount the amount to be paid
*/
void Slots::payoutWin(double amount) {
    player.setWallet(player.getWallet() + amount);
    string output = "Congratulations! You won ";
    ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, output);
    cout << "$" << amount << endl;

    string newBalOutput = "You have a new balance of ";
    ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, newBalOutput);
    cout << "$" << player.getWallet() << endl;
}

/**
 * Informs the user of the amount they have bet, in addition to calling the function to colorize the betting amount to console.
 * 
 * @param bet the amount the user has bet
*/
void Slots::placeBet(double bet) {
    betAmount = bet;
    string output = "You placed a Bet of ";
    ColorOutput::colorizeConsoleOutput(YELLOW, output);
    cout << betAmount << endl;
}

/**
 * The slots-options menu
*/
void Slots::outputMenu(ostream& out) {
    out << endl << "=== Slots ===" << endl;
    out << "1. Place Bet" << endl;
    out << "2. Spin the Wheel" << endl;
    out << "3. Quit" << endl;
}

/**
 * The betting-options menu
*/
void Slots::bettingMenu(ostream& out) {
    out << "Enter the amount you want to bet. Enter `0` if you want to exit." << endl;
}

/**
 * @return a bool whether the jackpot is hit
*/
bool Slots::isJackpot() {
    return (wheelResults.at(0) == wheelResults.at(1) && wheelResults.at(1) == wheelResults.at(2));
}