#ifndef UI_H
#define UI_H

// Foreground colors
#define COLOR_RED "\033[31m"
#define COLOR_BRIGHT_RED "\033[91m"
#define COLOR_GREEN "\033[38;2;170;219;30m"
#define COLOR_BRIGHT_GREEN "\033[92m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BRIGHT_YELLOW "\033[93m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_BRIGHT_WHITE "\033[97m"

// Reset
#define COLOR_RESET "\033[0m"

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

inline string centerText(const string &text, int width)
{
    if (text.length() >= width)
        return text;
    int padding = (width - text.length()) / 2;
    return string(padding, ' ') + text + string(padding, ' ');
}

const char *indent()
{
    return "\t\t\t\t\t\t\t\t\t\t";
}
const char *indent1()
{
    return "\t\t";
}

const char* banner[] = {
    "███████████████████████████████████████████████████████████████████████████████▀██████████████████████████████████████████████████████████████████████████",
    "█─▄▄▄▄█─▄─▄─█▄─██─▄█▄─▄▄▀█▄─▄▄─█▄─▀█▄─▄█─▄─▄─██▄─▀█▀─▄██▀▄─██▄─▀█▄─▄██▀▄─██─▄▄▄▄█▄─▄▄─█▄─▀█▀─▄█▄─▄▄─█▄─▀█▄─▄█─▄─▄─██─▄▄▄▄█▄─█─▄█─▄▄▄▄█─▄─▄─█▄─▄▄─█▄─▀█▀─▄█",
    "█▄▄▄▄─███─████─██─███─██─██─▄█▀██─█▄▀─████─█████─█▄█─███─▀─███─█▄▀─███─▀─██─██▄─██─▄█▀██─█▄█─███─▄█▀██─█▄▀─████─████▄▄▄▄─██▄─▄██▄▄▄▄─███─████─▄█▀██─█▄█─██",
    "▀▄▄▄▄▄▀▀▄▄▄▀▀▀▄▄▄▄▀▀▄▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀▀▄▄▄▀▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀"
};

void enter()
{
    cout << COLOR_BRIGHT_WHITE;
    cout << indent() << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    cout << COLOR_RESET;
}

int getMenuChoice(int min, int max, const string &prompt = "Enter your choice")
{
    string input;

    
    while (true)
    {
        cout << COLOR_CYAN << indent() << prompt << " (" << min << "-" << max << "): " << COLOR_RESET << flush;

        // Remove stray newline
        if (cin.rdbuf()->in_avail() == 0 && cin.peek() == '\n')
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (!getline(cin, input))
        {
            cin.clear();
            cout << COLOR_BRIGHT_RED << indent() << "Input error. Try again.\n"<< COLOR_RESET;
            continue;
        }

        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t"));
        input.erase(input.find_last_not_of(" \t") + 1);

        if (input.empty())
        {
            cout << COLOR_BRIGHT_RED << indent() << "Input cannot be empty.\n"<< COLOR_RESET;
            continue;
        }

        if (!all_of(input.begin(), input.end(), ::isdigit))
        {
            cout << COLOR_BRIGHT_YELLOW << indent() << "Please enter numbers only.\n"<< COLOR_RESET;
            continue;
        }

        int choice;
        istringstream(input) >> choice;

        if (choice < min || choice > max)
        {
            cout << COLOR_BRIGHT_YELLOW << indent()
                    << "Please enter a number between " << min << " and " << max << ".\n"<< COLOR_RESET;
            continue;
        }

        // Confirmed input
        cout << COLOR_BRIGHT_GREEN << indent() << "Choice accepted: " << choice << "\n"<< COLOR_RESET;
        return choice;
    }
}
// Case-insensitive string comparison
bool matches(const string &a, const string &b)
{
    if (a.length() != b.length())
        return false;
    for (size_t i = 0; i < a.length(); i++)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
}

bool isValidAge(int age) {
    return age >= 10 && age <= 100;
}

bool isValidGender(string gender) {
    return gender == "M" || gender == "m" || gender == "F" || gender == "f";
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(const std::string& dateStr)
{
    if (dateStr.length() != 10 || dateStr[2] != '-' || dateStr[5] != '-')
        return false;

    int day, month, year;
    char dash1, dash2;

    std::istringstream iss(dateStr);
    iss >> day >> dash1 >> month >> dash2 >> year;

    if (iss.fail() || dash1 != '-' || dash2 != '-')
        return false;

    if (month < 1 || month > 12)
        return false;

    if (day < 1)
        return false;

    // Days per month
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                        31, 31, 30, 31, 30, 31 };

    // Adjust for leap year
    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
        return false;

    return true;
}

void clearTerminal()
{
#ifdef _WIN32
    system("cls"); // Windows

#endif
}

void dropUI(const char* lines[], int numLines, int delayMs = 380) {
    for (int i = 0; i < numLines; ++i) {
        clearTerminal();
        cout<<"\n\n\n\n";
        for (int j = numLines - i - 1; j < numLines; ++j) {
            
            cout << indent1() << lines[j] << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}


#endif