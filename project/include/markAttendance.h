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
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║        No students available       ║\n", indent());
        printf("%s╚════════════════════════════════════╝\n", indent());

        return;
    }

    string date;
    int markingOption;
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║    Attendance for %-13s    ║\n", indent(), teacherSubject.c_str());
    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ 1. Use today's date (%s)   ║\n", indent(), getCurrentDate().c_str());
    printf("%s║ 2. Enter custom date               ║\n", indent());
    printf("%s╚════════════════════════════════════╝\n", indent());
    printf("%s║ Choose option: ", indent());

    cin >> markingOption;

    if (markingOption == 1)
    {
        date = getCurrentDate();
    }
    else
    {
        printf("║ Enter date (YYYY-MM-DD): ", indent());
        cin >> date;
    }

    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ 1. Mark individual student         ║\n", indent());
    printf("%s║ 2. Mark all students               ║\n", indent());
    printf("%s╚════════════════════════════════════╣\n", indent());
    printf("%s║ Choose marking mode: ", indent());
    cin >> markingOption;

    if (markingOption == 1)
    {
        // Individual student marking
        string studentId;
        char status;
        printf("%s║ Enter Student ID: ", indent());
        cin >> studentId;
        printf("%s║ Present (P) or Absent (A): ", indent());
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
                            printf("%s╠════════════════════════════════════╣\n", indent());
                            printf("%s║ Attendance updated successfully!  ║\n", indent());
                            printf("%s╚════════════════════════════════════╝\n", indent());
                            return;
                        }
                        attCurrent = attCurrent->next;
                    }
                    attCurrent->next = newAtt;
                }

                printf("%s╠════════════════════════════════════╣\n", indent());
                printf("%s║ Attendance marked successfully!    ║\n", indent());
                printf("%s╚════════════════════════════════════╝\n", indent());
                return;
            }
            current = current->next;
        }
        printf("%s╠════════════════════════════════════╣\n", indent());
        printf("%s║ Student not found or not enrolled  ║\n", indent());
        printf("%s║ in %-30s ║\n", teacherSubject.c_str(), indent());
    }
    else
    {
        // Bulk marking for all students in subject
        char status;
        printf("%s║ Mark all as Present (P) or Absent (A): ", indent());
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
            printf("%s╠════════════════════════════════════╣\n", indent());
            printf("%s║ Attendance marked for all students ║\n", indent());
        }
        else
        {
            printf("%s╠════════════════════════════════════╣\n", indent());
            printf("%s║ No students in your subject        ║\n", indent());
        }
    }
    printf("%s╚════════════════════════════════════╝\n", indent());
}

#endif // MARK_ATTENDANCE_H