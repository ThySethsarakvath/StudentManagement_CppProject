#ifndef MARK_ATTENDANCE_H
#define MARK_ATTENDANCE_H

#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Helper function to get current date
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

void markAttendance(StudentList* list, const string& teacherSubject) {
    if (list->n == 0) {
        printf("╔════════════════════════════════════╗\n");
        printf("║        No students available       ║\n");
        printf("╚════════════════════════════════════╝\n");
        return;
    }

    string date;
    int markingOption;
    printf("╔════════════════════════════════════╗\n");
    printf("║    Attendance for %-13s    ║\n", teacherSubject.c_str());
    printf("╠════════════════════════════════════╣\n");
    printf("║ 1. Use today's date (%s)   ║\n", getCurrentDate().c_str());
    printf("║ 2. Enter custom date               ║\n");
    printf("╚════════════════════════════════════╣\n");
    printf("║ Choose option: ");
    cin >> markingOption;

    if (markingOption == 1) {
        date = getCurrentDate();
    } else {
        printf("║ Enter date (YYYY-MM-DD): ");
        cin >> date;
    }

    printf("╠════════════════════════════════════╣\n");
    printf("║ 1. Mark individual student         ║\n");
    printf("║ 2. Mark all students               ║\n");
    printf("╚════════════════════════════════════╣\n");
    printf("║ Choose marking mode: ");
    cin >> markingOption;

    if (markingOption == 1) {
        // Individual student marking
        string studentId;
        char status;
        printf("║ Enter Student ID: ");
        cin >> studentId;
        printf("║ Present (P) or Absent (A): ");
        cin >> status;

        Student* current = list->head;
        while (current != nullptr) {
            if (current->id == studentId && current->subject == teacherSubject) {
                Attendance* newAtt = new Attendance;
                newAtt->date = date;
                newAtt->present = (toupper(status) == 'P');
                newAtt->next = nullptr;

                if (current->attendanceHead == nullptr) {
                    current->attendanceHead = newAtt;
                } else {
                    // Check if attendance already exists for this date
                    Attendance* attCurrent = current->attendanceHead;
                    while (attCurrent->next != nullptr) {
                        if (attCurrent->date == date) {
                            attCurrent->present = (toupper(status) == 'P');
                            delete newAtt;
                            printf("╠════════════════════════════════════╣\n");
                            printf("║ Attendance updated successfully!  ║\n");
                            printf("╚════════════════════════════════════╝\n");
                            return;
                        }
                        attCurrent = attCurrent->next;
                    }
                    attCurrent->next = newAtt;
                }

                printf("╠════════════════════════════════════╣\n");
                printf("║ Attendance marked successfully!    ║\n");
                printf("╚════════════════════════════════════╝\n");
                return;
            }
            current = current->next;
        }
        printf("╠════════════════════════════════════╣\n");
        printf("║ Student not found or not enrolled  ║\n");
        printf("║ in %-30s ║\n", teacherSubject.c_str());
    } else {
        // Bulk marking for all students in subject
        char status;
        printf("║ Mark all as Present (P) or Absent (A): ");
        cin >> status;

        Student* current = list->head;
        bool markedAny = false;
        while (current != nullptr) {
            if (current->subject == teacherSubject) {
                markedAny = true;
                Attendance* newAtt = new Attendance;
                newAtt->date = date;
                newAtt->present = (toupper(status) == 'P');
                newAtt->next = nullptr;

                if (current->attendanceHead == nullptr) {
                    current->attendanceHead = newAtt;
                } else {
                    Attendance* attCurrent = current->attendanceHead;
                    while (attCurrent->next != nullptr) {
                        if (attCurrent->date == date) {
                            attCurrent->present = (toupper(status) == 'P');
                            delete newAtt;
                            break;
                        }
                        attCurrent = attCurrent->next;
                    }
                    if (attCurrent->next == nullptr) {
                        attCurrent->next = newAtt;
                    }
                }
            }
            current = current->next;
        }

        if (markedAny) {
            printf("╠════════════════════════════════════╣\n");
            printf("║ Attendance marked for all students ║\n");
        } else {
            printf("╠════════════════════════════════════╣\n");
            printf("║ No students in your subject        ║\n");
        }
    }
    printf("╚════════════════════════════════════╝\n");
}

#endif // MARK_ATTENDANCE_H