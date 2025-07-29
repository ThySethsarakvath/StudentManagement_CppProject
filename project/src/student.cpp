#include "../include/student.h"
#include "../include/helpers.h"
#include "../include/isValid.h"
#include "../include/indent.h"
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
        cout << indent() << "Student not found.\n";
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

    while (true)
    {
        cout << indent() << "╔══════════════════════════════════════════════╗\n";
        cout << indent() << "║" << centerText("STUDENT DASHBOARD: " + current->name, 46) << "║\n";
        cout << indent() << "╠══════════════════════════════════════════════╣\n";
        cout << indent() << "║ 1. View Profile                              ║\n";
        cout << indent() << "║ 2. View Grades by Subject                    ║\n";
        cout << indent() << "║ 3. View Attendance Records                   ║\n";
        cout << indent() << "║ 4. View Overall Performance                  ║\n";
        cout << indent() << "║ 5. Change Password                           ║\n";
        cout << indent() << "║ 6. Logout                                    ║\n";
        cout << indent() << "╚══════════════════════════════════════════════╝\n";
        int choice = getMenuChoice(1, 6);

        switch (choice)
        {
        case 1:
        { // View Profile
            printf("%s╔═════════════════════════════════════════════╗\n", indent());
            printf("%s║ %s ║\n", indent(), centerText("STUDENT PROFILE", 44).c_str());
            printf("%s╠══════════════════════╦══════════════════════╣\n", indent());
            printf("%s║ %-20s ║ %-20s ║\n", indent(), "ID:", current->id.c_str());
            printf("%s║ %-20s ║ %-20s ║\n", indent(), "Name:", current->name.c_str());
            printf("%s║ %-20s ║ %-20s ║\n", indent(), "Gender:", current->gender.c_str());
            printf("%s║ %-20s ║ %-20d ║\n", indent(), "Age:", current->age);
            printf("%s║ %-20s ║ %-20s ║\n", indent(), "Major:", current->major.c_str());
            printf("%s║ %-20s ║ %-20s ║\n", indent(), "Enrolled Subject:", current->subject.c_str());
            printf("%s╚══════════════════════╩══════════════════════╝\n", indent());
            break;
        }
        case 2:
        { // View Grades by Subject
            printf("%s╔═════════════════════════════════════════════╗\n", indent());
            printf("%s║ %s║\n", indent(), centerText("GRADE REPORT", 44).c_str());
            printf("%s╠══════════════════════╦══════════════════════╣\n", indent());
            printf("%s║ %-20s ║ %-20s║\n", indent(), "SUBJECT", "GRADES (Latest First)");
            printf("%s╠══════════════════════╬══════════════════════╣\n", indent());

            for (const auto &subj : gradesBySubject)
            {
                string gradesStr;
                for (int i = subj.second.size() - 1; i >= 0; --i)
                {
                    gradesStr += to_string(subj.second[i]) + " ";
                }
                printf("%s║ %-20s ║ %-20s ║\n",
                       indent(),
                       subj.first.c_str(),
                       gradesStr.empty() ? "N/A" : gradesStr.c_str());
            }

            printf("%s╚══════════════════════╩══════════════════════╝\n", indent());
            break;
        }
        case 3:
        { // View Attendance
            printf("%s╔══════════════════════════════════════════════╗\n", indent());
            printf("%s║ %s ║\n", indent(), centerText("ATTENDANCE RECORDS", 44).c_str());
            printf("%s╠══════════════════════╦══════════╦════════════╣\n", indent());
            printf("%s║ %-20s ║ %-8s ║ %-10s ║\n", indent(), "DATE", "STATUS", "SUBJECT");
            printf("%s╠══════════════════════╬══════════╬════════════╣\n", indent());

            Attendance *att = current->attendanceHead;
            while (att)
            {
                printf("%s║ %-20s ║ %-8s ║ %-10s ║\n",
                       indent(),
                       att->date.c_str(),
                       att->present ? "Present" : "Absent",
                       current->subject.c_str());
                att = att->next;
            }

            printf("%s╚══════════════════════╩══════════╩════════════╝\n", indent());

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
                printf("%sAttendance Rate: %.1f%% (%d/%d)\n", indent(),
                       (present * 100.0) / total, present, total);
            }
            break;
        }
        case 4:
        { // Overall Performance
            printf("%s╔═════════════════════════════════════════════╗\n", indent());
            printf("%s║ %s ║\n", indent(), centerText("OVERALL PERFORMANCE", 44).c_str());
            printf("%s╠══════════════════════╦══════════════════════╣\n", indent());

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

            printf("%s║ %-20s ║ %-20.2f ║\n", indent(), "GPA:", gpa);
            printf("%s║ %-20s ║ %-20.1f%%║\n", indent(), "Attendance Rate:", attRate);
            printf("%s║ %-20s ║ %-20d ║\n", indent(), "Subjects Taken:", (int)gradesBySubject.size());
            printf("%s╚══════════════════════╩══════════════════════╝\n", indent());
            break;
        }
        case 5:
        { // Change Password
            string oldPass, newPass;
            cout<< indent() << "Enter current password: ";
            cin >> oldPass;
            if (oldPass != current->password)
            {
                cout<< indent() << "Incorrect password!\n";
                break;
            }
            cout<< indent() << "Enter new password: ";
            cin >> newPass;
            current->password = newPass;
            cout<< indent() << "Password changed successfully!\n";
            break;
        }
        case 6: // Logout
            cout<< indent() << "Logging out...\n";
            return;
        default:
            cout<< indent() << "Invalid choice!\n";
        }
    }
}