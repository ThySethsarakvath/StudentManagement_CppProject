#ifndef ADD_STUDENT_H
#define ADD_STUDENT_H
#include "indent.h"
#include "student.h"
#include <iostream>
#include <string>

using namespace std;

void addStudent(StudentList* list, const string& id, const string& password, const string& name, const string& gender, int age, const string& major, const string& subject) {
    Student *newStudent = new Student;

    newStudent -> id = id;
    newStudent -> password = password;
    newStudent -> name = name;
    newStudent -> gender = gender;
    newStudent -> age = age;
    newStudent -> major = major;
    newStudent -> subject = subject;

    newStudent -> gradesHead = nullptr;
    newStudent -> attendanceHead = nullptr;
    newStudent -> next = nullptr;

    if(list -> n == 0){
        list -> head = newStudent;
        list -> tail = newStudent;
    }
    else{
        list -> tail -> next = newStudent;
        list -> tail = newStudent;
    }

    list -> n++;
    cout<<indent() << "Student added successfully!" << endl;
}

#endif