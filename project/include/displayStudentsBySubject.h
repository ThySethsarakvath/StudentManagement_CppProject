#ifndef DISPLAY_STUDENTS_BY_SUBJECT_H
#define DISPLAY_STUDENTS_BY_SUBJECT_H

#include "student.h"
#include <iostream>
#include <cstdio>

using namespace std;

void displayStudentsBySubject(StudentList *list, const string &subject)
{
    if (list->n == 0 || list->head == nullptr)
    {
        printf("╔════════════════════════════════════╗\n");
        printf("║ No students in %-21s ║\n", subject.c_str());
        printf("╚════════════════════════════════════╝\n");
        return;
    }

    Student *current = list->head;
    bool found = false;

    while (current != nullptr)
    {
        if (current->subject == subject)
        {
            found = true;
            printf("\n╔══════════════════════════════════════════════════════╗\n");
            printf("║ ID     : %-43s ║\n", current->id.c_str());
            printf("║ Name   : %-43s ║\n", current->name.c_str());
            printf("║ Gender : %-43s ║\n", current->gender.c_str());
            printf("║ Age    : %-43d ║\n", current->age);
            printf("║ Major  : %-43s ║\n", current->major.c_str());
            printf("╠══════════════════════════════════════════════════════╣\n");

            // Grades
            Grade *g = current->gradesHead;
            if (g == nullptr)
            {
                printf("║ Grades    : None                                     ║\n");
            }
            else
            {
                printf("║ Grades:                                              ║\n");
                while (g != nullptr)
                {
                    printf("║   %-20s : %-18.2f          ║\n", g->subject.c_str(), g->score);
                    g = g->next;
                }
            }

            printf("╠══════════════════════════════════════════════════════╣\n");

            // Attendance
            Attendance *a = current->attendanceHead;
            if (a == nullptr)
            {
                printf("║ Attendance: None                                     ║\n");
            }
            else
            {
                printf("║ Attendance:                                          ║\n");
                while (a != nullptr)
                {
                    printf("║   %-10s - %-30s ║\n", a->date, a->present ? "Present" : "Absent");
                    a = a->next;
                }
            }

            printf("╚══════════════════════════════════════════════════════╝\n");
        }
        current = current->next;
    }

    if (!found)
    {
        printf("╔════════════════════════════════════╗\n");
        printf("║ No students in %-18s ║\n", subject.c_str());
        printf("╚════════════════════════════════════╝\n");
    }
}

#endif