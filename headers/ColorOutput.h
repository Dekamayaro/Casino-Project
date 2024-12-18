#pragma once

#include <string>

enum ConsoleColor {
    BLACK = 30,
    RED = 31,
    BRIGHT_RED = 91,
    GREEN = 32,
    BRIGHT_GREEN = 92,
    YELLOW = 33,
    BRIGHT_YELLOW = 93,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    BRIGHT_CYAN = 96,
    WHITE = 37
};

/**
 * The colorizeConsoleOutput() static function colorizes the given text in the console based on the provided color code. 
 * It uses ANSI escape sequences to change the text color and then resets the color after the text is printed.
 * 
 * @param colorCode The ANSI color code to apply to the text.
 * @param text The text to be colorized and output to the console.
 */
class ColorOutput {
    public:
        static void colorizeConsoleOutput(const int& colorCode, const std::string& text) {
            printf("\x1B[%dm%s\033[0m", colorCode, text.c_str());
        }
};