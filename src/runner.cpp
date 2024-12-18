#include "../headers/runner.h"
#include "../headers/player.h"
#include "../headers/bar.h"
#include "../headers/slots.h"
#include "../headers/blackjack.h"
#include "../headers/roulette.h"
#include "../headers/drink.h"
#include "../headers/drinks.h"
#include "../headers/ColorOutput.h"
#include "../headers/menumanager.h"
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace this_thread;

/**
 * Launches the main menu and guides the user through selecting a game difficulty and viewing their backstory.
 * The function handles user input to navigate the menus, selects the difficulty, and then starts the game.
 * 
 * @param in The input stream used to capture user input.
 * @param out The output stream used to display messages to the user.
 * 
 * @return void
 */

void Runner::launch(istream& in, ostream& out) {
    MenuManager::displayIntroMenu(out);
    int choice = 0;
    choice = getValidInput(in, out, 1, 2);
    out << "\33[2J\033[H";  //clears screen and moves cursor to top left
    
    if (choice == 1) {
        MenuManager::displayDifficultyMenu(out);
        choice = getValidInput(in, out, 1, 3);
    } 
    
    else if(choice == 2) {
        out << "Goodbye!" << endl;
        return;
    }

    MenuManager::displayBackstory(out, choice);
    setDifficulty(choice);
    startGame(in, out);
}

/**
 * Starts the game loop where the player interacts with the main menu, plays games, or visits the bar.
 * The function continues until the player runs out of money or chooses to quit.
 * It handles user input for game selection and bar visits, and exits the game when the wallet is empty or the player quits.
 * 
 * @param in The input stream used to capture user input.
 * @param out The output stream used to display messages to the user.
 * 
 * @return void
 */
void Runner::startGame(istream& in, ostream& out) {
    while(player.getWallet() != 0) {
        MenuManager::formatScreenTop(out);
        MenuManager::displayMainMenu(out, games);
        MenuManager::formatScreenBottom(out);
        
        int choice;
        int min = 1;
        int max = games.size() + 2; // + 2 for bar and quit
        choice = getValidInput(in, out, min, max);
        out << "\33[2J\033[H";  //clears screen and moves cursor to top left

        if(choice == max) { // QUIT
            out << "Good Bye! Hopefully we see you soon!" << endl;
            return;
        } else if(choice == max - 1) { // BAR
            bar.enterBar(out);
        } else {
            // Subtract 1 so it works with the array
            games.at(choice - 1)->play(out);
        }
    }
    if(player.getWallet() == 0) {
        out << "You have lost all your money! You have been kicked out of the Casino!" << endl;
    }
}

/**
 * Prompts the user for input until a valid integer between the specified minimum and maximum values is entered.
 * It ensures that the input is within the valid range and handles invalid inputs by displaying an error message.
 * 
 * @param in The input stream used to capture user input.
 * @param out The output stream used to display messages to the user.
 * @param min The minimum valid value for the input.
 * @param max The maximum valid value for the input.
 * 
 * @return The valid input value within the specified range.
 */
int Runner::getValidInput(istream& in, ostream& out, int min, int max) const {
    int input;

    while(true) {
        in >> input;
        
        while(in && (max >= input && input >= min)) {
            return input;
        }

        out << endl << "Invalid input. Please re-enter value between " 
            << min << " - " << max << endl; 

        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/**
 * Sets the player's difficulty level by adjusting their luck and initial wallet amount based on the selected choice.
 * 
 * @param choice The selected difficulty level
 */
void Runner::setDifficulty(int choice) {
    if (choice == 1) {
        player.setLuck(1.2);
        player.setWallet(5000);
    } 
    
    else if (choice == 2) {
        player.setLuck(1.0);
        player.setWallet(10000);
    } 
    
    else if (choice == 3) {
        player.setLuck(0.8);
        player.setWallet(15000);
    }
}