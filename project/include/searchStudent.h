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
            clearTerminal();
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %s           STUDENT FOUND           %s║\n", indent(), COLOR_BLUE, COLOR_MAGENTA);
            printf("%s╠════════════════════════════════════╣\n", indent());
            printf("%s║ %sID     :    %-22s%s ║\n", indent(), COLOR_BRIGHT_GREEN, current->id.c_str(), COLOR_MAGENTA);
            printf("%s║ %sName   :    %-22s%s ║\n", indent(), COLOR_BRIGHT_GREEN, current->name.c_str(), COLOR_MAGENTA);
            printf("%s║ %sSubject:    %-22s%s ║\n", indent(), COLOR_BRIGHT_GREEN, current->subject.c_str(), COLOR_MAGENTA);
            printf("%s╚════════════════════════════════════╝\n", indent());
            enter();
            return;
        }
        current = current->next;
    }
    clearTerminal();
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║ No student found with ID: %s%-9s%s║\n",
           indent(), COLOR_BRIGHT_YELLOW, searchID.substr(0, 9).c_str(), COLOR_MAGENTA);
    printf("%s╚════════════════════════════════════╝\n", indent());

    enter();
    cout << COLOR_RESET;
}

// Search by name (partial match)
void searchByName(StudentList *list, const string &teacherSubject)
{
    cout << COLOR_MAGENTA;
    string searchName;
    cout << indent() << "Enter Student Name: ";
    getline(cin, searchName);

    Student *current = list->head;
    bool foundAny = false;

    clearTerminal();

    // First check if any matches exist
    while (current)
    {
        if (current->subject == teacherSubject)
        {
            string currNameLower = current->name;
            string searchLower = searchName;
            transform(currNameLower.begin(), currNameLower.end(), currNameLower.begin(), ::tolower);
            transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

            if (currNameLower.find(searchLower) != string::npos)
            {
                foundAny = true;
                break;
            }
        }
        current = current->next;
    }

    if (foundAny)
    {
        // Display header
        printf("%s╔══════════════════════════════════════════════╗\n", indent());
        printf("%s║ %s                SEARCH RESULTS               %s║\n", indent(), COLOR_BLUE, COLOR_MAGENTA);
        printf("%s╠═══════════╦══════════════════════╦═══════════╣\n", indent());
        printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-9s%s ║\n", indent(),
               COLOR_BRIGHT_GREEN, "ID", COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, "Name", COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, "Subject", COLOR_MAGENTA);
        printf("%s╠═══════════╬══════════════════════╬═══════════╣\n", indent());

        // Display matches
        current = list->head;
        while (current)
        {
            if (current->subject == teacherSubject)
            {
                string currNameLower = current->name;
                string searchLower = searchName;
                transform(currNameLower.begin(), currNameLower.end(), currNameLower.begin(), ::tolower);
                transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

                if (currNameLower.find(searchLower) != string::npos)
                {
                    printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-9s%s ║\n", indent(),
                           COLOR_BRIGHT_GREEN, current->id.c_str(), COLOR_MAGENTA,
                           COLOR_BRIGHT_GREEN, current->name.c_str(), COLOR_MAGENTA,
                           COLOR_BRIGHT_GREEN, current->subject.c_str(), COLOR_MAGENTA);
                }
            }
            current = current->next;
        }
        printf("%s╚═══════════╩══════════════════════╩═══════════╝\n", indent());
    }
    else
    {
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ No students name: %s%-14s%s   ║\n",
               indent(), COLOR_BRIGHT_YELLOW, searchName.substr(0, 14).c_str(), COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());
    }
    enter();
    cout << COLOR_RESET;
}

// Teacher search menu
void searchStudentMenu(StudentList *list, const string &teacherSubject)
{
    while (true)
    {
        clearTerminal();
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

        switch (choice)
        {
        case 1:
            searchByID(list, teacherSubject);
            break;
        case 2:
            searchByName(list, teacherSubject);
            break;
        case 3:
            clearTerminal();
            return; // Exit to main menu
        default:
            cout << COLOR_BRIGHT_RED << indent() << "Invalid choice!" << COLOR_RESET;
        }
    }
}

#endif // SEARCH_STUDENT_H