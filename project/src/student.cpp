#include <iostream>
#include "../include/student.h"

using namespace std;

void studentMain(StudentList* list, string studentID) {
    Student* current = list->head;
    while (current != nullptr) {
        if (current->id == studentID) {
            break;
        }
        current = current->next;
    }

    if (!current) {
        cout << "Student not found.\n";
        return;
    }

    cout << "\n===== Welcome, " << current->name << " =====\n";
    cout << "Major: " << current->major << "\n";
    cout << "Age: " << current->age << "\n";

    cout << "\nGrades:\n";
    Grade* g = current->gradesHead;
    while (g) {
        cout << g->subject << ": " << g->score << endl;
        g = g->next;
    }

    cout << "\nAttendance:\n";
    Attendance* a = current->attendanceHead;
    while (a) {
        cout << a->date << ": " << (a->present ? "Present" : "Absent") << endl;
        a = a->next;
    }

    cout << endl;
}
