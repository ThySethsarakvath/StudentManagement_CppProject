#ifndef SEARCH_STUDENT_H
#define SEARCH_STUDENT_H

#include "ui.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <cctype> // for tolower()

using namespace std;

// Search by ID (exact match)
void searchByID(StudentList *list, const string &teacherSubject)
{
    cout << COLOR_MAGENTA;
    string searchID;
    cout << indent() << "Enter Student ID: ";
    getline(cin, searchID);

    Student *current = list->head;
    bool found = false;

    while (current)
    {
        if (current->subject == teacherSubject && current->id == searchID)
        {
            found = true;
            cout << endl;

            clearTerminal();
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %s           STUDENT FOUND           %s║\n", indent(), COLOR_BLUE, COLOR_MAGENTA);
            printf("%s╠════════════════════════════════════╣\n", indent());
            printf("%s║ %sID     :    %-22s%s ║\n", indent(), COLOR_BRIGHT_GREEN, current->id.c_str(), COLOR_MAGENTA);
            printf("%s║ %sName   :    %-22s%s ║\n", indent(), COLOR_BRIGHT_GREEN, current->name.c_str(), COLOR_MAGENTA);
            printf("%s║ %sSubject:    %-25s%s ║\n", indent(), COLOR_BRIGHT_GREEN, current->subject.c_str(), COLOR_MAGENTA);
            printf("%s╚════════════════════════════════════╝\n", indent());

            break;
        }
        current = current->next;
    }

    if (!found)
    {
        clearTerminal();
        cout << endl;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ No student found with ID: %s%-9s%s║\n",
               indent(),
               COLOR_BRIGHT_YELLOW,
               searchID.substr(0, 9).c_str());
        printf("%s╚════════════════════════════════════╝\n", indent());
    }
    cout << COLOR_RESET;
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

// Search by name (partial match)
void searchByName(StudentList *list, const string &teacherSubject)
{
    cout << COLOR_MAGENTA;
    string searchName;
    cout << indent() << "Enter Student Name: ";
    getline(cin, searchName);

    Student *current = list->head;
    vector<Student *> matched;

    // Collect matches based on partial name and subject
    while (current)
    {
        if (current->subject == teacherSubject)
        {
            string currNameLower = current->name;
            string searchLower = searchName;

            for (char &c : currNameLower)
                c = tolower(c);
            for (char &c : searchLower)
                c = tolower(c);

            if (currNameLower.find(searchLower) != string::npos)
            {
                matched.push_back(current);
            }
        }
        current = current->next;
    }

    cout << endl;

    if (!matched.empty())
    {
        clearTerminal();
        printf("%s╔══════════════════════════════════════════════╗\n", indent());
        printf("%s║ %s                SEARCH RESULTS               %s║\n", indent(), COLOR_BLUE, COLOR_MAGENTA);

        printf("%s╠═══════════╦══════════════════════╦═══════════╣\n", indent());
        printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-9s%s ║\n", indent(),
               COLOR_BRIGHT_GREEN, "ID", COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, "Name", COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, "Subject", COLOR_MAGENTA);
        printf("%s╠═══════════╬══════════════════════╬═══════════╣\n", indent());

        for (const auto &s : matched)
        {
            printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-9s%s ║\n", indent(),
                   COLOR_BRIGHT_GREEN, s->id.c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, s->name.c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, s->subject.c_str(), COLOR_MAGENTA);
        }

        printf("%s╚═══════════╩══════════════════════╩═══════════╝\n", indent());
        cout << COLOR_RESET;
    }
    else
    {
        clearTerminal();
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ No student name: %s%-19s%s║\n",
               indent(),
               COLOR_BRIGHT_YELLOW,
               searchName.substr(0, 9).c_str());
        printf("%s╚════════════════════════════════════╝\n", indent());
    }
    cout << COLOR_RESET;
}

// Teacher search menu
void searchStudentMenu(StudentList *list, const string &teacherSubject)
{
    cout << COLOR_MAGENTA;
    while (true)
    {
        cout << COLOR_MAGENTA;
        cout << endl;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ %s        SEARCH STUDENT MENU        %s║\n", indent(), COLOR_BLUE, COLOR_MAGENTA);
        printf("%s╠════════════════════════════════════╣\n", indent());
        printf("%s║ %s1. Search by ID                    %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s║ %s2. Search by Name                  %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s║ %s3. Back to Main Menu               %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());

        int choice = getMenuChoice(1, 3);

        if (choice == 1)
        {
            searchByID(list, teacherSubject);
        }
        else if (choice == 2)
        {
            searchByName(list, teacherSubject);
        }
        else if (choice == 3)
        {
            clearTerminal();
            break;
        }
        else
        {
            cout << COLOR_BRIGHT_RED;
            printf("%sInvalid choice! Please enter 1-3\n", indent());
        }
    }
    cout << COLOR_RESET;
}

#endif // SEARCH_STUDENT_H