#include "../headers/roulette.h"
#include <cctype>
#include <cstring>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include <limits>
#include <thread>
#include <ctime>
#include <set>

using namespace std;

Roulette::Roulette(Player& player)
{   
    name = "Roulette";
    this->player = &player;
    calculateChips();
    //setting all bet values to 0
    memset(bets, 0, (sizeof(bets) / sizeof(bets[0])) * sizeof(bets[0]));
}

void Roulette::calculateChips()
{
    int userWallet = player->getWallet();
    //the player will only have 1 chips, 5 chips, 10 chips, 25 chips, 100 chips, 500 chips, and 1000 chips

    //if user has <=1500 dollars, then they will get no 1000 chips
    if(1500 >= userWallet)
    {
        oneThousand = 0;
        //calculating 500 chips
        fiveHundread = userWallet / 500;
        userWallet %= 500;
        //calculating 100 chips
        oneHundread = userWallet / 100;
        userWallet %= 100;
        //calcualting 25 chips
        twentyFive = userWallet / 25;
        userWallet %= 25;
        //calculating 10 chips
        ten = userWallet / 10;
        userWallet %= 10;
        //calculating 5 chips
        five = userWallet / 5;
        userWallet %= 5;
        //calculating 1 chips
        one = userWallet;
    }
    else
    {
        oneThousand = userWallet / 1000;
        userWallet %= 1000;
        //calculating 500 chips
        fiveHundread = userWallet / 500;
        userWallet %= 500;
        //calculating 100 chips
        oneHundread = userWallet / 100;
        userWallet %= 100;
        //calcualting 25 chips
        twentyFive = userWallet / 25;
        userWallet %= 25;
        //calculating 10 chips
        ten = userWallet / 10;
        userWallet %= 10;
        //calculating 5 chips
        five = userWallet / 5;
        userWallet %= 5;
        //calculating 1 chips
        one = userWallet;
    }
}

void Roulette::showChips(ostream& out)
{
    //cout << "\033[c1;c2" << word << "\033[0" << endl;
        //c1 back, c2 fore
    calculateChips();
    out << "\033[40;37m" << "one: " << one << "\033[0m " 
        << "\033[40;31m" << "five: " << five << "\033[0m "
        << "\033[40;34m" << "ten: " << ten << "\033[0m "
        << "\033[40;32m" << "twenty-five: " << twentyFive << "\033[0m " 
        << "\033[40;36m" << "one hundread: " << oneHundread << "\033[0m "
        << "\033[40;35m" << "five hundread: " << fiveHundread << "\033[0m "
        << "\033[40;33m" << "one thousand: " << oneThousand << "\033[0m"
        << endl;
}

void Roulette::placeBet(int bet, int betIndex)
{
    //need to validate input;
    while(bet > player->getWallet() || 0 > bet)
    {
        cout << "Your bet is invalid.\nYou currently have $" << player->getWallet() << endl;
        cout << "Please input a bet that is greater than 0 but less than or equal to what you have: " << endl;
        clearCin(cin);
        cin >> bet;
    }

    bets[betIndex] = bet;
}

