#ifndef ADD_GRADE_H
#define ADD_GRADE_H

#include "ui.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void addGrade(StudentList *list, const string &teacherSubject)
{
    cout << COLOR_MAGENTA;
    if (list->n == 0)
    {
        clearTerminal();
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║        No students available       ║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());
        return;
    }
    cout << COLOR_MAGENTA;

    string studentId;

    clearTerminal();
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║     Add Grade for %-12s     ║\n", indent(), teacherSubject.c_str());
    printf("%s╚════════════════════════════════════╝\n", indent());
    printf("%s%s Enter Student ID: %s", COLOR_MAGENTA, indent(), COLOR_BRIGHT_GREEN);
    cin >> studentId;

    Student *current = list->head;
    while (current != nullptr)
    {
        if (current->id == studentId && current->subject == teacherSubject)
        {
            float score;

            printf("%s%s Enter Score for %s:", COLOR_MAGENTA, indent(), teacherSubject.c_str(), COLOR_BRIGHT_GREEN);
            cin >> score;
            cout<<COLOR_MAGENTA;

            Grade *newGrade = new Grade{teacherSubject, score, nullptr};

            Grade *gradeCurrent = current->gradesHead;
            if (!gradeCurrent)
            {
                current->gradesHead = newGrade;
            }
            else
            {
                while (gradeCurrent != nullptr)
                {
                    if (gradeCurrent->subject == teacherSubject)
                    {
                        clearTerminal();
                        cout<<COLOR_MAGENTA;
                        printf("%s╔════════════════════════════════════╗\n", indent());
                        printf("%s%s║ Grade already exists! Overwriting. ║\n", indent(), COLOR_BRIGHT_YELLOW,COLOR_MAGENTA);
                        gradeCurrent->score = score;
                        delete newGrade;
                        printf("%s╚════════════════════════════════════╝\n", indent());
                        return;
                    }
                    if (!gradeCurrent->next)
                        break;
                    gradeCurrent = gradeCurrent->next;
                }
                gradeCurrent->next = newGrade;
            }
            clearTerminal();
            cout<<COLOR_MAGENTA;
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║   %s  Grade added successfully!      %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
            printf("%s╚════════════════════════════════════╝\n", indent());
            return;
        }
        current = current->next;
    }

    // Student not found message
    clearTerminal();
    cout<<COLOR_MAGENTA;
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║ %sStudent not found or not enrolled  %s║\n", indent(), COLOR_BRIGHT_YELLOW,COLOR_MAGENTA);
    printf("%s║ %sin %-32s%s║\n", indent(), COLOR_BRIGHT_YELLOW, teacherSubject.c_str(),COLOR_MAGENTA);
    printf("%s╚════════════════════════════════════╝\n", indent());

    cout << COLOR_RESET;
}

#endif // ADD_GRADE_H