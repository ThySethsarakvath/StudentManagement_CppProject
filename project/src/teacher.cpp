
#include <iostream>
#include <regex>
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
        cout << indent() << "║           " << COLOR_BLUE << "Teacher Panel (" << subject << ")" << COLOR_MAGENTA << "                 ║\n";
        cout << indent() << "╠══════════════════════════════════════════════╣\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "1. Add new Student" << COLOR_MAGENTA << "                           ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "2. Edit Students Details" << COLOR_MAGENTA << "                     ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "3. Display All Students" << COLOR_MAGENTA << "                      ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "4. Search Students" << COLOR_MAGENTA << "                           ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "5. Mark Attendences" << COLOR_MAGENTA << "                          ║\n";
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

            string id, password, name, gender, major, ageStr;
            int age;
            clearTerminal();
            cout << COLOR_MAGENTA;
            cout << indent() << "========== Adding New Student ==========\n";
            cout << indent() << "Enter Student ID: ";
            cin >> id;
            cout << indent() << "Enter Password: ";
            cin >> password;
            cout << indent() << "Enter Name: ";
            cin >> name;
            cout << indent() << "Enter Gender (M/F): ";
            cin >> gender;
            while (!isValidGender(gender))
            {
                cout << indent() << "Invalid gender. Please enter M or F: ";
                cin >> gender;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Age input with validation
            while (true)
            {
                cout << indent() << "Enter Age: ";
                getline(cin, ageStr);

                // Validate full string is numeric
                if (regex_match(ageStr, regex("^[0-9]+$")))
                {
                    age = stoi(ageStr);
                    if (isValidAge(age))
                    {
                        break;
                    }
                    else
                    {
                        cout << indent() << "Invalid age. Enter a number between 10 and 100.\n";
                    }
                }
                else
                {
                    cout << indent() << "Invalid input. Please enter a numeric value only.\n";
                }
            }
            cout << indent() << "Enter Major: ";
            cin >> major;
            cout << COLOR_RESET;
            clearTerminal();
            addStudent(list, id, password, name, gender, age, major, subject);
            break;
        }
        case 2:
        {
            clearTerminal();
            string idToEdit;
            cout << COLOR_MAGENTA;
            cout << indent() << "========== Edit Student Details ==========\n";
            cout << indent() << "Enter Student ID to edit: ";
            cin >> idToEdit;
            cout << COLOR_RESET;
            clearTerminal();
            editStudent(list, idToEdit, subject);
            break;
        }

        case 3:
            clearTerminal();
            showViewMenu(list, subject);
            break;

        case 4:
            clearTerminal();
            searchStudentMenu(list, subject);
            break;

        case 5:
            clearTerminal();
            markAttendance(list, subject);
            break;

        case 6:
            clearTerminal();
            addGrade(list, subject);
            break;

        case 7:
        {
            clearTerminal();
            string idToDelete;
            cout << COLOR_MAGENTA;
            cout << indent() << "========== Delete Student ==========\n";
            cout << indent() << "Enter Student ID to delete: ";
            cin >> idToDelete;
            cout << COLOR_RESET;
            deleteStudent(list, idToDelete);
            break;
        }

        case 8:
            clearTerminal();
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