int Roulette::payoutWin(int winningNum) //supposed to only be responsible for the payout
{
    //need to calculate total that was bet && the total that was won
    int totalWon = 0, totalBet = 0;
    std::set<int> row1 = {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34};
    std::set<int> row2 = {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35};
    std::set<int> row3 = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36};
    std::set<int> dozen1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::set<int> dozen2 = {13, 14, 15, 16, 17, 18, 19, 20, 21 ,22, 23, 24};
    std::set<int> dozen3 = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
    std::set<int> odds = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
    std::set<int> evens = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
    std::set<int> red = {32, 19, 21, 25, 34, 27, 36, 30, 23, 5, 16, 1, 14, 9, 18, 7, 12, 3}; 
    std::set<int> black = {15, 4, 2, 17, 6, 13, 11, 8, 10, 24, 33, 20, 31, 22, 29, 28, 35, 26};
    std::set<int> half1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    std::set<int> half2 = {19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};

    //calculating total ammount won
    totalWon = (35 * bets[winningNum]);
    //need to calculate if they bet on any special function
    if(0 != winningNum && 37 != winningNum)
    {
        // 38, 39, 40 --> rows 1, 2, 3
        if((0 != bets[38]) && (row1.find(winningNum) != row1.end())) //row1 {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34}
            totalWon += (2 * bets[38]);
        if((0 != bets[39]) && (row2.find(winningNum) != row2.end())) //row2 {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35}
            totalWon += (2 * bets[39]);
        if((0 != bets[40]) && (row2.find(winningNum) != row2.end())) //row3 {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36}
            totalWon += (2 * bets[40]);
        // 41, 42, 43 --> dozens 1, 2, 3
        if((0 != bets[41]) && (dozen1.find(winningNum) != dozen1.end())) //dozen1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
            totalWon += (2 * bets[41]);
        if((0 != bets[42]) && (dozen2.find(winningNum) != dozen2.end())) //dozen2 {13, 14, 15, 16, 17, 18, 19, 20, 21 ,22, 23, 24};
            totalWon += (2 * bets[42]);
        if((0 != bets[43]) && (dozen3.find(winningNum) != dozen3.end())) //dozen3 {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
            totalWon += (2 * bets[43]);
        // 44, 45 --> odds or evens
        if((0 != bets[44]) && (odds.find(winningNum) != odds.end()))
            totalWon += bets[44];
        if((0 != bets[45]) && (evens.find(winningNum) != evens.end()))
            totalWon += bets[45];
        // 46, 47 --> red or black
        if((0 != bets[46]) && (red.find(winningNum) != red.end()))
            totalWon += bets[46];
        if((0 != bets[47]) && (black.find(winningNum) != black.end()))
            totalWon += bets[47];
        // 48, 49 --> half1 or half2
        if((0 != bets[48]) && (half1.find(winningNum) != half1.end()))
            totalWon += bets[48];
        if((0 != bets[49]) && (half2.find(winningNum) != half2.end()))
            totalWon += bets[49];
    }

    //finding how much the player bet
    for(int i = 0; i < 50; i++)
    {
        totalBet += bets[i];
    }

    return (totalWon - totalBet);
}

bool Roulette::calculateOutcome()
{
    bool playerWon = -1;
    
    //need to calculate the total probability of the user getting some sort of payout
    double totalProbability = calculateTotalProbability();
    //if the player bets on all of the numebrs, then they can't 'lose'
    if((single * 38) == totalProbability)
        return true;

    //if the player does not bet on all of the numbers, hey have a chance to loose
    totalProbability *= player->getLuck();

    int percentWinChance = totalProbability * 100;
    
    //figuring out if the player's number(s) were selected
    srand(time(0));
    playerWon = ((rand() % 101) < percentWinChance);
    return playerWon;
}

