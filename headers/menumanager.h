#pragma once

#include "../headers/game.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class MenuManager {
public:
    static void displayIntroMenu(std::ostream& out);
    static void displayDifficultyMenu(std::ostream& out);
    static void displayMainMenu(std::ostream& out, const vector<std::unique_ptr<Game>>& games);
    static void displayBackstory(std::ostream& out, int choice);
    static void formatScreenTop(std::ostream& out);
    static void formatScreenBottom(std::ostream& out);
    static void generateLoadingBar(std::ostream& out);
};