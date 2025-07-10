#ifndef TEACHERACC_H
#define TEACHERACC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "teacher.h"
using namespace std;

bool isDuplicateTeacherId(TeacherList* list, const string& id) {
    Teacher* cur = list->head;
    while (cur != nullptr) {
        if (cur->id == id) return true;
        cur = cur->next;
    }
    return false;
}

void loadTeachersFromCSV(TeacherList* list, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, pw, name, subject;
        getline(ss, id, ',');
        getline(ss, pw, ',');
        getline(ss, name, ',');
        getline(ss, subject, ',');

        addTeacher(list, id, pw, name, subject);
    }

    file.close();
}

void saveTeachersToCSV(TeacherList* list, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return;

    Teacher* cur = list->head;
    while (cur != nullptr) {
        file << cur->id << "," << cur->password << "," << cur->name << "," << cur->subject << "\n";
        cur = cur->next;
    }

    file.close();
}

#endif