int Roulette::spinWheel(bool playerWon)
{
    srand(time(0));
    //find what the player bet on:
    int playerBet[38] = {};
    int numberOfBets = 0;
    int chosenNum = -1;
    //puts a '1'(int) on every spot in playerBets where the player bet && increments numBets for every bet found
        //checks for bets on singles
    for(int i = 0; i < 38; i++)
    {
        if(0 != bets[i])
        {
            playerBet[i] = 1;
            numberOfBets++;
        }
    }

    //checking for special bets:
    if(0 != bets[38]) //row1 {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34}
    {
        playerBet[1] = 1;
        playerBet[4] = 1;
        playerBet[7] = 1;
        playerBet[10] = 1;
        playerBet[13] = 1;
        playerBet[16] = 1;
        playerBet[19] = 1;
        playerBet[22] = 1;
        playerBet[25] = 1;
        playerBet[28] = 1;
        playerBet[31] = 1;
        playerBet[34] = 1;
        numberOfBets += 12;
    }
    if(0 != bets[39]) //row2 {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35}
    {
        playerBet[2] = 1;
        playerBet[5] = 1;
        playerBet[8] = 1;
        playerBet[11] = 1;
        playerBet[14] = 1;
        playerBet[17] = 1;
        playerBet[20] = 1;
        playerBet[23] = 1;
        playerBet[26] = 1;
        playerBet[29] = 1;
        playerBet[32] = 1;
        playerBet[35] = 1;
        numberOfBets += 12;
    }
    if(0 != bets[40]) //row3 {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36}
    {
        playerBet[3] = 1;
        playerBet[6] = 1;
        playerBet[9] = 1;
        playerBet[12] = 1;
        playerBet[15] = 1;
        playerBet[18] = 1;
        playerBet[21] = 1;
        playerBet[24] = 1;
        playerBet[27] = 1;
        playerBet[30] = 1;
        playerBet[33] = 1;
        playerBet[36] = 1;
        numberOfBets += 12;
    }
    if(0 != bets[41]) //dozen1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    {
        playerBet[1] = 1;
        playerBet[2] = 1;
        playerBet[3] = 1;
        playerBet[4] = 1;
        playerBet[5] = 1;
        playerBet[6] = 1;
        playerBet[7] = 1;
        playerBet[8] = 1;
        playerBet[9] = 1;
        playerBet[10] = 1;
        playerBet[11] = 1;
        playerBet[12] = 1;
        numberOfBets += 12;
    }
    if(0 != bets[42]) //dozen2 {13, 14, 15, 16, 17, 18, 19, 20, 21 ,22, 23, 24};
    {
        playerBet[13] = 1;
        playerBet[14] = 1;
        playerBet[15] = 1;
        playerBet[16] = 1;
        playerBet[17] = 1;
        playerBet[18] = 1;
        playerBet[19] = 1;
        playerBet[20] = 1;
        playerBet[21] = 1;
        playerBet[22] = 1;
        playerBet[23] = 1;
        playerBet[24] = 1;
        numberOfBets += 12;
    }
    if(0 != bets[43]) //dozen3 {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
    {   
        playerBet[25] = 1;
        playerBet[26] = 1;
        playerBet[27] = 1;
        playerBet[28] = 1;
        playerBet[29] = 1;
        playerBet[30] = 1;
        playerBet[31] = 1;
        playerBet[32] = 1;
        playerBet[33] = 1;
        playerBet[34] = 1;
        playerBet[35] = 1;
        playerBet[36] = 1;
        numberOfBets += 12;
    }
    if(0 != bets[44]) //odd {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35}
    {
        playerBet[1] = 1;
        playerBet[3] = 1;
        playerBet[5] = 1;
        playerBet[7] = 1;
        playerBet[9] = 1;
        playerBet[11] = 1;
        playerBet[13] = 1;
        playerBet[15] = 1;
        playerBet[17] = 1;
        playerBet[19] = 1;
        playerBet[21] = 1;
        playerBet[23] = 1;
        playerBet[25] = 1;
        playerBet[27] = 1;
        playerBet[29] = 1;
        playerBet[31] = 1;
        playerBet[33] = 1;
        playerBet[35] = 1;
        numberOfBets += 18;
    }
    if(0 != bets[45]) //even {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36}
    {
        playerBet[2] = 1;
        playerBet[4] = 1;
        playerBet[6] = 1;
        playerBet[8] = 1;
        playerBet[10] = 1;
        playerBet[12] = 1;
        playerBet[14] = 1;
        playerBet[16] = 1;
        playerBet[18] = 1;
        playerBet[20] = 1;
        playerBet[22] = 1;
        playerBet[24] = 1;
        playerBet[26] = 1;
        playerBet[28] = 1;
        playerBet[30] = 1;
        playerBet[32] = 1;
        playerBet[34] = 1;
        playerBet[36] = 1;
        numberOfBets += 18;
    }
    if(0 != bets[46]) //red {32, 19, 21, 25, 34, 27, 36, 30, 23, 5, 16, 1, 14, 9, 18, 7, 12, 3}
    {
        playerBet[32] = 1;
        playerBet[19] = 1;
        playerBet[21] = 1;
        playerBet[25] = 1;
        playerBet[34] = 1;
        playerBet[27] = 1;
        playerBet[36] = 1;
        playerBet[30] = 1;
        playerBet[23] = 1;
        playerBet[5] = 1;
        playerBet[16] = 1;
        playerBet[1] = 1;
        playerBet[14] = 1;
        playerBet[9] = 1;
        playerBet[18] = 1;
        playerBet[7] = 1;
        playerBet[12] = 1;
        playerBet[3] = 1;
        numberOfBets += 18;
    }
    if(0 != bets[47]) //black {15, 4, 2, 17, 6, 13, 11, 8, 10, 24, 33, 20, 31, 22, 29, 28, 35, 26}
    {
        playerBet[15] = 1;
        playerBet[4] = 1;
        playerBet[2] = 1;
        playerBet[17] = 1;
        playerBet[6] = 1;
        playerBet[13] = 1;
        playerBet[11] = 1;
        playerBet[8] = 1;
        playerBet[10] = 1;
        playerBet[24] = 1;
        playerBet[33] = 1;
        playerBet[20] = 1;
        playerBet[31] = 1;
        playerBet[22] = 1;
        playerBet[29] = 1;
        playerBet[28] = 1;
        playerBet[35] = 1;
        playerBet[26] = 1;
        numberOfBets += 18;
    }
    if(0 != bets[48]) //half1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}
    {
        playerBet[1] = 1;
        playerBet[2] = 1;
        playerBet[3] = 1;
        playerBet[4] = 1;
        playerBet[5] = 1;
        playerBet[6] = 1;
        playerBet[7] = 1;
        playerBet[8] = 1;
        playerBet[9] = 1;
        playerBet[10] = 1;
        playerBet[11] = 1;
        playerBet[12] = 1;
        playerBet[13] = 1;
        playerBet[14] = 1;
        playerBet[15] = 1;
        playerBet[16] = 1;
        playerBet[17] = 1;
        playerBet[18] = 1;
        numberOfBets += 18;
    }
    if(0 != bets[49]) //half2 {19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36}
    {
        playerBet[19] = 1;
        playerBet[20] = 1;
        playerBet[21] = 1;
        playerBet[22] = 1;
        playerBet[23] = 1;
        playerBet[24] = 1;
        playerBet[25] = 1;
        playerBet[26] = 1;
        playerBet[27] = 1;
        playerBet[28] = 1;
        playerBet[29] = 1;
        playerBet[30] = 1;
        playerBet[31] = 1;
        playerBet[32] = 1;
        playerBet[33] = 1;
        playerBet[34] = 1;
        playerBet[35] = 1;
        playerBet[36] = 1;
        numberOfBets += 18;
    }

    //if the player won, then randomly select a number from those that they bet on
    if(playerWon)
    {
        //gives us a random index that the user bet on;
        int chosenPlace = rand() % numberOfBets + 1;
        //finding what number that corresponds to
        for(int i = 0; (i < 38) && (chosenPlace > 0); i++)
        {
            if((1 == playerBet[i]) && (1 != chosenPlace))
                chosenPlace--;
            else if((1 == playerBet[i]) && (1 == chosenPlace))
            {
                if(0 == i)
                    chosenNum = 0;
                else
                    chosenNum = i;

                i = 38;
            }
        }

        return chosenNum;
    }
    else // if the player lost, randomly select what number was roled from those that they did NOT bet on
    {
        //gives us a random index that the user did NOT bet on
        int chosenPlace = rand() % (38 - numberOfBets) + 1;
        //finding what number that corresponds to
        for(int i = 0; (i < 38) && (chosenPlace > 0); i++)
        {
            if((0 == playerBet[i]) && (1 != chosenPlace))
                chosenPlace--;
            else if((0 == playerBet[i]) && (1 == chosenPlace))
            {
                if(0 == i)
                    chosenNum = 0;
                else
                    chosenNum = i;

                i = 38;
            }
        }

        return chosenNum;
    }
}

