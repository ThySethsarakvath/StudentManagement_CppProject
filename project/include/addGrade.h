#ifndef ADD_GRADE_H
#define ADD_GRADE_H

#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void addGrade(StudentList* list, const string& teacherSubject) {
    if (list->n == 0) {
        printf("╔════════════════════════════════════╗\n");
        printf("║        No students available       ║\n");
        printf("╚════════════════════════════════════╝\n");
        return;
    }

    string studentId;
    printf("╔════════════════════════════════════╗\n");
    printf("║     Add Grade for %-12s     ║\n", teacherSubject.c_str());
    printf("╠════════════════════════════════════╣\n");
    printf("║ Enter Student ID: ");
    cin >> studentId;

    Student* current = list->head;
    while (current != nullptr) {
        if (current->id == studentId && current->subject == teacherSubject) {
            float score;
            printf("║ Enter Score for %-15s: ", teacherSubject.c_str());
            cin >> score;

            // Create new grade
            Grade* newGrade = new Grade;
            newGrade->subject = teacherSubject;
            newGrade->score = score;
            newGrade->next = nullptr;

            // Add to student's grade list
            if (current->gradesHead == nullptr) {
                current->gradesHead = newGrade;
            } else {
                Grade* gradeCurrent = current->gradesHead;
                while (gradeCurrent->next != nullptr) {
                    if (gradeCurrent->subject == teacherSubject) {
                        printf("╠════════════════════════════════════╣\n");
                        printf("║ Grade already exists! Overwriting. ║\n");
                        gradeCurrent->score = score;
                        delete newGrade;
                        printf("╚════════════════════════════════════╝\n");
                        return;
                    }
                    gradeCurrent = gradeCurrent->next;
                }
                gradeCurrent->next = newGrade;
            }

            printf("╠════════════════════════════════════╣\n");
            printf("║ Grade added successfully!          ║\n");
            printf("╚════════════════════════════════════╝\n");
            return;
        }
        current = current->next;
    }

    printf("╠════════════════════════════════════╣\n");
    printf("║ Student not found or not enrolled  ║\n");
    printf("║ in %-32s ║\n", teacherSubject.c_str());
    printf("╚════════════════════════════════════╝\n");
}

#endif // ADD_GRADE_H