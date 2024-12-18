#pragma once

#include <iostream>

using namespace std;

class Card {
 private:
    char suit;
    int rank;
 public:
    Card();
    Card(char, int);
    char getSuit() const;
    int getRank() const;
    friend ostream& operator<<(ostream &, const Card &);
};