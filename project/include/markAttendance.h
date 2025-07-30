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
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", ltm);
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
    cout << COLOR_MAGENTA;
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║    %sAttendance for %-13s%s    ║\n", indent(), COLOR_BLUE, teacherSubject.c_str(), COLOR_MAGENTA);
    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ %s1. Use today's date (%s%s%s)%s   ║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_BRIGHT_YELLOW, getCurrentDate().c_str(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s║ %s2. Enter custom date               %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s╚════════════════════════════════════╝\n", indent());

    int choice = getMenuChoice(1, 2);

    if (choice == 1)
    {
        date = getCurrentDate();
    }
    else
    {
        printf("  %sEnter date (DD-MM-YYYY): ", indent());
        cin >> date;

        while(true){
            if(isValidDate(date)){
                break;
            }
            else{
                cout << COLOR_BRIGHT_YELLOW << indent() << "Invalid date format! Please use DD-MM-YYYY." << COLOR_MAGENTA << endl;
                printf("  %sEnter date (DD-MM-YYYY): ", indent());
                cin >> date;
            }
        
        }
    }
    clearTerminal();
    cout << COLOR_MAGENTA;
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║      %sAttendance for %s%s%s     %s║\n", indent(), COLOR_BLUE, date.c_str(), COLOR_MAGENTA);
    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ %s1. Mark individual student         %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s║ %s2. Mark all students               %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
    printf("%s╚════════════════════════════════════╝\n", indent());

    int choices = getMenuChoice(1, 2);

    if (choices == 1)
    {
        string studentId;
        Student *current = nullptr;
        bool foundStudent = false;

        while (!foundStudent)
        {
            printf("%sEnter Student ID: ", indent());
            cin >> studentId;

            current = list->head;
            while (current)
            {
                if (current->id == studentId && current->subject == teacherSubject)
                {
                    foundStudent = true;
                    break; // Exit inner loop once found
                }
                current = current->next;
            }

            if (!foundStudent)
            {
                printf("%s%sStudent ID not found or not enrolled in subject (%s)%s\n",
                       indent(), COLOR_BRIGHT_YELLOW, teacherSubject.c_str(), COLOR_RESET);
            }
        }

        string status;
        while (true)
        {
            printf("%sPresent (P) or Absent (A): ", indent());
            cin >> status;

            if (status == "P" || status == "p" || status == "A" || status == "a")
                break;

            printf("%sInvalid input! Please enter 'P' or 'A'.\n", indent());
        }

        Attendance *newAtt = new Attendance;
        newAtt->date = date;
        newAtt->present = (toupper(status[0]) == 'P');
        newAtt->next = nullptr;

        if (!current->attendanceHead)
        {
            current->attendanceHead = newAtt;
        }
        else
        {
            Attendance *attCurrent = current->attendanceHead;
            while (attCurrent)
            {
                if (attCurrent->date == date)
                {
                    attCurrent->present = (toupper(status[0]) == 'P');
                    delete newAtt;
                    clearTerminal();
                    cout << COLOR_MAGENTA;
                    printf("%s╔════════════════════════════════════╗\n", indent());
                    printf("%s║  %sAttendance updated successfully!  %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
                    printf("%s╚════════════════════════════════════╝\n", indent());
                    return;
                }
                if (!attCurrent->next)
                    break;
                attCurrent = attCurrent->next;
            }
            attCurrent->next = newAtt;
        }

        clearTerminal();
        cout << COLOR_MAGENTA;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ %sAttendance marked successfully!    %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());
        // enter();
    }
    else
    {
        // Bulk marking for all students in subject
        string status;
        while (true)
        {
            printf("%sMark all as Present (P) or Absent (A): ", indent());
            cin >> status;

            if (status == "P" || status == "A" || status == "p" || status == "a")
            {
                break; // Valid input
            }
            else
            {

                printf("%sInvalid input! Please enter 'P' or 'A'.\n", indent());
            }
        }

        Student *current = list->head;
        bool markedAny = false;
        while (current != nullptr)
        {
            if (current->subject == teacherSubject)
            {
                markedAny = true;
                Attendance *newAtt = new Attendance;
                newAtt->date = date;
                newAtt->present = (toupper(status[0]) == 'P');
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
                            attCurrent->present = (toupper(status[0]) == 'P');
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
            cout << COLOR_MAGENTA;
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %sAttendance marked for all students %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
            printf("%s╚════════════════════════════════════╝\n", indent());
        }
        else
        {
            clearTerminal();
            cout << COLOR_MAGENTA;
            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║ %sNo students in your subject        %s║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
            printf("%s╚════════════════════════════════════╝\n", indent());
        }
    }
}

#endif // MARK_ATTENDANCE_H