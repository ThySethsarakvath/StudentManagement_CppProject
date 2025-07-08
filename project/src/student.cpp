#include "../include/student.h"
#include "../include/helpers.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Display student dashboard
void studentMain(StudentList *list, const string &studentId)
{
    Student *current = list->head;
    while (current != nullptr && current->id != studentId)
    {
        current = current->next;
    }

    if (!current)
    {
        cout << "Student not found.\n";
        return;
    }

    // Organize grades by subject
    map<string, vector<float>> gradesBySubject;
    Grade *grade = current->gradesHead;
    while (grade)
    {
        gradesBySubject[grade->subject].push_back(grade->score);
        grade = grade->next;
    }

    // Organize attendance by subject
    map<string, vector<pair<string, bool>>> attendanceBySubject;
    Attendance *att = current->attendanceHead;
    while (att)
    {
        attendanceBySubject[current->subject].emplace_back(att->date, att->present);
        att = att->next;
    }

    int choice;
    while (true)
    {
        cout << "\n╔══════════════════════════════════════════════╗\n";
        cout << "║" << centerText("STUDENT DASHBOARD: " + current->name, 46) << "║\n";
        cout << "╠══════════════════════════════════════════════╣\n";
        cout << "║ 1. View Profile                              ║\n";
        cout << "║ 2. View Grades by Subject                    ║\n";
        cout << "║ 3. View Attendance Records                   ║\n";
        cout << "║ 4. View Overall Performance                  ║\n";
        cout << "║ 5. Change Password                           ║\n";
        cout << "║ 6. Logout                                    ║\n";
        cout << "╚══════════════════════════════════════════════╝\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        { // View Profile
            printf("\n╔═════════════════════════════════════════════╗\n");
            printf("║ %s ║\n", centerText("STUDENT PROFILE", 44).c_str());
            printf("╠══════════════════════╦══════════════════════╣\n");
            printf("║ %-20s ║ %-20s ║\n", "ID:", current->id.c_str());
            printf("║ %-20s ║ %-20s ║\n", "Name:", current->name.c_str());
            printf("║ %-20s ║ %-20s ║\n", "Gender:", current->gender.c_str());
            printf("║ %-20s ║ %-20d ║\n", "Age:", current->age);
            printf("║ %-20s ║ %-20s ║\n", "Major:", current->major.c_str());
            printf("║ %-20s ║ %-20s ║\n", "Enrolled Subject:", current->subject.c_str());
            printf("╚══════════════════════╩══════════════════════╝\n");
            break;
        }
        case 2:
        { // View Grades by Subject
            printf("\n╔═════════════════════════════════════════════╗\n");
            printf("║ %s║\n", centerText("GRADE REPORT", 44).c_str());
            printf("╠══════════════════════╦══════════════════════╣\n");
            printf("║ %-20s ║ %-20s║\n", "SUBJECT", "GRADES (Latest First)");
            printf("╠══════════════════════╬══════════════════════╣\n");

            for (const auto &subj : gradesBySubject)
            {
                string gradesStr;
                for (int i = subj.second.size() - 1; i >= 0; --i)
                {
                    gradesStr += to_string(subj.second[i]) + " ";
                }
                printf("║ %-20s ║ %-20s ║\n",
                       subj.first.c_str(),
                       gradesStr.empty() ? "N/A" : gradesStr.c_str());
            }
            printf("╚══════════════════════╩══════════════════════╝\n");
            break;
        }
        case 3:
        { // View Attendance
            printf("\n╔══════════════════════════════════════════════╗\n");
            printf("║ %s ║\n", centerText("ATTENDANCE RECORDS", 44).c_str());
            printf("╠══════════════════════╦══════════╦════════════╣\n");
            printf("║ %-20s ║ %-8s ║ %-10s ║\n", "DATE", "STATUS", "SUBJECT");
            printf("╠══════════════════════╬══════════╬════════════╣\n");

            Attendance *att = current->attendanceHead;
            while (att)
            {
                printf("║ %-20s ║ %-8s ║ %-10s ║\n",
                       att->date.c_str(),
                       att->present ? "Present" : "Absent",
                       current->subject.c_str());
                att = att->next;
            }
            printf("╚══════════════════════╩══════════╩════════════╝\n");

            // Calculate attendance rate
            int total = 0, present = 0;
            att = current->attendanceHead;
            while (att)
            {
                total++;
                if (att->present)
                    present++;
                att = att->next;
            }
            if (total > 0)
            {
                printf("\nAttendance Rate: %.1f%% (%d/%d)\n",
                       (present * 100.0) / total, present, total);
            }
            break;
        }
        case 4:
        { // Overall Performance
            printf("\n╔═════════════════════════════════════════════╗\n");
            printf("║ %s ║\n", centerText("OVERALL PERFORMANCE", 44).c_str());
            printf("╠══════════════════════╦══════════════════════╣\n");

            // GPA Calculation
            float totalPoints = 0;
            int count = 0;
            for (const auto &subj : gradesBySubject)
            {
                if (!subj.second.empty())
                {
                    totalPoints += subj.second.back(); // Use latest grade
                    count++;
                }
            }
            float gpa = count > 0 ? totalPoints / count : 0;

            // Attendance Calculation
            int totalAtt = 0, presentAtt = 0;
            Attendance *att = current->attendanceHead;
            while (att)
            {
                totalAtt++;
                if (att->present)
                    presentAtt++;
                att = att->next;
            }
            float attRate = totalAtt > 0 ? (presentAtt * 100.0) / totalAtt : 0;

            printf("║ %-20s ║ %-20.2f ║\n", "GPA:", gpa);
            printf("║ %-20s ║ %-20.1f%%║\n", "Attendance Rate:", attRate);
            printf("║ %-20s ║ %-20d ║\n", "Subjects Taken:", (int)gradesBySubject.size());
            printf("╚══════════════════════╩══════════════════════╝\n");
            break;
        }
        case 5:
        { // Change Password
            string oldPass, newPass;
            cout << "Enter current password: ";
            cin >> oldPass;
            if (oldPass != current->password)
            {
                cout << "Incorrect password!\n";
                break;
            }
            cout << "Enter new password: ";
            cin >> newPass;
            current->password = newPass;
            cout << "Password changed successfully!\n";
            break;
        }
        case 6: // Logout
            cout << "Logging out...\n";
            return;
        default:
            cout << "Invalid choice!\n";
        }
    }
}