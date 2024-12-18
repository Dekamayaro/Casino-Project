#include "../headers/drink.h"
#include "../headers/player.h"
#include "../headers/ColorOutput.h"
#include <iostream>

class Margarita : public Drink {
    public:
        Margarita() : Drink("Margarita", 8, [](Player& player) {
            bool applyBuff = std::rand() % 2 == 0;
            double effectiveValue = 5 + std::rand() % 6;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class Oldfashioned : public Drink {
    public:
        Oldfashioned() : Drink("Old Fashioned", 10, [](Player& player) {
            bool applyBuff = std::rand() % 3 == 0;
            double effectiveValue = 5 + std::rand() % 9;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class Martini : public Drink {
    public:
        Martini() : Drink("Martini", 11, [](Player& player) {
            bool applyBuff = std::rand() % 5 == 0;
            double effectiveValue = 10 + std::rand() % 19;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class MoscowMule : public Drink {
    public:
        MoscowMule() : Drink("Moscow Mule", 10, [](Player& player) {
            bool applyBuff = std::rand() % 3 == 0;
            double effectiveValue = 10 + std::rand() % 9;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class GinAndTonic : public Drink {
    public:
        GinAndTonic() : Drink("Gin and Tonic", 15, [](Player& player) {
            bool applyBuff = std::rand() % 2 == 0;
            double effectiveValue = 10 + std::rand() % 24;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class Spritz : public Drink {
    public:
        Spritz() : Drink("Spritz", 8, [](Player& player) {
            bool applyBuff = std::rand() % 4 == 0;
            double effectiveValue = 5 + std::rand() % 9;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class PinaColada : public Drink {
    public:
        PinaColada() : Drink("Pina Colada", 20, [](Player& player) {
            bool applyBuff = std::rand() % 3 == 0;
            double effectiveValue = 20 + std::rand() % 31;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};

class Mimosa : public Drink {
    public:
        Mimosa() : Drink("Mimosa", 50, [](Player& player) {
            bool applyBuff = std::rand() % 2 == 0;
            double effectiveValue = 40 + std::rand() % 51;

            if (applyBuff) {
                player.applyBuff(effectiveValue / 100);
                std::string buff = "Your luck has been buffed by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_GREEN, buff);
                cout << effectiveValue << "%" << std::endl;
            } else {
                player.applyDebuff(effectiveValue / 100);
                std::string debuff = "Your luck has been decreased by ";
                ColorOutput::colorizeConsoleOutput(BRIGHT_RED, debuff);
                cout << effectiveValue << "%" << std::endl;
            }
        }) {}
};
