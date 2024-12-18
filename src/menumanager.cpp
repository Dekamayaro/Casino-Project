#include "../headers/menumanager.h"
#include "../headers/ColorOutput.h"
#include "../headers/game.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace this_thread;

/**
 * Displays the introductory menu for the game, including a header title, game title, loading bar, and menu options.
 * It also colors the output to provide a visually appealing experience to the user.
 * 
 * @param out The output stream to display the menu to the player.
 * 
 * @return void
 */
void MenuManager::displayIntroMenu(ostream& out) {
    const string HEADER_TITLE = R"(
                                                 ____        __
     /'\_/`\                                    /\  _`\   __/\ \__
    /\      \    ___     ___      __   __  __   \ \ \L\ \/\_\ \ ,_\
    \ \ \__\ \  / __`\ /' _ `\  /'__`\/\ \/\ \   \ \ ,__/\/\ \ \ \/
     \ \ \_/\ \/\ \L\ \/\ \/\ \/\  __/\ \ \_\ \   \ \ \/  \ \ \ \ \_
      \ \_\\ \_\ \____/\ \_\ \_\ \____\\/`____ \   \ \_\   \ \_\ \__\
       \/_/ \/_/\/___/  \/_/\/_/\/____/ `/___/> \   \/_/    \/_/\/__/
                                           /\___/
                                           \/__/
    )";

    const string TITLE = R"(
      /$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$ /$$   /$$  /$$$$$$ 
     /$$__  $$ /$$__  $$ /$$__  $$|_  $$_/| $$$ | $$ /$$__  $$
    | $$  \__/| $$  \ $$| $$  \__/  | $$  | $$$$| $$| $$  \ $$
    | $$      | $$$$$$$$|  $$$$$$   | $$  | $$ $$ $$| $$  | $$
    | $$      | $$__  $$ \____  $$  | $$  | $$  $$$$| $$  | $$
    | $$    $$| $$  | $$ /$$  \ $$  | $$  | $$\  $$$| $$  | $$
    |  $$$$$$/| $$  | $$|  $$$$$$/ /$$$$$$| $$ \  $$|  $$$$$$/
    \______/ |__/  |__/ \______/ |______/|__/  \__/ \______/ 
    )";

    ColorOutput::colorizeConsoleOutput(RED, HEADER_TITLE);

    ColorOutput::colorizeConsoleOutput(BRIGHT_YELLOW, TITLE);

    generateLoadingBar(out);

    out << endl << "Please select an option from the menu below:" << endl;
    ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, "1. Start Game\n");
    ColorOutput::colorizeConsoleOutput(BRIGHT_RED, "2. Quit\n");
}

/**
 * Displays the difficulty selection menu, showing different difficulty levels with their corresponding labels.
 * The output is colorized to highlight the difficulty levels.
 * 
 * @param out The output stream to display the menu to the player.
 * 
 * @return void
 */
void MenuManager::displayDifficultyMenu(ostream& out) {
    out << endl << "Please select a difficulty:" << endl;
    // code is on the same line, because that is how it appears in console
    out << "1. The Casual Player "; ColorOutput::colorizeConsoleOutput(GREEN, "(Easiest)\n");
    out << "2. The Average Joe "; ColorOutput::colorizeConsoleOutput(BRIGHT_YELLOW, "(Medium)\n");
    out << "3. The High Roller "; ColorOutput::colorizeConsoleOutput(BRIGHT_RED, "(Hard)\n");
}

/**
 * Displays the main menu to the player, listing available games to play along with the option to visit the bar or quit.
 * The menu options are dynamically generated based on the provided list of games.
 * 
 * @param out The output stream to display the menu to the player.
 * @param games A vector of unique pointers to Game objects, used to populate the menu with available games.
 * 
 * @return void
 */
void MenuManager::displayMainMenu(ostream& out, const vector<std::unique_ptr<Game>>& games) {
    out << "Please select an option from the menu below:" << endl;
    long unsigned int i;
    for(i = 0; i < games.size(); i++) {
        cout << i + 1 << ". Play " << games.at(i)->name << endl;
    }
    out << i + 1 << ". Visit the Bar" << endl;
    out << i + 2 << ". Quit" << endl;
}

/**
 * Displays the backstory, buffs, and playstyle for the selected character choice.
 * Provides information about the character's background, abilities, and approach to gameplay based on the player's choice.
 * 
 * @param out The output stream to display the backstory and related information to the player.
 * @param choice The character choice selected by the player (1 = The Underdog, 2 = The Realist, 3 = The High Roller).
 * 
 * @return void
 */