void Roulette::outputMenu(ostream& out)
{
    //asking user what they would like to bet on:
    out << "Would you like to bet on:\n" <<
            "1: A Number\n" <<
            "2: A Dozen or Row\n" <<
            "3: Red or Black\n" <<
            "4: Even or Odd\n" <<
            "5: (1 - 18) or (19 - 36)\n" <<
            "Enter 'q' to quit: " << endl;
}

void Roulette::bettingOnSingles(ostream& out)
{
    string userNumBet;
    int index;

    visuals Visuals;
    Visuals.visualizeBoard(out);
    showChips(out);
    out << endl;

    out << "Please enter the number you would like to bet:\n" <<
            "Options: 0, 00, 1 - 36: " << endl;
    
    clearCin(cin);
    cin >> userNumBet;

    //validating input: 
    bool badIn = true;
    while(badIn)
    {
        try
        {
            stoi(userNumBet);
            badIn = false;
        }
        catch(const std::invalid_argument& inv)
        {
            out << endl << "\033[31mBad input, please try again.\033[0m" << endl << endl;
            out << "Please enter the number you would like to bet:\n" <<
            "Options: 0, 00, 1 - 36: " << endl;

            clearCin(cin);
            cin >> userNumBet;
        }
    }
    
    int userNum = stoi(userNumBet);

    while(true)
    {
        if(userNumBet == "00" && userNum == 0) //betting on 00
        {
            index = 37;
            break;
        }
        else if(userNumBet != "00" && userNum == 0) // betting on 0
        {
            index = 0;
            break;
        }
        else if(userNum >= 1 && userNum <= 36) // betting on 1 - 36
        {
            index = userNum;
            break;
        }
        else //something is wrong
        {
            out << "Invalid input." << endl;
            out << "Please enter the number you would like to bet:\n" <<
                   "Options: 0, 00, 1 - 36: " << endl;

            cin.clear(); // Clear error flags
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            cin >> userNumBet;
            userNum = stoi(userNumBet);
        }
    }

    //assuming valid input
    out << endl << "How much would you like to bet on: " << userNumBet << "?" << endl;
    int userBet;
    clearCin(cin);
    cin >> userBet;

    placeBet(userBet, index);
}

