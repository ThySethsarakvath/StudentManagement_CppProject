
#include <iostream>
#include "../include/searchStudent.h"
#include "../include/student.h"
#include "../include/addStudent.h"
#include "../include/deleteStudent.h"
#include "../include/editStudent.h"
#include "../include/addGrade.h"
#include "../include/markAttendance.h"
#include "../include/studentViews.h"
#include "../include/ui.h"

using namespace std;

void teacherMain(StudentList *list, string teacherID, string subject)
{
    while (true)
    {
        cout << COLOR_MAGENTA;
        cout << indent() << "╔══════════════════════════════════════════════╗\n";
        cout << indent() << "║           " << COLOR_BLUE << "Teacher Panel (" << subject << ")" << COLOR_MAGENTA << "               ║\n";
        cout << indent() << "╠══════════════════════════════════════════════╣\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "1. Add new Student" << COLOR_MAGENTA << "                           ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "2. Edit Students Details" << COLOR_MAGENTA << "                      ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "3. Display All Students" << COLOR_MAGENTA << "                      ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "4. Search Students" << COLOR_MAGENTA << "                            ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "5. Mark Attendences" << COLOR_MAGENTA << "                           ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "6. Add Grade" << COLOR_MAGENTA << "                                 ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "7. Delete Students" << COLOR_MAGENTA << "                           ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_YELLOW << "8. Logout" << COLOR_MAGENTA << "                                    ║\n";
        cout << indent() << "╚══════════════════════════════════════════════╝\n";
        cout << COLOR_RESET;
        int choice = getMenuChoice(1, 8);

        switch (choice)
        {
        case 1:
        {

            // Call addStudent()
            string id, password, name, gender, major;
            int age;
            cout << COLOR_MAGENTA;
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
            cout << COLOR_RESET;
            addStudent(list, id, password, name, gender, age, major, subject);
            break;
        }
        case 2:
        {
            string idToEdit;
            cout << COLOR_MAGENTA;
            cout << indent() << "Enter Student ID to edit: ";
            cin >> idToEdit;
            cout << COLOR_RESET;
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
            cout << COLOR_MAGENTA;
            cout << indent() << "Enter Student ID to delete: ";
            cin >> idToDelete;
            cout << COLOR_RESET;
            deleteStudent(list, idToDelete);
            break;
        }

        case 8:
            cout << COLOR_BRIGHT_YELLOW;
            cout << indent() << "Logging out...\n";
            cout << COLOR_RESET;
            return;

        default:
            cout << COLOR_BRIGHT_RED;
            cout << indent() << "Invalid choice.\n";
            cout << COLOR_RESET;
        }
    }
}
