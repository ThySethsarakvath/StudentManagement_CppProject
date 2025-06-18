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

using namespace std;

void teacherMain(StudentList* list, string teacherID, string subject) {
    int choice;
    while (true) {
        cout << "\n╔══════════════════════════════════════════════╗\n";
        cout << "║          Teacher Panel (" << subject << ")               ║\n";
        cout << "╠══════════════════════════════════════════════╣\n";
        cout << "║ 1. Add new Student                           ║\n";
        cout << "║ 2. Edit Student Details                      ║\n";
        cout << "║ 3. Display all Students                      ║\n";
        cout << "║ 4. Search Student                            ║\n";
        cout << "║ 5. Mark Attendance                           ║\n";
        cout << "║ 6. Add Grade                                 ║\n";
        cout << "║ 7. Logout                                    ║\n";
        cout << "╚══════════════════════════════════════════════╝\n";
        cout << "Choose: ";
        cin >> choice;


        switch (choice) {
            case 1:
                // Call addStudent()
                cout << "Feature: Add Student\n";
                break;

            case 2:
                // Call editStudents()
                cout << "Feature: Edit Students\n";
                break;

            case 3:
                // Call displayStudent()
                cout << "Feature: Display Student\n";
                break;

            case 4:
                // Call searchStudetn()
                cout << "Feature: Search Student\n";
                break;

            case 5:
                // Call markAttendance()
                cout << "Feature: Mark Attendance\n";
                break;

            case 6:
                // Call addGrade()
                cout << "Feature: Add Grade\n";
                break;

            case 7:
                cout << "Logging out...\n";
                return;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
