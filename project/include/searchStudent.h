#ifndef SEARCH_STUDENT_H
#define SEARCH_STUDENT_H

#include <iostream>
#include <string>
#include <algorithm>  // for transform
#include "student.h"
using namespace std;

// Helper to convert string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

Student* searchStudentByID(StudentList* list, const string& id) {
    Student* cur = list->head;
    while (cur != nullptr) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void searchStudentByName(StudentList* list, const string& name) {
    string lowerName = toLower(name);
    Student* cur = list->head;
    bool found = false;
    while (cur != nullptr) {
        string lowerStudentName = toLower(cur->name);
        if (lowerStudentName.find(lowerName) != string::npos) {
            cout << "Found: " << cur->name << " | ID: " << cur->id << " | Subject: " << cur->subject << "\n";
            found = true;
        }
        cur = cur->next;
    }
    if (!found) cout << "No student found with name containing: " << name << endl;
}

void searchStudentBySubject(StudentList* list, const string& subject) {
    Student* cur = list->head;
    bool found = false;
    while (cur != nullptr) {
        if (cur->subject == subject) {
            cout << "Student: " << cur->name << " | ID: " << cur->id << " | Subject: " << cur->subject << "\n";
            found = true;
        }
        cur = cur->next;
    }
    if (!found) cout << "No student found in subject: " << subject << endl;
}

#endif
