#ifndef DISPLAY_STUDENT_H
#define DISPLAY_STUDENT_H

#include <iostream>
#include "student.h"

using namespace std;

void displayStudents(StudentList* list) {
    if (list->n == 0 || list->head == nullptr) {
        cout << "No students in the list.\n";
        return;
    }

    Student* current = list->head;
    while (current != nullptr) {
        cout << "--------------------------\n";
        cout << "ID: " << current->id << endl;
        cout << "Name: " << current->name << endl;
        cout << "Gender: " << current->gender << endl;
        cout << "Age: " << current->age << endl;
        cout << "Major: " << current->major << endl;

        // Grades
        Grade* g = current->gradesHead;
        if (g == nullptr) {
            cout << "Grades: None\n";
        } else {
            cout << "Grades:\n";
            while (g != nullptr) {
                cout << "  " << g->subject << ": " << g->score << endl;
                g = g->next;
            }
        }

        // Attendance
        Attendance* a = current->attendanceHead;
        if (a == nullptr) {
            cout << "Attendance: None\n";
        } else {
            cout << "Attendance:\n";
            while (a != nullptr) {
                cout << "  " << a->date << " - " << (a->present ? "Present" : "Absent") << endl;
                a = a->next;
            }
        }

        current = current->next;
    }

    cout << "--------------------------\n";
}

#endif
