#ifndef UI_H
#define UI_H

// Foreground colors
#define COLOR_RED     "\033[31m"
#define COLOR_BRIGHT_RED "\033[91m"
#define COLOR_GREEN   "\033[38;2;170;219;30m"
#define COLOR_BRIGHT_GREEN "\033[92m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BRIGHT_YELLOW "\033[93m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

// Background colors (optional)
#define BG_BLACK      "\033[40m"
#define BG_RED        "\033[41m"
#define BG_GREEN      "\033[42m"
#define BG_YELLOW     "\033[43m"
#define BG_BLUE       "\033[44m"
#define BG_MAGENTA    "\033[45m"
#define BG_CYAN       "\033[46m"
#define BG_WHITE      "\033[47m"

// Reset
#define COLOR_RESET   "\033[0m"


#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

inline string centerText(const string &text, int width) {
    if (text.length() >= width) return text;
    int padding = (width - text.length()) / 2;
    return string(padding, ' ') + text + string(padding, ' ');
}

const char* indent(){
    return "\t\t\t\t\t\t\t\t\t\t";
}
const char* indent1(){
    return "\t\t";
}

int getMenuChoice(int min, int max, const string& prompt = "Enter your choice") {
    string input;

    while (true) {
        cout << indent() << prompt << " (" << min << "-" << max << "): " << flush;

        // Only remove if stray newline is sitting in buffer
        if (cin.rdbuf()->in_avail() == 0 && cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (!getline(cin, input)) {
            cin.clear();
            cout<< indent() << "\nInput error. Try again.\n";
            continue;
        }

        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        if (input.empty()) {
            cout<< indent() << "Input cannot be empty.\n";
            continue;
        }

        // Must be all digits
        if (!all_of(input.begin(), input.end(), ::isdigit)) {
            cout<< indent() << "Please enter numbers only.\n";
            continue;
        }

        // Convert to int
        int choice;
        istringstream(input) >> choice;

        if (choice < min || choice > max) {
            cout<< indent() << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }

        return choice;
    }
}

#endif