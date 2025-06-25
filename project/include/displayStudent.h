#ifndef DISPLAY_STUDENT_H
#define DISPLAY_STUDENT_H

#include <iostream>
#include "student.h"

using namespace std;

void displayStudents(StudentList* list) {
    if (list->n == 0 || list->head == nullptr) {
        printf("╔══════════════════════════╗\n");
        printf("║   No students in list.   ║\n");
        printf("╚══════════════════════════╝\n");
        return;
    }

    Student* current = list->head;
    while (current != nullptr) {
        printf("\n╔══════════════════════════════════════════════════════╗\n");
        printf("║ ID     : %-43s ║\n", current->id.c_str());
        printf("║ Name   : %-43s ║\n", current->name.c_str());
        printf("║ Gender : %-43s ║\n", current->gender.c_str());
        printf("║ Age    : %-43d ║\n", current->age);
        printf("║ Major  : %-43s ║\n", current->major.c_str());
        printf("╠══════════════════════════════════════════════════════╣\n");

        // Grades
        Grade* g = current->gradesHead;
        if (g == nullptr) {
            printf("║ Grades    : None                                     ║\n");
        } else {
            printf("║ Grades:                                               ║\n");
            while (g != nullptr) {
                printf("║   %-20s : %-22.2f          ║\n", g->subject.c_str(), g->score);
                g = g->next;
            }
        }

        printf("╠══════════════════════════════════════════════════════╣\n");

        // Attendance
        Attendance* a = current->attendanceHead;
        if (a == nullptr) {
            printf("║ Attendance: None                                     ║\n");
        } else {
            printf("║ Attendance:                                          ║\n");
            while (a != nullptr) {
                printf("║   %-10s - %-30s ║\n", a->date, a->present ? "Present" : "Absent");
                a = a->next;
            }
        }

        printf("╚══════════════════════════════════════════════════════╝\n");
        current = current->next;
    }
}


#endif
