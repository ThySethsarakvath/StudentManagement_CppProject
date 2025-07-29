#include <iostream>
#include <windows.h>
#include "../include/fileIO.h"
#include "../include/student.h"
#include "../include/teacher.h"
#include "../include/studentUI.h"
#include "../include/addStudent.h"
#include "../include/teacherAcc.h"
#include "../include/isValid.h"
#include "../include/indent.h"
#include "student.cpp"
#include "teacher.cpp"

// #include <limits>

using namespace std;

void loginMenu(StudentList *list, TeacherList *teacherList)
{
    string id, password;

    cout<<"\n\n";
    cout<< indent1() << "    ███████████████████████████████████████████████████████████████████████████████▀██████████████████████████████████████████████████████████████████████████" << endl;
    cout<< indent1() << "    █─▄▄▄▄█─▄─▄─█▄─██─▄█▄─▄▄▀█▄─▄▄─█▄─▀█▄─▄█─▄─▄─██▄─▀█▀─▄██▀▄─██▄─▀█▄─▄██▀▄─██─▄▄▄▄█▄─▄▄─█▄─▀█▀─▄█▄─▄▄─█▄─▀█▄─▄█─▄─▄─██─▄▄▄▄█▄─█─▄█─▄▄▄▄█─▄─▄─█▄─▄▄─█▄─▀█▀─▄█" << endl;
    cout<< indent1() << "    █▄▄▄▄─███─████─██─███─██─██─▄█▀██─█▄▀─████─█████─█▄█─███─▀─███─█▄▀─███─▀─██─██▄─██─▄█▀██─█▄█─███─▄█▀██─█▄▀─████─████▄▄▄▄─██▄─▄██▄▄▄▄─███─████─▄█▀██─█▄█─██" << endl;
    cout<< indent1() << "    ▀▄▄▄▄▄▀▀▄▄▄▀▀▀▄▄▄▄▀▀▄▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀▀▄▄▄▀▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀" << endl;


    cout<<"\n\n";
    try
    {
        while (true)
        {
            cout << indent() << "╔════════════════════════════════════╗\n";
            cout << indent() << "║            Login Menu              ║\n";
            cout << indent() << "╠════════════════════════════════════╣\n";
            cout << indent() << "║ 1. Login as Teacher                ║\n";
            cout << indent() << "║ 2. Login as Student                ║\n";
            cout << indent() << "║ 3. Register New Teacher (Admin)    ║\n";
            cout << indent() << "║ 4. Exit                            ║\n";
            cout << indent() << "╚════════════════════════════════════╝\n";
            int choice = getMenuChoice(1, 4);

            switch (choice)
            {
            case 1:
            {
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
                    cout << indent() << "========== Login Successful ==========\n";
                    cout << indent() << "Welcome back, " << t->name << "!\n";
                    cout << indent() << "Subject: " << t->subject << "\n";
                    cout << indent() << "You can now manage your students.\n";
                    cout << indent() << "=======================================\n";
                    teacherMain(list, id, t->subject);
                }
                else
                {
                    cout << indent() << "Invalid ID or password.\n";
                }

                break;
            }
            case 2:
            {
                cout << indent() << "========== Student Login ==========\n";
                cout << indent() << "Please enter your ID: ";
                cin >> id;
                cout << indent() << "Please enter your password: ";
                cin >> password;

                cout << indent() << "Login successful!\n";

                studentMain(list, id);

                break;
            }
            case 3:
            {
                cout << indent() << "========== Register New Teacher ==========\n";
                cout << indent() << "Enter Teacher ID: ";
                cin >> id;
                if (isDuplicateTeacherId(teacherList, id))
                {
                    cout << indent() << " ID already exists. Please use a different ID.\n";
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
                break;
            }
            case 4:
                cout << indent() << "Exiting the system. Goodbye!\n";
                return;
            default:
                cout << indent() << "Invalid option. Please try again.\n";
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
