#ifndef EDIT_STUDENT_H
#define EDIT_STUDENT_H

#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void editStudent(StudentList* list, const string& id, const string& teacherSubject) {
    if (list->n == 0) {
        printf("╔════════════════════════════════════╗\n");
        printf("║        No students to edit         ║\n");
        printf("╚════════════════════════════════════╝\n");
        return;
    }

    Student* current = list->head;
    while (current != nullptr) {
        if (current->id == id && current->subject == teacherSubject) {
            printf("\n╔══════════════════════════════════════════════╗\n");
            printf("║ EDITING STUDENT (%-10s) %-15s ║\n", teacherSubject.c_str(), id.c_str());
            printf("╠══════════════════════════════════════════════╣\n");
            printf("║ 1. Name: %-35s ║\n", current->name.c_str());
            printf("║ 2. Gender: %-33s ║\n", current->gender.c_str());
            printf("║ 3. Age: %-36d ║\n", current->age);
            printf("║ 4. Major: %-34s ║\n", current->major.c_str());
            printf("║ 5. Password: %-31s ║\n", current->password.c_str());
            printf("╚══════════════════════════════════════════════╝\n");

            int choice;
            printf("Select field to edit (1-5, 0 to cancel): ");
            cin >> choice;

            if (choice == 0) return;

            cin.ignore(); // Clear input buffer
            string newValue;
            printf("Enter new value: ");
            getline(cin, newValue);

            switch (choice) {
                case 1: current->name = newValue; break;
                case 2: current->gender = newValue; break;
                case 3: 
                    try { current->age = stoi(newValue); } 
                    catch (...) { 
                        printf("Invalid age! Keeping old value.\n"); 
                    }
                    break;
                case 4: current->major = newValue; break;
                case 5: current->password = newValue; break;
                default: printf("Invalid choice!\n"); return;
            }

            printf("╔════════════════════════════════════╗\n");
            printf("║     Student updated successfully!  ║\n");
            printf("╚════════════════════════════════════╝\n");
            return;
        }
        current = current->next;
    }

    printf("╔════════════════════════════════════╗\n");
    printf("║ Student not found or not in your   ║\n");
    printf("║ subject (%s)                     ║\n", teacherSubject.c_str());
    printf("╚════════════════════════════════════╝\n");
}

#endif // EDIT_STUDENT_H