#ifndef EDIT_STUDENT_H
#define EDIT_STUDENT_H

#include "ui.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void editStudent(StudentList *list, const string &id, const string &teacherSubject)
{
    if (list->n == 0)
    {
        clearTerminal();
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║        No students to edit         ║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());

        return;
    }

    Student *current = list->head;
    while (current != nullptr)
    {
        if (current->id == id && current->subject == teacherSubject)
        {
            clearTerminal();
            cout << COLOR_MAGENTA;
            printf("%s╔══════════════════════════════════════════════╗\n", indent());
            printf("%s║ %sEDITING STUDENT (%-10s) %-15s%s ║\n", indent(), COLOR_BLUE, id.c_str(), teacherSubject.c_str(), COLOR_MAGENTA);
            printf("%s╠══════════════════════════════════════════════╣\n", indent());
            printf("%s║ %s1. Name    : %-31s%s ║\n", indent(), COLOR_GREEN, current->name.c_str(), COLOR_MAGENTA);
            printf("%s║ %s2. Gender  : %-31s%s ║\n", indent(), COLOR_GREEN, current->gender.c_str(), COLOR_MAGENTA);
            printf("%s║ %s3. Age     : %-31d%s ║\n", indent(), COLOR_GREEN, current->age, COLOR_MAGENTA);
            printf("%s║ %s4. Major   : %-31s%s ║\n", indent(), COLOR_GREEN, current->major.c_str(), COLOR_MAGENTA);
            printf("%s║ %s5. Password: %-31s%s ║\n", indent(), COLOR_GREEN, current->password.c_str(), COLOR_MAGENTA);
            printf("%s╚══════════════════════════════════════════════╝\n", indent());
            cout << COLOR_RESET;

            int choice = getMenuChoice(1, 5);

            string newValue;
            printf("%sEnter new value: ", indent());
            getline(cin, newValue);

            switch (choice)
            {
            case 1:
                current->name = newValue;
                break;
            case 2:
                current->gender = newValue;
                break;
            case 3:
                try
                {
                    current->age = stoi(newValue);
                }
                catch (...)
                {
                    printf("%sInvalid age! Keeping old value.\n", indent());
                }
                break;
            case 4:
                current->major = newValue;
                break;
            case 5:
                current->password = newValue;
                break;
            default:
                printf("%sInvalid choice!\n", indent());
                return;
            }

            cout << COLOR_MAGENTA;
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %s    Student updated successfully!  %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
            printf("%s╚════════════════════════════════════╝\n", indent());
            cout << COLOR_RESET;

            return;
        }
        current = current->next;
    }

    cout << COLOR_MAGENTA;
printf("%s╔════════════════════════════════════╗\n", indent());
printf("%s║ %sStudent not found or not in your   %s║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
printf("%s║ %ssubject (%s)                     %s║\n", indent(), COLOR_BRIGHT_YELLOW, teacherSubject.c_str(), COLOR_MAGENTA);
printf("%s╚════════════════════════════════════╝\n", indent());
cout << COLOR_RESET;

}

#endif // EDIT_STUDENT_H