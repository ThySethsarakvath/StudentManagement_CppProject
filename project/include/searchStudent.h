#ifndef SEARCH_STUDENT_H
#define SEARCH_STUDENT_H

#include "indent.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <cctype> // for tolower()

using namespace std;

// Search by ID (exact match)
void searchByID(StudentList* list, const string& teacherSubject) {
    string searchID;
    cout<< indent() << "Enter Student ID: ";
    getline(cin, searchID);

    Student* current = list->head;
    bool found = false;

    while (current) {
        if (current->subject == teacherSubject && current->id == searchID) {
            found = true;
            printf("\n╔════════════════════════════════════╗\n", indent());
            printf("║           STUDENT FOUND           ║\n", indent());
            printf("╠════════════════════════════════════╣\n", indent());
            printf("║ ID:      %-25s ║\n", current->id.c_str(), indent());
            printf("║ Name:    %-25s ║\n", current->name.c_str(), indent());
            printf("║ Subject: %-25s ║\n", current->subject.c_str(), indent());
            printf("╚════════════════════════════════════╝\n", indent());
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("\n╔════════════════════════════════════╗\n", indent());
        printf("║ No student found with ID: %-8s ║\n", searchID.c_str(), indent());
        printf("╚════════════════════════════════════╝\n", indent());
    }
}

// Case-insensitive string comparison
bool matches(const string& a, const string& b) {
    if (a.length() != b.length()) return false;
    for (size_t i = 0; i < a.length(); i++) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    return true;
}

// Search by name (partial match)
void searchByName(StudentList* list, const string& teacherSubject) {
    string searchName;
    cout<<indent() << "Enter Student Name: ";
    getline(cin, searchName);

    Student* current = list->head;
    int count = 0;

    printf("\n╔══════════════════════════════════════════════╗\n", indent());
    printf("║           SEARCH RESULTS                    ║\n", indent());
    printf("╠═══════════╦══════════════════════╦═══════════╣\n", indent());
    printf("║ %-9s ║ %-20s ║ %-9s ║\n", "ID", "Name", "Subject", indent());
    printf("╠═══════════╬══════════════════════╬═══════════╣\n", indent());

    while (current) {
        if (current->subject == teacherSubject) {
            // Case-insensitive partial match
            bool nameMatches = false;
            string currNameLower = current->name;
            string searchLower = searchName;
            // Convert both to lowercase
            for (char &c : currNameLower) c = tolower(c);
            for (char &c : searchLower) c = tolower(c);
            
            if (currNameLower.find(searchLower) != string::npos) {
                printf("║ %-9s ║ %-20s ║ %-9s ║\n, indent()", 
                      current->id.c_str(),
                      current->name.c_str(),
                      current->subject.c_str());
                count++;
            }
        }
        current = current->next;
    }

    if (count == 0) {
        printf("║ %-42s ║\n", "No matching students found", indent());
    }
    printf("╚═══════════╩══════════════════════╩═══════════╝\n", indent());
}

// Teacher search menu
void searchStudentMenu(StudentList* list, const string& teacherSubject) {
    while (true) {
        printf("\n╔════════════════════════════════════╗\n", indent());
        printf("║        SEARCH STUDENT MENU        ║\n", indent());
        printf("╠════════════════════════════════════╣\n", indent());
        printf("║ 1. Search by ID                   ║\n", indent());
        printf("║ 2. Search by Name                 ║\n", indent());
        printf("║ 3. Back to Main Menu              ║\n", indent());
        printf("╚════════════════════════════════════╝\n", indent());
        printf("Choose option (1-3): ");

        string input;
        getline(cin, input);
        
        if (input == "1") {
            searchByID(list, teacherSubject);
        } 
        else if (input == "2") {
            searchByName(list, teacherSubject);
        }
        else if (input == "3") {
            break;
        }
        else {
            printf("Invalid choice! Please enter 1-3\n", indent());
        }
    }
}

#endif // SEARCH_STUDENT_H