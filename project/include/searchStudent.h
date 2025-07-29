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
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║            STUDENT FOUND           ║\n", indent());
            printf("%s╠════════════════════════════════════╣\n", indent());
            printf("%s║ ID:      %-25s ║\n", indent(), current->id.c_str());
            printf("%s║ Name:    %-25s ║\n", indent(), current->name.c_str());
            printf("%s║ Subject: %-25s ║\n", indent(), current->subject.c_str());
            printf("%s╚════════════════════════════════════╝\n", indent());

            break;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << endl;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ No student found with ID: %-8s ║\n", indent(), searchID.c_str());
        printf("%s╚════════════════════════════════════╝\n", indent());
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

// Search by name (partial match)
void searchByName(StudentList *list, const string &teacherSubject)
{
    string searchName;
    cout << indent() << "Enter Student Name: ";
    getline(cin, searchName);

    Student *current = list->head;
    vector<Student*> matched;

    // Collect matches based on partial name and subject
    while (current)
    {
        if (current->subject == teacherSubject)
        {
            string currNameLower = current->name;
            string searchLower = searchName;

            for (char &c : currNameLower) c = tolower(c);
            for (char &c : searchLower) c = tolower(c);

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
        printf("%s╔══════════════════════════════════════════════╗\n", indent());
        printf("%s║              SEARCH RESULTS                  ║\n", indent());
        printf("%s╠═══════════╦══════════════════════╦═══════════╣\n", indent());
        printf("%s║ %-9s ║ %-20s ║ %-9s ║\n", indent(), "ID", "Name", "Subject");
        printf("%s╠═══════════╬══════════════════════╬═══════════╣\n", indent());

        for (const auto& s : matched)
        {
            printf("%s║ %-9s ║ %-20s ║ %-9s ║\n", indent(),
                   s->id.c_str(),
                   s->name.c_str(),
                   s->subject.c_str());
        }

        printf("%s╚═══════════╩══════════════════════╩═══════════╝\n", indent());
    }
    else
    {
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ No student found with name: %-9s║\n", indent(), searchName.substr(0,10).c_str());
        printf("%s╚════════════════════════════════════╝\n", indent());
    }
}


// Teacher search menu
void searchStudentMenu(StudentList *list, const string &teacherSubject)
{
    while (true)
    {
        cout << endl;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║         SEARCH STUDENT MENU        ║\n", indent());
        printf("%s╠════════════════════════════════════╣\n", indent());
        printf("%s║ 1. Search by ID                    ║\n", indent());
        printf("%s║ 2. Search by Name                  ║\n", indent());
        printf("%s║ 3. Back to Main Menu               ║\n", indent());
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
            break;
        }
        else
        {
            printf("%sInvalid choice! Please enter 1-3\n", indent());
        }
    }
}

#endif // SEARCH_STUDENT_H