void Roulette::bettingOnRowDozen(ostream& out) 
{
    char dozenRow;
    int index;

    visuals Visuals;
    Visuals.visualizeBoard(out);
    showChips(out);
    out << endl;

    out << "Please enter 'd' for Dozen or 'r' for Rows: " << endl;
    clearCin(cin);
    cin >> dozenRow;

    //input validation:
    while(!cin || (!('d' == tolower(dozenRow)) && !('r' == tolower(dozenRow))))
    {
        out << "Invalid input" << endl;
        out << "Please enter 'd' for Dozen or 'r' for Rows: " << endl;
        clearCin(cin);
        cin >> dozenRow;
    }

    //assuming good input:
        //need to determine where the user wants to bet:
    if('r' == tolower(dozenRow)) // betting on a row
    {
        out << "Please select a row to bet on:" << endl;
        out << "1) Row 1 (R1)" << endl;
        out << "2) Row 2 (R2)" << endl;
        out << "3) Row 3 (R3)" << endl;
        out << "Enter 1, 2, or 3:" << endl;

        int userRow;
        clearCin(cin);
        cin >> userRow;

        //input validation:
        while(!cin || (!(1 == userRow) && !(2 == userRow) && !(3 == userRow)))
        {
            out << "Invalid input" << endl;

            out << "Please select a row to bet on:" << endl;
            out << "1) Row 1 (R1)" << endl;
            out << "2) Row 2 (R2)" << endl;
            out << "3) Row 3 (R3)" << endl;
            out << "Enter 1, 2, or 3:" << endl;

            clearCin(cin);
            cin >> userRow;
        }

        if(1 == userRow)
            index = 38;
        else if(2 == userRow)
            index = 39;
        else if(3 == userRow)
            index = 40;

        //assuming valid input now
            //getting user's bet for their selected column:
        out << "How much would you like to bet on row " << userRow << "?" << endl;
        int userBet;

        clearCin(cin);
        cin >> userBet;

        placeBet(userBet, index);
    }
    else //betting on a dozen
    {
        out << "Please select a dozen to bet on:" << endl;
        out << "1) Dozen 1 (1 - 12)" << endl;
        out << "2) Dozen 2 (13 - 24)" << endl;
        out << "3) Dozen 3 (25 - 36)" << endl;
        out << "Enter 1, 2, or 3:" << endl;

        int userDozen;
        
        clearCin(cin);
        cin >> userDozen;

        //input validation:
        while(!cin || (!(1 == userDozen) && !(2 == userDozen) && !(3 == userDozen)))
        {
            out << "Invalid input" << endl;

            out << "Please select a dozen to bet on:" << endl;
            out << "1) Dozen 1 (1 - 12)" << endl;
            out << "2) Dozen 2 (13 - 24)" << endl;
            out << "3) Dozen 3 (25 - 36)" << endl;
            out << "Enter 1, 2, or 3:" << endl;

            clearCin(cin);
            cin >> userDozen;
        }

        if(1 == userDozen)
            index = 41;
        else if(2 == userDozen)
            index = 42;
        else if(3 == userDozen)
            index = 43;

        //assuming correct input
            //need to get user's bet on the dozen of their choice;
        out << "How much would you like to bet on dozen " << userDozen << "?" << endl;
        int userBet;

        clearCin(cin);
        cin >> userBet;

        placeBet(userBet, index);
    }
}

