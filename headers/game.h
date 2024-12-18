#pragma once
#include "player.h"
#include "bar.h"
#include <ostream>
#include <iostream>
#include <limits>
#include <functional>

class Game {
public:
    string name;
    virtual bool play(ostream& out)=0;
    virtual ~Game() = default;
protected:
    virtual void outputMenu(ostream& out)=0;
    virtual bool calculateOutcome()=0;

protected:
    int getValidInput(int minRange, int maxRange, std::istream& in, 
        std::ostream& out, 
        const std::function<void(std::ostream&)>& menu) {
        
        int input;
        while(true) {
            menu(out);
            in >> input;

            while(in && (maxRange >= input && input >= minRange)) {
                return input;
            }

            out << endl << "Invalid input. Please re-enter value between " 
                << minRange << " - " << maxRange << endl; 

            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }
};
