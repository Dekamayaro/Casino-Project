#pragma once
#include <ostream>
#include <vector>
#include <memory>
#include "../headers/player.h"
#include "../headers/bar.h"
#include "../headers/slots.h"
#include "../headers/roulette.h"
#include "../headers/blackjack.h"
#include "../headers/game.h"

class Runner {
    friend class TestClass;
private:
    Player player;
    std::vector<std::unique_ptr<Game>> games;
    Bar bar;
public:
    Runner() : player(), bar(player) {
        games.push_back(make_unique<Slots>(player));
        games.push_back(make_unique<Blackjack>(player));
        games.push_back(make_unique<Roulette>(player));
    };
    void launch(std:: istream& in, std::ostream& out);

    //Player getUser() {return player;};  // for testing

private:
    void setDifficulty(int choice);
    void startGame(std::istream& in, std::ostream& out);
    int getValidInput(istream& in, ostream& out, int min, int max) const;
};
