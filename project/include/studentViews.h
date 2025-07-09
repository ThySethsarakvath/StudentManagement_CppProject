#ifndef STUDENT_VIEWS_H
#define STUDENT_VIEWS_H

#include "student.h"
#include "helpers.h"
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
        printf("\n╔════════════════════════════════════╗\n");
        printf("║ %s ║\n", centerText("NO STUDENTS IN " + subject, 34).c_str());
        printf("╚════════════════════════════════════╝\n");
        return;
    }

    printf("\n╔═════════════════════════════════════════════════════════════════╗\n");
    printf("║ %s ║\n", centerText("STUDENT OVERVIEW (" + subject + ")", 63).c_str());
    printf("╠═══════════╦══════════════════════╦════════╦═════╦═══════════════╣\n");
    printf("║ %-9s ║ %-20s ║ %-5s ║ %-3s ║ %-13s ║\n", "ID", "NAME", "GENDER", "AGE", "MAJOR");
    printf("╠═══════════╬══════════════════════╬════════╬═════╬═══════════════╣\n");

    for (const auto &s : students)
    {
        printf("║ %-9s ║ %-20s ║ %-5s  ║ %-3d ║ %-13s ║\n",
               s->id.c_str(),
               s->name.substr(0, 20).c_str(),
               s->gender.c_str(),
               s->age,
               s->major.substr(0, 13).c_str());
    }
    printf("╚═══════════╩══════════════════════╩════════╩═════╩═══════════════╝\n");
    printf("Total Students: %zu\n", students.size());
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

    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║ %s ║\n", centerText("GRADE REPORT (" + subject + ")", 62).c_str());
    printf("╠═══════════╦══════════════════════╦═════════════╦══════════════╣\n");
    printf("║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n", "ID", "NAME", "GRADE", "PERFORMANCE");
    printf("╠═══════════╬══════════════════════╬═════════════╬══════════════╣\n");

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

        printf("║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n",
               s->id.c_str(),
               s->name.substr(0, 20).c_str(),
               (latestScore >= 0) ? to_string(latestScore).c_str() : "N/A",
               performance.c_str());
    }
    printf("╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n");
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

    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║ %s║\n", centerText("ATTENDANCE REPORT (" + subject + ")", 62).c_str());
    printf("╠═══════════╦══════════════════════╦═════════════╦══════════════╣\n");
    printf("║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n", "ID", "NAME", "LAST ATTEND", "STATUS");
    printf("╠═══════════╬══════════════════════╬═════════════╬══════════════╣\n");

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

        printf("║ %-9s ║ %-20s ║ %-11s ║ %-12s ║\n",
               s->id.c_str(),
               s->name.substr(0, 20).c_str(),
               lastDate.c_str(),
               lastStatus.c_str());
    }
    printf("╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n");
}

#endif