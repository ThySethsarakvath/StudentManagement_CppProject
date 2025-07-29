#ifndef EDIT_STUDENT_H
#define EDIT_STUDENT_H

#include "indent.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

void editStudent(StudentList *list, const string &id, const string &teacherSubject)
{
    if (list->n == 0)
    {
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║        No students to edit         ║\n", indent());
        printf("%s╚════════════════════════════════════╝\n", indent());

        return;
    }

    Student *current = list->head;
    while (current != nullptr)
    {
        if (current->id == id && current->subject == teacherSubject)
        {
            printf("%s╔══════════════════════════════════════════════╗\n", indent());
            printf("%s║ EDITING STUDENT (%-10s) %-15s ║\n", indent(), teacherSubject.c_str(), id.c_str());
            printf("%s╠══════════════════════════════════════════════╣\n", indent());
            printf("%s║ 1. Name: %-35s ║\n", indent(), current->name.c_str());
            printf("%s║ 2. Gender: %-33s ║\n", indent(), current->gender.c_str());
            printf("%s║ 3. Age: %-36d ║\n", indent(), current->age);
            printf("%s║ 4. Major: %-34s ║\n", indent(), current->major.c_str());
            printf("%s║ 5. Password: %-31s ║\n", indent(), current->password.c_str());
            printf("%s╚══════════════════════════════════════════════╝\n", indent());

            int choice;
            printf("%sSelect field to edit (1-5, 0 to cancel): ", indent());
            cin >> choice;

            if (choice == 0)
                return;

            cin.ignore(); // Clear input buffer
            string newValue;
            printf("%sEnter new value: ", indent());
            getline(cin, newValue);

            switch (choice)
            {
            case 1:
                current->name = newValue;
                break;
            case 2:
                current->gender = newValue;
                break;
            case 3:
                try
                {
                    current->age = stoi(newValue);
                }
                catch (...)
                {
                    printf("%sInvalid age! Keeping old value.\n", indent());
                }
                break;
            case 4:
                current->major = newValue;
                break;
            case 5:
                current->password = newValue;
                break;
            default:
                printf("%sInvalid choice!\n", indent());
                return;
            }

            printf("%s╔════════════════════════════════════╗\n", indent());
            printf("%s║     Student updated successfully!  ║\n", indent());
            printf("%s╚════════════════════════════════════╝\n", indent());

            return;
        }
        current = current->next;
    }

    printf("╔════════════════════════════════════╗\n",indent());
    printf("║ Student not found or not in your   ║\n", indent());
    printf("║ subject (%s)                     ║\n", teacherSubject.c_str(), indent());
    printf("╚════════════════════════════════════╝\n", indent());
}

#endif // EDIT_STUDENT_H