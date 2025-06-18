#include <iostream>
#include "../include/student.h"
#include "../include/teacher.h"
#include "../include/studentUI.h"
#include "../include/addStudent.h"
#include <limits>

using namespace std;

void loginMenu(StudentList *list){
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
        cout<<"\n========== Login Menu ==========\n";
        cout<<"1. Login as Teacher\n";
        cout<<"2. Login as Student\n";
        cout<<"3. Register New Teacher (Admin)\n";
        cout<<"4. Exit\n";
        cout<<"=================================\n";
        cout<<"Please select an option: ";
        cin>>opt;

        // if (cin.fail()) {
        //     cin.clear(); // clear the error flag
        //     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard the invalid input
        //     cout << "Invalid input. Please enter a number.\n";
        //     continue;
        // }

        

        switch(opt){
            case 1:
                cout<<"\n========== Teacher Login ==========\n";
                cout<<"Please enter your ID: ";
                cin>>id;
                cout<<"Please enter your password: ";
                cin>>password;

                // teacherMainMenu(id, password, list);
                break;
            case 2:
                cout<<"\n========== Student Login ==========\n";
                cout<<"Please enter your ID: ";
                cin>>id;
                cout<<"Please enter your password: ";
                cin>>password;

                cout<<"Login successful!\n";

                // studentMainMenu(id, password, list);
                break;
            case 3:
                cout<<"\n========== Register New Teacher ==========\n";
                break;
            case 4:
                cout<<"Exiting the system. Goodbye!\n";
                return;
            default:
                cout<<"Invalid option. Please try again.\n";
        }
    }
    }
    catch(const exception& e){
        cout << "An error occurred: " << e.what() << endl;
        return;
    }
    
}

int main(){
    StudentList *list = createStudentList();
    cout << "Welcome to the Student Management System!" << endl;

    // Add some sample students
    addStudent(list, "S001", "pass123", "Alice", "Female", 20, "Computer Science");

    loginMenu(list);

    return 0;
}
