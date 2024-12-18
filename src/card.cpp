#include "../headers/card.h"

/**
 * Constructs a default Card object with the suit set to 'c' (clubs) and rank set to 2.
 */
Card::Card() {
    suit = 'c';
    rank = 2;
}

/**
 * Constructs a Card object with the specified suit and rank.
 * 
 * @param c The suit of the card, represented by a character: 'c' for clubs, 'd' for diamonds, 
 *          'h' for hearts, and 's' for spades. Any invalid character defaults to 'c' (clubs).
 * @param x The rank of the card, an integer between 2 and 13 (inclusive). Any invalid rank 
 *          outside this range defaults to 2 (the lowest rank).
 */

Card::Card(char c, int x){
    c = tolower(c);
    if (c == 'c' || c == 'd' || c == 'h' || c == 's') {
        suit = c;
    } else {
        suit = 'c';
    }
    if (x > 0 && x < 14) {
        rank = x;
    } else {
        rank = 2;
    }
}

char Card::getSuit() const{
    return suit;
}

int Card::getRank() const{
    return rank;
}

/*
* Overloads the << operator to print out the card in the format of "Rank of Suit"
*/
ostream & operator<<(ostream &out, const Card &card){
    out << "[";
    if (card.getRank() == 1){
        out << "A";
    } else if (card.getRank() < 11) {
        out << card.getRank();
    } else if(card.getRank() == 11){
        out << "J";
    } else if(card.getRank() == 12){
        out << "Q";
    } else{
        out << "K";
    }

    if (card.getSuit() == 'c') {
        out << " \033[30m\u2663\033[0m"; // greyish Clubs symbol
    } else if (card.getSuit() == 's') {
        out << " \033[30m\u2660\033[0m"; // greyish Spades symbol
    } else if (card.getSuit() == 'd') {
        out << " \033[31m\u2666\033[0m"; // Red Diamonds symbol
    } else if (card.getSuit() == 'h') {
        out << " \033[31m\u2665\033[0m"; // Red Hearts symbol
    } 

    out << "]";
    return out;
}