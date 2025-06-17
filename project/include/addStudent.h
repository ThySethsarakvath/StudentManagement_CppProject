#ifndef ADD_STUDENT_H
#define ADD_STUDENT_H
#include "student.h"
#include <iostream>
#include <string>

using namespace std;

void addStudent(StudentList* list, const string& id, const string& password, const string& name, const string& gender, int age, const string& major){
    Student *newStudent = new Student;

    cout << "Enter student ID: ";
    cin >> newStudent->id;
    cout << "Enter password: ";
    cin >> newStudent->password;
    cout << "Enter name: ";
    cin >> newStudent->name;
    cout <<"Enter Gender: ";
    cin>> newStudent->gender;
    cout << "Enter age: ";
    cin >> newStudent->age;
    cout << "Enter major: ";
    cin >> newStudent->major;

    newStudent->gratesHead = nullptr;
    newStudent->attendanceHead = nullptr;
    newStudent->next = nullptr;

    if(list->n == 0){
        list->head = newStudent;
        list->tail = newStudent;
    }
    else{
        list->tail->next = newStudent;
        list->tail = newStudent;
    }

    list->n++;
    cout << "Student added successfully!" << endl;
}

#endif // ADD_STUDENT_H