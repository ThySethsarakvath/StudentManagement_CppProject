#include <iostream>
#include "../include/student.h"
#include "../include/teacher.h"
#include "../include/studentUI.h"
#include "../include/addStudent.h"
#include "student.cpp"
#include "teacher.cpp"
// #include <limits>

using namespace std;

void loginMenu(StudentList *list, TeacherList *teacherList) {
    int opt;
    string id, password;

    cout<<R"( 
    ██████████████████████████████████████████████
    █─▄▄▄▄█─▄─▄─█▄─██─▄█▄─▄▄▀█▄─▄▄─█▄─▀█▄─▄█─▄─▄─█
    █▄▄▄▄─███─████─██─███─██─██─▄█▀██─█▄▀─████─███
    ▀▄▄▄▄▄▀▀▄▄▄▀▀▀▄▄▄▄▀▀▄▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀
    █████████████████████████████████▀███████████████████████████████████
    █▄─▀█▀─▄██▀▄─██▄─▀█▄─▄██▀▄─██─▄▄▄▄█▄─▄▄─█▄─▀█▀─▄█▄─▄▄─█▄─▀█▄─▄█─▄─▄─█
    ██─█▄█─███─▀─███─█▄▀─███─▀─██─██▄─██─▄█▀██─█▄█─███─▄█▀██─█▄▀─████─███
    ▀▄▄▄▀▄▄▄▀▄▄▀▄▄▀▄▄▄▀▀▄▄▀▄▄▀▄▄▀▄▄▄▄▄▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀▄▄▄▄▄▀▄▄▄▀▀▄▄▀▀▄▄▄▀▀
    ███████████████████████████████████████
    █─▄▄▄▄█▄─█─▄█─▄▄▄▄█─▄─▄─█▄─▄▄─█▄─▀█▀─▄█
    █▄▄▄▄─██▄─▄██▄▄▄▄─███─████─▄█▀██─█▄█─██
    ▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▀▄▄▄▀▀▄▄▄▄▄▀▄▄▄▀▄▄▄▀)"<<endl;

    try{
        while(true){
        cout << "╔════════════════════════════════════╗\n";
        cout << "║            Login Menu              ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║ 1. Login as Teacher                ║\n";
        cout << "║ 2. Login as Student                ║\n";
        cout << "║ 3. Register New Teacher (Admin)    ║\n";
        cout << "║ 4. Exit                            ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "Please select an option: ";
        cin >> opt;


        // if (cin.fail()) {
        //     cin.clear(); // clear the error flag
        //     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
        //     cout << "Invalid input. Please enter a number.\n";
        //     continue;
        // }

        switch(opt) {
            case 1: {
                cout <<"\n========== Teacher Login ==========\n";
                cout <<"Please enter your ID: ";
                cin >> id;
                cout <<"Please enter your password: ";
                cin >> password;

                Teacher* t = teacherList->head;
                bool found = false;
                while (t != nullptr) {
                    if (t->id == id && t->password == password) {
                        found = true;
                        break;
                    }
                    t = t->next;
                }

                if (found) {
                    cout << "\n========== Login Successful ==========\n";
                    cout << "Welcome back, " << t->name << "!\n";
                    cout << "Subject: " << t->subject << "\n";
                    cout << "You can now manage your students.\n";
                    cout << "=======================================\n";
                    teacherMain(list, id, t->subject);
                } else {
                    cout << "Invalid ID or password.\n";
                }

                break;
            }
            case 2: {
                cout <<"\n========== Student Login ==========\n";
                cout <<"Please enter your ID: ";
                cin >> id;
                cout <<"Please enter your password: ";
                cin >> password;

                cout <<"Login successful!\n";

                studentMain(list, id);

                break;
            }
            case 3: {
                cout <<"\n========== Register New Teacher ==========\n";
                cout << "Enter Teacher ID: ";
                cin >> id;
                cout << "Enter Password: ";
                cin >> password;
                cout << "Enter Name: ";
                cin.ignore();
                string name;
                getline(cin, name);
                cout << "Enter Subject: ";
                string subject;
                getline(cin, subject);

                addTeacher(teacherList, id, password, name, subject);
                cout << "Teacher registered successfully!\n";
                cout <<"==========================================\n";
                break;
            }
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                return;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
    }
    catch(const exception& e) {
        cout << "An error occurred: " << e.what() << endl;
        return;
    }
    
}

int main() {
    StudentList *list = createStudentList();
    TeacherList *teacherList = createTeacherList();
    
    loginMenu(list, teacherList);

    return 0;
}