void MenuManager::displayBackstory(std::ostream& out, int choice) {
    out << endl;
    if(1 == choice)
    {
        ColorOutput::colorizeConsoleOutput(GREEN, "1. The Underdog\n");

        // Backstory
        ColorOutput::colorizeConsoleOutput(RED, "Backstory: ");
        out << "You grew up in a modest household, but things took a turn for the worse when your Uncle Rick rolled into town. \n"
            << "Promising fortunes from the “next big game,” he gambled away your family’s savings, leaving you broke and bitter. \n"
            << "With only the clothes on your back and a few coins in your pocket, you decide to hit the casino, hoping to turn your luck around. \n"
            << "Surprisingly, the universe seems to be on your side — starting poor might just be the key to riches." << endl << endl;

        // Buff
        ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, "Buff: ");
        out << "Increased starting luck, giving you a slight edge in early games." << endl << endl;

        // Playstyle
        ColorOutput::colorizeConsoleOutput(BRIGHT_CYAN, "Playstyle: ");
        out << "High chance of winning early, but it might dwindle as you get wealthier." << endl;
    }
    else if(2 == choice)
    {
        ColorOutput::colorizeConsoleOutput(BRIGHT_YELLOW, "2. The Realist\n");

        // Backstory
        ColorOutput::colorizeConsoleOutput(RED, "Backstory: ");
        out << "You’re no stranger to the game but no high roller either. A decent job, some savings, \n"
            << "and a bit of confidence have gotten you to the casino today. You heard about the place from a friend, and \n"
            << "now you’re here to test your skills. With your wits about you and a sensible bankroll, you’re ready for whatever \n"
            << "Lady Luck has in store. But remember, she’s fair — wins and losses come in equal measure." << endl << endl;

        // Buff
        ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, "Buff: ");
        out << "Balanced luck — a classic 50-50 chance, just like a real casino." << endl << endl;

        // Playstyle
        ColorOutput::colorizeConsoleOutput(BRIGHT_CYAN, "Playstyle: ");
        out << "Consistent, with average odds; good for players who like the true casino experience." << endl;
    }
    else if(3 == choice)
    {   
        ColorOutput::colorizeConsoleOutput(BRIGHT_RED, "3. The High Roller\n");

        // Backstory
        ColorOutput::colorizeConsoleOutput(RED, "Backstory: ");
        out << "You’ve always had everything handed to you, thanks to a hefty trust fund and your family’s connections. \n"
            << "But your friends think you’re just another spoiled rich kid who doesn’t understand risk. To prove them wrong \n"
            << "(and maybe win a fortune of your own), you’re at the casino tonight, ready to take on the odds. Unfortunately, \n"
            << "being overly confident and swimming in wealth doesn’t sit well with Lady Luck, and the odds seem stacked against you." << endl << endl;

        // Buff
        ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, "Buff: ");
        out << "Reduced luck, making it harder to win. Your fortune may be big, but your chances aren’t!" << endl << endl;

        // Playstyle
        ColorOutput::colorizeConsoleOutput(BRIGHT_CYAN, "Playstyle: ");
        out << "   Playstyle: Tougher wins, designed for a challenging experience — can you outplay the odds?" << endl;
    }
    else
    {
        out << "Invalid choice entered, not a playable class." << endl;
    }
    cout << endl;
}

/**
 * Formats and displays the top portion of the screen, including a welcome message with a border of equal signs.
 * The length of the border is proportional to the length of the welcome text.
 * 
 * @param out The output stream to display the formatted screen top.
 * 
 * @return void
 */
void MenuManager::formatScreenTop(ostream& out) {
    string welcomeText = "Welcome to Money Pit Casino!";

    for(long unsigned int i = 0; i < welcomeText.size() * (2); i++) out << "="; // Can change number of = to change length of line
    out << endl << "\t   " << welcomeText << "\t   " << endl;
    
    for(long unsigned int i = 0; i < welcomeText.size() * (2); i++) out << "=";
    out << endl; out << endl;
}

/**
 * Formats and displays the bottom portion of the screen,
 * 
 * @param out The output stream to display the formatted screen top.
 * 
 * @return void
 */
void MenuManager::formatScreenBottom(ostream& out) {
    out << endl;    
    for(int i = 0; i < 56; i++) out << "=";
    out << endl << endl;
}

/**
 * Generates and displays a simulated loading bar on the console, with a customizable width and load time.
 * The bar gradually fills up, and once complete, a "Done!" message is displayed.
 * 
 * @param out The output stream to display the loading bar.
 * 
 * @return void
 */
void MenuManager::generateLoadingBar(ostream& out) {
    const int barWidth = 50;
    const int loadTime = 2000;
    const int stepTime = loadTime / barWidth;

    out << endl << "Loading: [";
    for (int i = 0; i < barWidth; ++i) {
        sleep_for(milliseconds(stepTime)); // Simulate loading
        out << "=" << flush;
    }
    out << "] Done!" << endl;
    sleep_for(milliseconds(1000));
    out << "\33[2J\033[H";  //clears screen and moves cursor to top left
}