#ifndef DELETE_STUDENT_H
#define DELETE_STUDENT_H

#include "ui.h"
#include "student.h"
#include <iostream>

using namespace std;
void deleteStudent(StudentList* list, const string& id) {
    if (list->n == 0) {
        clearTerminal();
        cout<<COLOR_MAGENTA;
        printf("%s╔════════════════════════════════════╗\n",indent());
        printf("%s║        No students available       ║\n", indent(), COLOR_BRIGHT_YELLOW, COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());
        return;
    }

    Student* current = list->head;
    Student* previous = nullptr;

    while (current != nullptr) {
        if (current->id == id) {
            if (previous == nullptr) {
                // Deleting the head
                list->head = current->next;
            } else {
                // Deleting a middle or tail node
                previous->next = current->next;
            }

            if (current == list->tail) {
                // If we deleted the tail, update it
                list->tail = previous;
            }

            delete current;
            list->n--;
            cout<<COLOR_BRIGHT_GREEN;
            cout<<indent() << "Student with ID " << id << " deleted successfully." << endl;
            return;
        }
        previous = current;
        current = current->next;
    }

    clearTerminal();
    cout<<COLOR_BRIGHT_RED;
    cout<<indent() << "Student with ID " << id << " not found." << endl;
    cout<<COLOR_RESET;
}

#endif