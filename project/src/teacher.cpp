
#include <iostream>
#include "../include/searchStudent.h"
#include "../include/student.h"
#include "../include/addStudent.h"
#include "../include/displayStudent.h"
#include "../include/deleteStudent.h"
#include "../include/editStudent.h"
#include "../include/displayStudentsBySubject.h"
#include "../include/addGrade.h"
#include "../include/markAttendance.h"
#include "../include/studentViews.h"
#include "../include/isValid.h"
#include "../include/indent.h"

using namespace std;



void teacherMain(StudentList *list, string teacherID, string subject)
{
    while (true)
    {
        cout << indent() << "╔══════════════════════════════════════════════╗\n";
        cout << indent() << "║           Teacher Panel (" << subject << ")               ║\n";
        cout << indent() << "╠══════════════════════════════════════════════╣\n";
        cout << indent() << "║ 1. Add new Student                           ║\n";
        cout << indent() << "║ 2. Edit Student Details                      ║\n";
        cout << indent() << "║ 3. Display all Students                      ║\n";
        cout << indent() << "║ 4. Search Student                            ║\n";
        cout << indent() << "║ 5. Mark Attendance                           ║\n";
        cout << indent() << "║ 6. Add Grade                                 ║\n";
        cout << indent() << "║ 7. Delete Students                           ║\n";
        cout << indent() << "║ 8. Logout                                    ║\n";
        cout << indent() << "╚══════════════════════════════════════════════╝\n";
        int choice = getMenuChoice(1, 8);

        switch (choice)
        {
        case 1:
        {

            // Call addStudent()
            string id, password, name, gender, major;
            int age;
            cout << indent() << "Feature: Add Student\n";
            cout << indent() << "Enter Student ID: ";
            cin >> id;
            cout << indent() << "Enter Password: ";
            cin >> password;
            cout << indent() << "Enter Name: ";
            cin >> name;
            cout << indent() << "Enter Gender: ";
            cin >> gender;
            cout << indent() << "Enter Age: ";
            cin >> age;
            cout << indent() << "Enter Major: ";
            cin >> major;
            addStudent(list, id, password, name, gender, age, major, subject);
            break;
        }
        case 2:
        {
            string idToEdit;
            cout << indent() << "Enter Student ID to edit: ";
            cin >> idToEdit;
            editStudent(list, idToEdit, subject);
            break;
        }

        case 3:
            showViewMenu(list, subject); // Now it's clean and scoped!
            break;

        case 4:
            // Call searchStudetn()
            cout << indent() << "Feature: Search Student\n";
            searchStudentMenu(list, subject);
            break;

        case 5:
            // Call markAttendance()
            cout << indent() << "Feature: Mark Attendance\n";
            markAttendance(list, subject);
            break;

        case 6:
            // Call addGrade()
            cout << indent() << "Feature: Add Grade\n";
            addGrade(list, subject);
            break;

        case 7:
        {
            // Call deleteStudent()
            cout << indent() << "Feature: Delete Student\n";
            string idToDelete;
            cout << indent() << "Enter Student ID to delete: ";
            cin >> idToDelete;
            deleteStudent(list, idToDelete);
            break;
        }

        case 8:
            cout << indent() << "Logging out...\n";
            return;

        default:
            cout << indent() << "Invalid choice.\n";
        }
    }
}
