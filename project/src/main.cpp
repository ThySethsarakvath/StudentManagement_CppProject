#include <iostream>
#include <windows.h>
#include "../include/fileIO.h"
#include "../include/student.h"
#include "../include/teacher.h"
#include "../include/addStudent.h"
#include "../include/teacherAcc.h"
#include "../include/ui.h"
#include "student.cpp"
#include "teacher.cpp"

// #include <limits>

using namespace std;

void loginMenu(StudentList *list, TeacherList *teacherList)
{
    string id, password;

    clearTerminal();
    cout << "\n\n";
    cout << COLOR_CYAN;
    cout << indent1() << "    ███████████████████████████████████████████████████████████████████████████████▀██████████████████████████████████████████████████████████████████████████" << endl;
    cout << indent1() << "    █─▄▄▄▄█─▄─▄─█▄─██─▄█▄─▄▄▀█▄─▄▄─█▄─▀█▄─▄█─▄─▄─██▄─▀█▀─▄██▀▄─██▄─▀█▄─▄██▀▄─██─▄▄▄▄█▄─▄▄─█▄─▀█▀─▄█▄─▄▄─█▄─▀█▄─▄█─▄─▄─██─▄▄▄▄█▄─█─▄█─▄▄▄▄█─▄─▄─█▄─▄▄─█▄─▀█▀─▄█" << endl;
    cout << indent1() << "    █▄▄▄▄─███─████─██─███─██─██─▄█▀██─█▄▀─████─█████─█▄█─███─▀─███─█▄▀─███─▀─██─██▄─██─▄█▀██─█▄█─███─▄█▀██─█▄▀─████─████▄▄▄▄─██▄─▄██▄▄▄▄─███─████─▄█▀██─█▄█─██" << endl;
    cout << indent1() << "    ▀▄▄▄▄▄▀▀▄▄▄▀▀▀▄▄▄▄▀▀▄▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀▀▄▄▄▀▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀" << endl;
    cout << COLOR_RESET;

    cout << "\n\n";
    try
    {
        while (true)
        {
            cout << COLOR_MAGENTA;
            cout << indent() << "╔════════════════════════════════════╗\n";
            cout << indent() << "║            " << COLOR_BLUE << "Login Menu" << COLOR_MAGENTA << "              ║\n";
            cout << indent() << "╠════════════════════════════════════╣\n";
            cout << indent() << "║ " << COLOR_GREEN << "1. Login as Teacher" << COLOR_MAGENTA << "                ║\n";
            cout << indent() << "║ " << COLOR_GREEN << "2. Login as Student" << COLOR_MAGENTA << "                ║\n";
            cout << indent() << "║ " << COLOR_GREEN << "3. Register New Teacher (Admin)" << COLOR_MAGENTA << "    ║\n";
            cout << indent() << "║ " << COLOR_BRIGHT_RED << "4. Exit" << COLOR_MAGENTA << "                            ║\n";
            cout << indent() << "╚════════════════════════════════════╝\n";
            cout << COLOR_RESET;
            int choice = getMenuChoice(1, 4);

            switch (choice)
            {
            case 1:
            {
                cout << COLOR_MAGENTA;
                cout << indent() << "========== Teacher Login ==========\n";
                cout << indent() << "Please enter your ID: ";
                cin >> id;
                cout << indent() << "Please enter your password: ";
                cin >> password;

                Teacher *t = teacherList->head;
                bool found = false;
                while (t != nullptr)
                {
                    if (t->id == id && t->password == password)
                    {
                        found = true;
                        break;
                    }
                    t = t->next;
                }

                if (found)
                {
                    clearTerminal();
                    cout << COLOR_BRIGHT_GREEN;
                    cout << indent() << "    ========== Login Successful ==========\n";
                    cout << indent() << "        Welcome back, " << t->name << "!\n";
                    cout << indent() << "         Subject: " << t->subject << "\n";
                    cout << indent() << "       You can now manage your students.\n";
                    cout << indent() << "    =======================================\n";
                    cout << COLOR_RESET;
                    teacherMain(list, id, t->subject);
                }
                else
                {
                    cout << COLOR_BRIGHT_RED;
                    cout << indent() << "Invalid ID or password.\n";
                    cout << COLOR_RESET;
                }

                break;
            }
            case 2:
            {
                cout << COLOR_MAGENTA;
                cout << indent() << "========== Student Login ==========\n";
                cout << indent() << "Please enter your ID: ";
                cin >> id;
                cout << indent() << "Please enter your password: ";
                cin >> password;
                cout << COLOR_RESET;
                studentMain(list, id);

                break;
            }
            case 3:
            {
                clearTerminal();
                cout << COLOR_MAGENTA;
                cout << indent() << "========== Register New Teacher ==========\n";
                cout << indent() << "Enter Teacher ID: ";
                cin >> id;
                if (isDuplicateTeacherId(teacherList, id))
                {
                    cout << COLOR_BRIGHT_YELLOW;
                    cout << indent() << " ID already exists. Please use a different ID.\n";
                    cout << COLOR_MAGENTA;
                    break;
                }

                cout << indent() << "Enter Password: ";
                cin >> password;
                cout << indent() << "Enter Name: ";
                cin.ignore();
                string name;
                getline(cin, name);
                cout << indent() << "Enter Subject: ";
                string subject;
                getline(cin, subject);

                addTeacher(teacherList, id, password, name, subject);
                saveTeachersToCSV(teacherList, "../Data/teacherAcc.csv");
                cout << indent() << "Teacher registered successfully!\n";

                cout << indent() << "==========================================\n";
                cout << COLOR_RESET;
                break;
            }
            case 4:
                clearTerminal();
                cout << indent() << "Exiting the system. Goodbye!\n";
                return;
            default:
                cout << COLOR_BRIGHT_RED;
                cout << indent() << "Invalid option. Please try again.\n";
                cout << COLOR_RESET;
            }
        }
    }
    catch (const exception &e)
    {
        cout << indent() << "An error occurred: " << e.what() << endl;
        return;
    }
}

int main()
{

    SetConsoleOutputCP(CP_UTF8);
    StudentList *list = createStudentList();
    TeacherList *teacherList = createTeacherList();

    loadAllData(list);
    loadTeachersFromCSV(teacherList, "../Data/teacherAcc.csv");
    // addTeacher(teacherList, "T001", "pass111", "vath", "math");
    // addStudent(list, "S001", "pass123", "Alice", "M", 20, "Computer Science","math");
    loginMenu(list, teacherList);
    saveTeachersToCSV(teacherList, "../Data/teacherAcc.csv");

    saveAllData(list);

    return 0;
}
