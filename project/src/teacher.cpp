// #include <iostream>
// #include "../include/addStudent.h"
// #include "../include/student.h"
// #include "../include/displayStudent.h"

// using namespace std;

// int main() {
//     StudentList *student = createStudentList();
//     cout << "Welcome to the Student Management System!" << endl;
//     cout << "Please enter the student details:" << endl;
//     string id, password, name, gender, major;
//     int age;
//     cout << "ID: ";
//     cin >> id;
//     cout << "Password: ";
//     cin >> password;
//     cout << "Name: ";
//     cin >> name;
//     cout <<"Gender: ";
//     cin>>gender;
//     cout << "Age: ";
//     cin >> age;
//     cout << "Major: ";
//     cin >> major;
//     addStudent(student, id, password,name,gender, age, major);
//     // cout << "Student added successfully!" << endl;
//     cout << "Displaying all students:" << endl;
//     displayStudents(student);

//     return 0;
// }

#include <iostream>
#include "../include/student.h"
#include "../include/addStudent.h"
#include "../include/displayStudent.h"
#include "../include/deleteStudent.h"
#include "../include/editStudent.h"
#include "../include/displayStudentsBySubject.h"
#include "../include/addGrade.h"
#include "../include/markAttendance.h"
#include "../include/studentViews.h"

using namespace std;

void teacherMain(StudentList *list, string teacherID, string subject)
{
    int choice;
    while (true)
    {
        cout << "\n╔══════════════════════════════════════════════╗\n";
        cout << "║           Teacher Panel (" << subject << ")               ║\n";
        cout << "╠══════════════════════════════════════════════╣\n";
        cout << "║ 1. Add new Student                           ║\n";
        cout << "║ 2. Edit Student Details                      ║\n";
        cout << "║ 3. Display all Students                      ║\n";
        cout << "║ 4. Search Student                            ║\n";
        cout << "║ 5. Mark Attendance                           ║\n";
        cout << "║ 6. Add Grade                                 ║\n";
        cout << "║ 7. Delete Students                           ║\n";
        cout << "║ 8. Logout                                    ║\n";
        cout << "╚══════════════════════════════════════════════╝\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {

            // Call addStudent()
            string id, password, name, gender, major;
            int age;
            cout << "Feature: Add Student\n";
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Password: ";
            cin >> password;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Gender: ";
            cin >> gender;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Major: ";
            cin >> major;
            addStudent(list, id, password, name, gender, age, major, subject);
            break;
        }
        case 2:
        {
            string idToEdit;
            cout << "Enter Student ID to edit: ";
            cin >> idToEdit;
            editStudent(list, idToEdit, subject);
            break;
        }

        case 3:
        {
            int viewChoice;
            do
            {
                printf("╔════════════════════════════════════╗\n");
                printf("║            Select View             ║\n");
                printf("╠════════════════════════════════════╣\n");
                printf("║ 1. Student Overview                ║\n");
                printf("║ 2. Grade View                      ║\n");
                printf("║ 3. Attendance View                 ║\n");
                printf("║ 4. Back to Main Menu               ║\n");
                printf("╚════════════════════════════════════╝\n");
                printf("Choice: ");

                cin >> viewChoice;

                switch (viewChoice)
                {
                case 1:
                    displayStudentOverview(list, subject);
                    break;
                case 2:
                    displayGradeView(list, subject);
                    break;
                case 3:
                    displayAttendanceView(list, subject);
                    break;
                case 4:
                    cout << "Returning to Main Menu...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (viewChoice != 4); // Keep looping until user chooses to go back
            break;
        }

        case 4:
            // Call searchStudetn()
            cout << "Feature: Search Student\n";
            break;

        case 5:
            // Call markAttendance()
            cout << "Feature: Mark Attendance\n";
            markAttendance(list, subject);
            break;

        case 6:
            // Call addGrade()
            cout << "Feature: Add Grade\n";
            addGrade(list, subject);
            break;

        case 7:
        {
            // Call deleteStudent()
            cout << "Feature: Delete Student\n";
            string idToDelete;
            cout << "Enter Student ID to delete: ";
            cin >> idToDelete;
            deleteStudent(list, idToDelete);
            break;
        }

        case 8:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}