void Roulette::bettingOnRedBlack(ostream& out)
{
    //need to get user data as to red or black
    visuals Visuals;
    Visuals.visualizeBoard(out);
    showChips(out);
    out << endl;

    out << "\nPlease select Red or Black" << endl;
    out << "'r' for Red" << endl;
    out << "'b' for Black" << endl;

    char redBlack;
    clearCin(cin);
    cin >> redBlack;

    while(!cin || (!('r' == tolower(redBlack)) && !('b' == tolower(redBlack))))
    {
        out << "Invalid input" << endl;

        out << "Please select Red or Black" << endl;
        out << "'r' for Red" << endl;
        out << "'b' for Black" << endl;

        clearCin(cin);
        cin >> redBlack;
    }

        //assuming good input
    if('r' == tolower(redBlack)) //if they want to bet on red
    {
        out << "How much would you like to bet on red?" << endl;
        int betRed;

        clearCin(cin);
        cin >> betRed;

        placeBet(betRed, 46);
    }
    else //they are betting on black
    {
        out << "How much would you like to bet on black?" << endl;
        int betBlack;

        clearCin(cin);
        cin >> betBlack;

        placeBet(betBlack, 47);
    }
}

void Roulette::bettingOnOddEven(ostream& out)
{
    out << "Please select Even or Odd" << endl;
    out << "'e' for Even" << endl;
    out << "'o' for Odd" << endl;

    visuals Visuals;
    Visuals.visualizeBoard(out);
    showChips(out);
    out << endl;

    char evenOdd;
    clearCin(cin);
    cin >> evenOdd;

    while(!cin || (!('e' == tolower(evenOdd)) && !('o' == tolower(evenOdd))))
    {
        out << "Invalid input" << endl;

        out << "Please select Even or Odd" << endl;
        out << "'e' for Even" << endl;
        out << "'o' for Odd" << endl;

        clearCin(cin);
        cin >> evenOdd;
    }

    //assuming good input
    if('e' == tolower(evenOdd)) //if they want to bet on Even
    {
        out << "How much would you like to bet on Even?" << endl;
        int betEven;

        clearCin(cin);
        cin >> betEven;
        
        placeBet(betEven, 45);
    }
    else //they are betting on Odd
    {
        out << "How much would you like to bet on Odd?" << endl;
        int betOdd;

        clearCin(cin);
        cin >> betOdd;

        placeBet(betOdd, 44);
    }
}

void Roulette::bettingOnHalfs(ostream& out)
{
    out << "Please select (1 - 18) or (19 - 36)" << endl;
    out << "1 for (1 - 18)" << endl;
    out << "2 for (19 - 36)" << endl;

    visuals Visuals;
    Visuals.visualizeBoard(out);
    showChips(out);
    out << endl;

    int whichHalf;
    
    clearCin(cin);
    cin >> whichHalf;

    while(!cin || (!(1 == whichHalf) && !(2 == whichHalf)))
    {
        out << "Invalid input" << endl;

        out << "Please select (1 - 18) or (19 - 36)" << endl;
        out << "1 for (1 - 18)" << endl;
        out << "2 for (19 - 36)" << endl;

        clearCin(cin);
        cin >> whichHalf;
    }

    //assuming good input
    if(1 == whichHalf) //if they want to bet on (1 - 18)
    {
        out << "How much would you like to bet on (1 - 18)?" << endl;
        int betFirst;

        clearCin(cin);
        cin >> betFirst;

        placeBet(betFirst, 48);
    }
    else //they are betting on (19 - 36)
    {
        out << "How much would you like to bet on (19 - 36)?" << endl;
        int betSecond;

        clearCin(cin);
        cin >> betSecond;

        placeBet(betSecond, 49);
    }
}

