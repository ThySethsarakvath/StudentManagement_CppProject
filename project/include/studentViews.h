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
    cout << COLOR_MAGENTA;
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
        clearTerminal();
        cout << endl;
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║ %s%s%s  ║\n", indent(), COLOR_BRIGHT_YELLOW, centerText("NO STUDENTS IN " + subject, 34).c_str(), COLOR_MAGENTA);
        printf("%s╚════════════════════════════════════╝\n", indent());

        return;
    }
    clearTerminal();
    printf("%s╔═════════════════════════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s%s%s ║\n", indent(), COLOR_BLUE, centerText("STUDENT OVERVIEW (" + subject + ")", 63).c_str(), COLOR_MAGENTA);
    printf("%s╠═══════════╦══════════════════════╦════════╦═════╦═══════════════╣\n", indent());
    printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-5s%s ║ %s%-3s%s ║ %s%-13s%s ║\n", indent(),
           COLOR_BLUE, "ID", COLOR_MAGENTA,
           COLOR_BLUE, "NAME", COLOR_MAGENTA,
           COLOR_BLUE, "GENDER", COLOR_MAGENTA,
           COLOR_BLUE, "AGE", COLOR_MAGENTA,
           COLOR_BLUE, "MAJOR", COLOR_MAGENTA);
    printf("%s╠═══════════╬══════════════════════╬════════╬═════╬═══════════════╣\n", indent());
    for (const auto &s : students)
    {
        printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-5s%s  ║ %s%-3d%s ║ %s%-13s%s ║\n", indent(),
               COLOR_BRIGHT_GREEN, s->id.c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, s->name.substr(0, 20).c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, s->gender.c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, s->age, COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, s->major.substr(0, 13).c_str(), COLOR_MAGENTA);
    }
    printf("%s╚═══════════╩══════════════════════╩════════╩═════╩═══════════════╝\n", indent());
    printf("%s%sTotal Students: %zu%s\n", indent(), COLOR_BRIGHT_YELLOW, students.size(), COLOR_RESET);
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
    clearTerminal();
    cout << COLOR_MAGENTA;
    printf("%s╔═══════════════════════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s%s%s ║\n", indent(), COLOR_BLUE, centerText("GRADE REPORT (" + subject + ")", 62).c_str(), COLOR_MAGENTA);
    printf("%s╠═══════════╦══════════════════════╦═════════════╦══════════════╣\n", indent());
    printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-11s%s ║ %s%-12s%s ║\n", indent(),
           COLOR_BLUE, "ID", COLOR_MAGENTA,
           COLOR_BLUE, "NAME", COLOR_MAGENTA,
           COLOR_BLUE, "GRADE", COLOR_MAGENTA,
           COLOR_BLUE, "PERFORMANCE", COLOR_MAGENTA);
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
        string perfColor;
        if (latestScore >= 85)
        {
            performance = "Excellent";
            perfColor = COLOR_BRIGHT_GREEN;
        }
        else if (latestScore >= 70)
        {
            performance = "Good";
            perfColor = COLOR_BRIGHT_GREEN;
        }
        else if (latestScore >= 50)
        {
            performance = "Average";
            perfColor = COLOR_BRIGHT_YELLOW;
        }
        else if (latestScore >= 0)
        {
            performance = "Poor";
            perfColor = COLOR_BRIGHT_RED;
        }
        else
        {
            performance = "No Data";
            perfColor = COLOR_WHITE;
        }

        printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-11s%s ║ %s%-12s%s ║\n", indent(),
               COLOR_BRIGHT_GREEN, s->id.c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, s->name.substr(0, 20).c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, (latestScore >= 0) ? to_string(latestScore).c_str() : "N/A", COLOR_MAGENTA,
               perfColor.c_str(), performance.c_str(), COLOR_MAGENTA);
    }

    printf("%s╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n", indent());
    cout << COLOR_RESET;
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

    clearTerminal();
    cout << COLOR_MAGENTA;
    printf("%s╔═══════════════════════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s%s%s║\n", indent(), COLOR_BLUE, centerText("ATTENDANCE REPORT (" + subject + ")", 62).c_str(), COLOR_MAGENTA);
    printf("%s╠═══════════╦══════════════════════╦═════════════╦══════════════╣\n", indent());
    printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-11s%s ║ %s%-12s%s ║\n", indent(),
           COLOR_BLUE, "ID", COLOR_MAGENTA,
           COLOR_BLUE, "NAME", COLOR_MAGENTA,
           COLOR_BLUE, "LAST ATTEND", COLOR_MAGENTA,
           COLOR_BLUE, "STATUS", COLOR_MAGENTA);
    printf("%s╠═══════════╬══════════════════════╬═════════════╬══════════════╣\n", indent());

    for (const auto &s : students)
    {
        Attendance *att = s->attendanceHead;
        string lastDate = "N/A";
        string lastStatus = "N/A";
        string statusColor = COLOR_WHITE;

        while (att)
        {
            lastDate = att->date;
            if (att->present)
            {
                lastStatus = "Present";
                statusColor = COLOR_BRIGHT_GREEN;
            }
            else
            {
                lastStatus = "Absent";
                statusColor = COLOR_BRIGHT_RED;
            }
            att = att->next;
        }

        printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-11s%s ║ %s%-12s%s ║\n", indent(),
               COLOR_BRIGHT_GREEN, s->id.c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, s->name.substr(0, 20).c_str(), COLOR_MAGENTA,
               COLOR_BRIGHT_GREEN, lastDate.c_str(), COLOR_MAGENTA,
               statusColor.c_str(), lastStatus.c_str(), COLOR_MAGENTA);
    }
    printf("%s╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n", indent());
    cout << COLOR_RESET;
}

void showViewMenu(StudentList *list, const string &subject)
{
    cout << COLOR_MAGENTA;
    while (true)
    {
        printf("%s╔════════════════════════════════════╗\n", indent());
        printf("%s║            %sSelect View             %s║\n", indent(), COLOR_BLUE, COLOR_MAGENTA);
        printf("%s╠════════════════════════════════════╣\n", indent());
        printf("%s║ %s1. Student Overview                %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s║ %s2. Grade View                      %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s║ %s3. Attendance View                 %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
        printf("%s║ %s4. Back to Teacher Panel           %s║\n", indent(), COLOR_BRIGHT_GREEN, COLOR_MAGENTA);
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
            clearTerminal();
            cout << indent() << "Returning to Teacher Panel...\n";
            return; // Exits this function only

        default:
            cout << COLOR_BRIGHT_RED;
            cout << indent() << "Invalid choice!\n";
        }
    }
    cout << COLOR_RESET;
}

#endif