#include "../include/student.h"
#include "../include/ui.h"
#include "../include/studentViews.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>

using namespace std;

void studentMain(StudentList *list, const string &studentId)
{
    Student *current = list->head;
    while (current != nullptr && current->id != studentId)
    {
        current = current->next;
    }

    if (!current)
    {
        cout << COLOR_BRIGHT_RED;
        cout << indent() << "Student not found.\n";
        cout << COLOR_RESET;
        return;
    }

    clearTerminal();
    cout<<COLOR_BRIGHT_GREEN;
    cout<<indent()<<"Studnet Logged in successfully!"<<endl;
    cout<<COLOR_RESET;
    while (true)
    {
        cout << COLOR_MAGENTA;
        cout << indent() << "╔══════════════════════════════════════════════╗\n";
        cout << indent() << "║" << COLOR_BLUE << centerText(" STUDENT DASHBOARD: " + current->name, 46) << COLOR_MAGENTA << "║\n";
        cout << indent() << "╠══════════════════════════════════════════════╣\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "1. View Profile" << COLOR_MAGENTA << "                              ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "2. View Grade" << COLOR_MAGENTA << "                                ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "3. View Attendance Records" << COLOR_MAGENTA << "                   ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "4. View Overall Performance" << COLOR_MAGENTA << "                  ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_GREEN << "5. Change Password" << COLOR_MAGENTA << "                           ║\n";
        cout << indent() << "║ " << COLOR_BRIGHT_YELLOW << "6. Logout" << COLOR_MAGENTA << "                                    ║\n";
        cout << indent() << "╚══════════════════════════════════════════════╝\n";
        cout << COLOR_RESET;

        int choice = getMenuChoice(1, 6);

        switch (choice)
        {
        case 1:
        { // View Profile
            clearTerminal();
            cout << COLOR_MAGENTA;
            printf("%s╔═════════════════════════════════════════════╗\n", indent());
            printf("%s║ %s%-44s%s║\n", indent(), COLOR_BLUE, centerText("STUDENT PROFILE", 44).c_str(), COLOR_MAGENTA);
            printf("%s╠══════════════════════╦══════════════════════╣\n", indent());
            printf("%s║ %s%-20s%s ║ %-20s ║\n", indent(), COLOR_GREEN, "ID:", COLOR_MAGENTA, current->id.c_str());
            printf("%s║ %s%-20s%s ║ %-20s ║\n", indent(), COLOR_GREEN, "Name:", COLOR_MAGENTA, current->name.c_str());
            printf("%s║ %s%-20s%s ║ %-20s ║\n", indent(), COLOR_GREEN, "Gender:", COLOR_MAGENTA, current->gender.c_str());
            printf("%s║ %s%-20s%s ║ %-20d ║\n", indent(), COLOR_GREEN, "Age:", COLOR_MAGENTA, current->age);
            printf("%s║ %s%-20s%s ║ %-20s ║\n", indent(), COLOR_GREEN, "Major:", COLOR_MAGENTA, current->major.c_str());
            printf("%s║ %s%-20s%s ║ %-20s ║\n", indent(), COLOR_GREEN, "Enrolled Subject:", COLOR_MAGENTA, current->subject.c_str());
            printf("%s╚══════════════════════╩══════════════════════╝\n", indent());
            cout << COLOR_RESET;
            break;
        }
        case 2:
        { // View Grades
            showGradePanel(current->gradesHead, current->subject);
            break;
        }
        case 3:
        { // View Attendance
            showAttendancePanel(current->attendanceHead, current->subject);
            break;
        }
        case 4:
        { // Overall Performance
            clearTerminal();
            cout << COLOR_MAGENTA;
            printf("%s╔═════════════════════════════════════════════╗\n", indent());
            printf("%s║ %s%-44s%s║\n", indent(), COLOR_BLUE, centerText("OVERALL PERFORMANCE", 44).c_str(), COLOR_MAGENTA);
            printf("%s╠══════════════════════╦══════════════════════╣\n", indent());

            // Calculate GPA
            float totalPoints = 0;
            int count = 0;
            Grade *grade = current->gradesHead;
            while (grade)
            {
                if (grade->subject == current->subject)
                {
                    totalPoints += grade->score;
                    count++;
                }
                grade = grade->next;
            }
            float gpa = count > 0 ? totalPoints / count : 0;

            // Calculate attendance
            int totalAtt = 0, presentAtt = 0;
            Attendance *att = current->attendanceHead;
            while (att)
            {
                totalAtt++;
                if (att->present)
                    presentAtt++;
                att = att->next;
            }
            float attRate = totalAtt > 0 ? (presentAtt * 100.0f) / totalAtt : 0.0f;

            // Subjects count
            int subjectCount = 0;
            grade = current->gradesHead;
            string lastSubject = "";
            while (grade)
            {
                if (grade->subject != lastSubject)
                {
                    subjectCount++;
                    lastSubject = grade->subject;
                }
                grade = grade->next;
            }

            printf("%s║ %s%-20s%s ║ %-20.2f ║\n", indent(),COLOR_BRIGHT_GREEN, "GPA:", COLOR_MAGENTA, gpa);
            printf("%s║ %s%-20s%s ║ %-20.1f%%║\n", indent(),COLOR_BRIGHT_GREEN, "Attendance Rate:", COLOR_MAGENTA, attRate);
            printf("%s║ %s%-20s%s ║ %-20d ║\n", indent(),COLOR_BRIGHT_GREEN, "Subjects Taken:", COLOR_MAGENTA, subjectCount);
            printf("%s╚══════════════════════╩══════════════════════╝\n", indent());
            cout << COLOR_RESET;
            break;
        }
        case 5:
        { // Change Password
            clearTerminal();
            string oldPass, newPass;
            cout << COLOR_BRIGHT_YELLOW;
            cout << indent() << "Enter current password: ";
            cin >> oldPass;
            if (oldPass != current->password)
            {
                cout << COLOR_BRIGHT_RED;
                cout << indent() << "Incorrect password!\n";
                cout << COLOR_BRIGHT_YELLOW;
                break;
            }
            cout << indent() << "Enter new password: ";
            cin >> newPass;
            current->password = newPass;
            clearTerminal();
            cout << COLOR_BRIGHT_GREEN;
            cout << indent() << "Password changed successfully!\n";
            cout << COLOR_RESET;
            break;
        }
        case 6: // Logout
            clearTerminal();
            cout << COLOR_BRIGHT_YELLOW;
            cout << indent() << "Logging out...\n";
            cout << COLOR_RESET;
            return;
        default:
            cout << COLOR_BRIGHT_RED;
            cout << indent() << "Invalid choice!\n";
            cout << COLOR_RESET;
        }
    }
}