bool Roulette::play(ostream& out)
{
    bool playing = 0;
    string userChoice;

    clearScreen();
    out << "\033[2J\033[H" << endl;
    out << "Welcome to roulete!" << endl << endl;
    
    outputMenu(out);

    //validating input from outputMenu
    cin >> userChoice;
    while(!cin || (!("1" == userChoice) && !("2" == userChoice) && !("3" == userChoice) && !("4" == userChoice) && !("5" == userChoice) && !("q" == userChoice) && !("Q" == userChoice)))
    {
        out << "\033[40;31mInvlaid input, please input a number (1 - 5) or 'q' to quit: \033[0m" << endl;
        outputMenu(out);
        
        clearCin(cin);
        cin >> userChoice;
    }

    //loop until user wants to quit or the player has no money
    while((("q" != userChoice) && ("Q" != userChoice)) && (0 != player->getWallet()))
    {
        if("1" == userChoice) //betting on a number 0, 00, 1 --> 36
        {
            clearScreen();
            bettingOnSingles(out);
        }
        else if("2" == userChoice) //betting on a row or dozen
        {
            clearScreen();
            bettingOnRowDozen(out);
        }
        else if("3" == userChoice) //betting on red or black
        {
            clearScreen();
            bettingOnRedBlack(out);
        }
        else if("4" == userChoice) //betting on odd or even
        {
            clearScreen();
            bettingOnOddEven(out);
        }
        else if("5" == userChoice) //betting on first or second half (1 - 18) or (19 - 36)
        {
            clearScreen();
            bettingOnHalfs(out);
        }

        visuals Visuals;
        Visuals.visualizeWheel(out);

        int numberSpun = spinWheel(calculateOutcome());
        out << "The wheel landed on: " << numberSpun << "!" << endl;

        int wonLoss = payoutWin(numberSpun);
        player->changeWallet(wonLoss);
        if(0 <= wonLoss)
            out << "You won $" << wonLoss << "!" << endl;
        else
            out << "You lost $" << (-1 * wonLoss) << endl;


        calculateChips();

        //for spacing
        out << endl << endl << endl;

        int totalBet;
        for(int i = 0; i < 50; i++)
        {
            totalBet += bets[i];
        }

        if(totalBet >= player->getWallet())
        {
            clearBets();
            out << "Your bets were cleared because you either could not cover them or you had exactly enough." << endl << endl << endl << endl;
        }  

        out << "Would you like to play again?" << endl;
        out << endl << "Chips:" << endl;
        showChips(out);
        out << endl;
        outputMenu(out);
        
        
        clearCin(cin);
        cin >> userChoice;
        while(!cin || (!("1" == userChoice) && !("2" == userChoice) && !("3" == userChoice) && !("4" == userChoice) && !("5" == userChoice) && !("q" == userChoice) && !("Q" == userChoice)))
        {
            out << "\033[40;31mInvlaid input, please input a number (1 - 5) or 'q' to quit: \033[0m" << endl;
            outputMenu(out);
            
            clearCin(cin);
            cin >> userChoice;
        }  
    }

    return playing;
}

double Roulette::calculateTotalProbability()
{
    double totalProb = 0;

    //singles are from index 0 - 37
    for(int i = 0; i < 38; i++)
    {
        if(0 != bets[i])
            totalProb += single;
    }

    //rows and dozens are from index 38 - 43
    for(int i = 38; i < 44; i++)
    {
        if(0 != bets[i])
            totalProb += row_dozen;
    }

    //red, black, even, odd, (1 - 18), and (19 - 36) are from index 44 - 49
    for(int i = 44; i < 50; i++)
    {
        if(0 != bets[i])
            totalProb += block;
    }

    return totalProb;
}

void Roulette::clearScreen()
{
    for(int i = 0; i < 50; i++)
    {
        cout << endl;
    }
    cout << "\033[2J\033[H" << endl;
}

void Roulette::clearBets()
{
    memset(bets, 0, (sizeof(bets) / sizeof(bets[0])) * sizeof(bets[0]));
}

void Roulette::clearCin(istream& in)
{
    in.clear();
    in.ignore(numeric_limits<streamsize>::max(), '\n');
}
