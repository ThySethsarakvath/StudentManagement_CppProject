#ifndef ISVALID_H
#define ISVALID_H

#include "indent.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;

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
