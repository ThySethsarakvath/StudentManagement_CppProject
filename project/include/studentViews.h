#ifndef STUDENT_VIEWS_H
#define STUDENT_VIEWS_H

#include "ui.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>

using namespace std;



// 1. Student Overview Display
void displayStudentOverview(StudentList *list, const string &subject)
{
    vector<Student *> students;
    Student *current = list->head;
    while (current)
    {
        if (current->subject == subject)
            students.push_back(current);
        current = current->next;
    }

    if (students.empty())
    {
        cout<<endl;
        printf("%s╔════════════════════════════════════╗\n",indent());
        printf("%s║ %s  ║\n",indent(), centerText("NO STUDENTS IN " + subject, 34).c_str());
        printf("%s╚════════════════════════════════════╝\n",indent());
        return;
    }

    printf("%s╔═════════════════════════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s ║\n", indent(), centerText("STUDENT OVERVIEW (" + subject + ")", 63).c_str());
    printf("%s╠═══════════╦══════════════════════╦════════╦═════╦═══════════════╣\n", indent());
    printf("%s║ %-9s ║ %-20s ║ %-5s ║ %-3s ║ %-13s ║\n", indent(), "ID", "NAME", "GENDER", "AGE", "MAJOR");
    printf("%s╠═══════════╬══════════════════════╬════════╬═════╬═══════════════╣\n", indent());

    for (const auto &s : students)
    {
        printf("%s║ %-9s ║ %-20s ║ %-5s  ║ %-3d ║ %-13s ║\n",
               indent(),
               s->id.c_str(),
               s->name.substr(0, 20).c_str(),
               s->gender.c_str(),
               s->age,
               s->major.substr(0, 13).c_str());
    }

    printf("%s╚═══════════╩══════════════════════╩════════╩═════╩═══════════════╝\n", indent());
    printf("%sTotal Students: %zu\n", indent(), students.size());
}

// 2. Grade View Display
void displayGradeView(StudentList *list, const string &subject)
{
    vector<Student *> students;
    Student *current = list->head;
    while (current)
    {
        if (current->subject == subject)
            students.push_back(current);
        current = current->next;
    }

    printf("%s╔═══════════════════════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s ║\n", indent(), centerText("GRADE REPORT (" + subject + ")", 62).c_str());
    printf("%s╠═══════════╦══════════════════════╦═════════════╦══════════════╣\n", indent());
    printf("%s║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n", indent(), "ID", "NAME", "GRADE", "PERFORMANCE");
    printf("%s╠═══════════╬══════════════════════╬═════════════╬══════════════╣\n", indent());

    for (const auto &s : students)
    {
        Grade *grade = s->gradesHead;
        float latestScore = -1;
        while (grade)
        {
            if (grade->subject == subject)
                latestScore = grade->score;
            grade = grade->next;
        }

        string performance;
        if (latestScore >= 85)
            performance = "Excellent";
        else if (latestScore >= 70)
            performance = "Good";
        else if (latestScore >= 50)
            performance = "Average";
        else if (latestScore >= 0)
            performance = "Poor";
        else
            performance = "No Data";

        printf("%s║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n",
               indent(),
               s->id.c_str(),
               s->name.substr(0, 20).c_str(),
               (latestScore >= 0) ? to_string(latestScore).c_str() : "N/A",
               performance.c_str());
    }

    printf("%s╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n", indent());
}

// 3. Attendance View Display
void displayAttendanceView(StudentList *list, const string &subject)
{
    vector<Student *> students;
    Student *current = list->head;
    while (current)
    {
        if (current->subject == subject)
            students.push_back(current);
        current = current->next;
    }

    printf("%s╔═══════════════════════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s║\n", indent(), centerText("ATTENDANCE REPORT (" + subject + ")", 62).c_str());
    printf("%s╠═══════════╦══════════════════════╦═════════════╦══════════════╣\n", indent());
    printf("%s║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n", indent(), "ID", "NAME", "LAST ATTEND", "STATUS");
    printf("%s╠═══════════╬══════════════════════╬═════════════╬══════════════╣\n", indent());

    for (const auto &s : students)
    {
        Attendance *att = s->attendanceHead;
        string lastDate = "N/A";
        string lastStatus = "N/A";

        // Get most recent attendance
        while (att)
        {
            lastDate = att->date;
            lastStatus = att->present ? "Present" : "Absent";
            att = att->next;
        }

        printf("%s║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n",
               indent(),
               s->id.c_str(),
               s->name.substr(0, 20).c_str(),
               lastDate.c_str(),
               lastStatus.c_str());
    }

    printf("%s╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n", indent());
}

void showViewMenu(StudentList *list, const string &subject)
{
    while (true)
    {
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║            Select View             ║\n", indent());
        printf("%s╠════════════════════════════════════╣\n", indent());
        printf("%s║ 1. Student Overview                ║\n", indent());
        printf("%s║ 2. Grade View                      ║\n", indent());
        printf("%s║ 3. Attendance View                 ║\n", indent());
        printf("%s║ 4. Back to Teacher Panel           ║\n", indent());
        printf("%s╚════════════════════════════════════╝\n", indent());

        int viewChoice = getMenuChoice(1, 4);

        switch (viewChoice)
        {
        case 1:
            displayStudentOverview(list, subject);
            break;
        case 2:
            displayGradeView(list, subject);
            break;
        case 3:
            displayAttendanceView(list, subject);
            break;
        case 4:
            cout << indent() << "Returning to Teacher Panel...\n";
            return; // Exits this function only
        default:
            cout << indent() << "Invalid choice!\n";
        }
    }
}

#endif