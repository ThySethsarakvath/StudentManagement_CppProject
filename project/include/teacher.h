#ifndef TEACHER_H
#define TEACHER_H

#include <string>
using namespace std;

struct Teacher {
    string id;
    string password;
    string name;
    string subject;
    Teacher* next;
};

struct TeacherList {
    int n;
    Teacher* head;
    Teacher* tail;
};

TeacherList* createTeacherList() {
    TeacherList* list = new TeacherList;
    list -> n = 0;
    list -> head = nullptr;
    list -> tail = nullptr;
    return list;
}

void addTeacher(TeacherList* list, string id, string pw, string name, string subject) {
    Teacher* t = new Teacher;
    t -> id = id;
    t -> password = pw;
    t -> name = name;
    t -> subject = subject;
    t -> next = nullptr;

    if (list -> n == 0) {
        list -> head = t;
    } else {
        list -> tail -> next = t;
    }
    list -> tail = t;
    list -> n++;
}

#endif
