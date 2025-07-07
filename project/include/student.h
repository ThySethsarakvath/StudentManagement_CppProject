#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>


using namespace std;

struct Grade {
    string subject;
    float score;
    Grade *next;
};

struct Attendance {
    string date;
    bool present;
    Attendance *next;
};

struct Student {
    string id;
    string password;
    string name;
    string gender;
    int age;
    string major;
    string subject;
    Grade *gradesHead;
    Attendance *attendanceHead;
    Student *next;
};

struct StudentList {
    int n;
    Student *tail;
    Student *head;
};

StudentList *createStudentList() {
    StudentList *list = new StudentList;
    list -> n = 0;
    list -> tail = nullptr;
    list -> head = nullptr;
    return list;
}

#endif // STUDENT_H

