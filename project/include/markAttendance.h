#ifndef MARK_ATTENDANCE_H
#define MARK_ATTENDANCE_H

#include "ui.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Helper function to get current date
string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

void markAttendance(StudentList *list, const string &teacherSubject)
{
    if (list->n == 0)
    {
        clearTerminal();
        cout << COLOR_MAGENTA;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ %sNo students available%s       ║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());
        cout << COLOR_RESET;

        return;
    }

    clearTerminal();
    string date;
    int markingOption;
    cout << COLOR_MAGENTA;
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║    %sAttendance for %-13s%s    ║\n", indent(), COLOR_BLUE, teacherSubject.c_str(), COLOR_MAGENTA);
    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ %s1. Use today's date (%s%s%s)%s   ║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_BRIGHT_YELLOW, getCurrentDate().c_str(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s║ %s2. Enter custom date               %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s╚════════════════════════════════════╝\n", indent());
    printf("%s Choose option: ", indent());

    cin >> markingOption;

    if (markingOption == 1)
    {
        date = getCurrentDate();
    }
    else
    {
        printf("║ %sEnter date (YYYY-MM-DD): ", indent());
        cin >> date;
    }
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║    %sAttendance for %-13s%s    ║\n", indent(), COLOR_BLUE, teacherSubject.c_str(), COLOR_MAGENTA);
    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ %s1. Mark individual student         %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s║ %s2. Mark all students               %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s╚════════════════════════════════════╝\n", indent());
    printf("%s Choose marking mode: ", indent());

    cin >> markingOption;

    if (markingOption == 1)
    {
        // Individual student marking
        string studentId;
        char status;
        printf("%s Enter Student ID: ", indent());
        cin >> studentId;
        printf("%s Present (P) or Absent (A): ", indent());
        cin >> status;

        Student *current = list->head;
        while (current != nullptr)
        {
            if (current->id == studentId && current->subject == teacherSubject)
            {
                Attendance *newAtt = new Attendance;
                newAtt->date = date;
                newAtt->present = (toupper(status) == 'P');
                newAtt->next = nullptr;

                if (current->attendanceHead == nullptr)
                {
                    current->attendanceHead = newAtt;
                }
                else
                {
                    // Check if attendance already exists for this date
                    Attendance *attCurrent = current->attendanceHead;
                    while (attCurrent->next != nullptr)
                    {
                        if (attCurrent->date == date)
                        {
                            attCurrent->present = (toupper(status) == 'P');
                            delete newAtt;
                            clearTerminal();
                            printf("%s╔════════════════════════════════════╗\n", indent());
                            printf("%s║ %sAttendance updated successfully!  %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
                            printf("%s╚════════════════════════════════════╝\n", indent());
                            return;
                        }
                        attCurrent = attCurrent->next;
                    }
                    attCurrent->next = newAtt;
                }

                clearTerminal();
                printf("%s╔════════════════════════════════════╗\n", indent());
                printf("%s║ %sAttendance marked successfully!    %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
                printf("%s╚════════════════════════════════════╝\n", indent());
                return;
            }
            current = current->next;
        }
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ %sStudent not found or not in your   %s║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
        printf("%s║ %ssubject (%s)                     %s║\n", indent(), COLOR_BRIGHT_YELLOW, teacherSubject.c_str(), COLOR_MAGENTA);
    }
    else
    {
        // Bulk marking for all students in subject
        char status;
        printf("%s Mark all as Present (P) or Absent (A): ", indent());
        cin >> status;

        Student *current = list->head;
        bool markedAny = false;
        while (current != nullptr)
        {
            if (current->subject == teacherSubject)
            {
                markedAny = true;
                Attendance *newAtt = new Attendance;
                newAtt->date = date;
                newAtt->present = (toupper(status) == 'P');
                newAtt->next = nullptr;

                if (current->attendanceHead == nullptr)
                {
                    current->attendanceHead = newAtt;
                }
                else
                {
                    Attendance *attCurrent = current->attendanceHead;
                    while (attCurrent->next != nullptr)
                    {
                        if (attCurrent->date == date)
                        {
                            attCurrent->present = (toupper(status) == 'P');
                            delete newAtt;
                            break;
                        }
                        attCurrent = attCurrent->next;
                    }
                    if (attCurrent->next == nullptr)
                    {
                        attCurrent->next = newAtt;
                    }
                }
            }
            current = current->next;
        }

        if (markedAny)
        {
            clearTerminal();
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %sAttendance marked for all students %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        }
        else
        {
            clearTerminal();
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %sNo students in your subject        %s║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
        }
    }
    printf("%s╚════════════════════════════════════╝\n", indent());
}

#endif // MARK_ATTENDANCE_H