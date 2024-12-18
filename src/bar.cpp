#include "../headers/bar.h"
#include "../headers/player.h"
#include "../headers/drink.h"
#include "../headers/drinks.h"

#include <iostream>
#include <ostream>
#include <limits>

using namespace std;

/**
 * Validates input from @param minRange to @param maxRange
*/
int getValidInput(int minRange, int maxRange, std::istream& in) {
    int input;
    while(true) {
        cout << "Please enter the integer value for the drink you would like? Optionally enter '0' to exit" << endl;
        in >> input;

        while(in && (maxRange >= input && input >= minRange)) {
            return input;
        }

        cout << "Invalid input. "; // NO std::endl; because we want it to all be on the same line

        in.clear();
        in.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

/**
 * Handles the player's interaction with the Bar, allowing them to choose and purchase drinks.
 * If the player has insufficient funds, they are given two attempts before being kicked out.
 * 
 * @param out The output stream to display messages to the player.
 * 
 * @return void
 */
void Bar::enterBar(ostream& out) {
    int numAttemptsWithoutPlayerFunds = 0;
    //!auto input = 0;

    out << "Welcome to the Bar, what kind of drink can I get you?" << endl;
    
    while(true) {
        display(out);
        int choice = getValidInput(0, drinks.size(), cin);
    
        if(choice == 0) { return; }

        if(player.getWallet() >= serveDrink(choice).getPrice()) {
            purchase(out, choice);
        } else {
            out << "You do not have enough money!" << endl;
            if((++numAttemptsWithoutPlayerFunds) >= 2) {
                out << "You have been kicked out of the Bar! Show up with more money next time!" << endl;
                return;
            }
        }
        cout << endl;
    }
}

void Bar::purchase(ostream& out, int drinkIndex) {
    Drink drink = serveDrink(drinkIndex);
    out << "You purchased " << drink.getName() << " for $" << drink.getPrice() << endl;
    
    player.purchase(drink.getPrice());
    drink.affectPlayer(player);
}

const Drink& Bar::serveDrink(int drinkIndex) const {
    return (drinks.at(drinkIndex - 1));
}

void Bar::display(ostream& out) {
    for(unsigned i = 0; i < drinks.size(); i++) {
        out << i + 1 << ": " << drinks.at(i).getName() << " $" << drinks.at(i).getPrice() << endl;
    }
}

void Bar::setUpDrinks() {
    drinks.push_back(Margarita());
    drinks.push_back(Oldfashioned());
    drinks.push_back(Martini());
    drinks.push_back(MoscowMule());
    drinks.push_back(GinAndTonic());
    drinks.push_back(Spritz());
    drinks.push_back(PinaColada());
    drinks.push_back(Mimosa());
}
