#ifndef ADD_GRADE_H
#define ADD_GRADE_H

#include "indent.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void addGrade(StudentList* list, const string& teacherSubject) {
    if (list->n == 0) {
        printf("%s╔════════════════════════════════════╗\n",indent());
        printf("%s║        No students available       ║\n", indent());
        printf("%s╚════════════════════════════════════╝\n", indent());
        return;
    }

    string studentId;
    printf("%s╔════════════════════════════════════╗\n", indent());
    printf("%s║     Add Grade for %-12s     ║\n", teacherSubject.c_str(), indent());
    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ Enter Student ID: ", indent());
    cin >> studentId;

    Student* current = list->head;
    while (current != nullptr) {
        if (current->id == studentId && current->subject == teacherSubject) {
            float score;
            printf("%s║ Enter Score for %-15s: ", teacherSubject.c_str(), indent());
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
                        printf("%s╠════════════════════════════════════╣\n", indent());
                        printf("%s║ Grade already exists! Overwriting. ║\n", indent());
                        gradeCurrent->score = score;
                        delete newGrade;
                        printf("%s╚════════════════════════════════════╝\n", indent());
                        return;
                    }
                    gradeCurrent = gradeCurrent->next;
                }
                gradeCurrent->next = newGrade;
            }

            printf("%s╠════════════════════════════════════╣\n",indent());
            printf("%s║ Grade added successfully!          ║\n", indent());
            printf("%s╚════════════════════════════════════╝\n", indent());
            return;
        }
        current = current->next;
    }

    printf("%s╠════════════════════════════════════╣\n", indent());
    printf("%s║ Student not found or not enrolled  ║\n", indent());
    printf("%s║ in %-32s ║\n", teacherSubject.c_str(), indent());
    printf("%s╚════════════════════════════════════╝\n", indent());
}

#endif // ADD_GRADE_H