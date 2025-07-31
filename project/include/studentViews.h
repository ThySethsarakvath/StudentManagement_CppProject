#ifndef STUDENT_VIEWS_H
#define STUDENT_VIEWS_H

#include "ui.h"
#include "student.h"
#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

void displayStudentOverview(StudentList *list, const string &subject)
{
    cout << COLOR_MAGENTA;
    int studentCount = 0;
    Student *current = list->head;

    // First pass to count students in this subject
    while (current)
    {
        if (current->subject == subject)
        {
            studentCount++;
        }
        current = current->next;
    }

    if (studentCount == 0)
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

    // Second pass to display students
    current = list->head;
    while (current)
    {
        if (current->subject == subject)
        {
            printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-5s%s  ║ %s%-3d%s ║ %s%-13s%s ║\n", indent(),
                   COLOR_BRIGHT_GREEN, current->id.c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, current->name.substr(0, 20).c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, current->gender.c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, current->age, COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, current->major.substr(0, 13).c_str(), COLOR_MAGENTA);
        }
        current = current->next;
    }
    printf("%s╚═══════════╩══════════════════════╩════════╩═════╩═══════════════╝\n", indent());
    printf("%s%sTotal Students: %d%s\n", indent(), COLOR_BRIGHT_YELLOW, studentCount, COLOR_RESET);
}

void displayGradeView(StudentList *list, const string &subject)
{
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

    Student *current = list->head;
    while (current)
    {
        if (current->subject == subject)
        {
            Grade *grade = current->gradesHead;
            float latestScore = -1;
            while (grade)
            {
                if (grade->subject == subject)
                {
                    latestScore = grade->score;
                }
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

            const char *scoreText;

            if (latestScore >= 0)
            {
                scoreText = to_string(latestScore).c_str();
            }
            else
            {
                scoreText = "N/A";
            }

            printf("%s║ %s%-9s%s ║ %s%-20s%s ║ %s%-11s%s ║ %s%-12s%s ║\n", indent(),
                   COLOR_BRIGHT_GREEN, current->id.c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, current->name.substr(0, 20).c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, scoreText, COLOR_MAGENTA,
                   perfColor.c_str(), performance.c_str(), COLOR_MAGENTA);
        }
        current = current->next;
    }
    printf("%s╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n", indent());
    cout << COLOR_RESET;
}

void displayAttendanceView(StudentList *list, const string &subject)
{
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

    Student *current = list->head;
    while (current)
    {
        if (current->subject == subject)
        {
            Attendance *att = current->attendanceHead;
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
                   COLOR_BRIGHT_GREEN, current->id.c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, current->name.substr(0, 20).c_str(), COLOR_MAGENTA,
                   COLOR_BRIGHT_GREEN, lastDate.c_str(), COLOR_MAGENTA,
                   statusColor.c_str(), lastStatus.c_str(), COLOR_MAGENTA);
        }
        current = current->next;
    }
    printf("%s╚═══════════╩══════════════════════╩═════════════╩══════════════╝\n", indent());
    cout << COLOR_RESET;
}

void showViewMenu(StudentList *list, const string &subject)
{
   
    while (true)
    {
        cout << COLOR_MAGENTA;
        printf("%s╔════════════════════════════════════╗\n", indent(), COLOR_MAGENTA);
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
            return;

        default:
            cout << COLOR_BRIGHT_RED;
            cout << indent() << "Invalid choice!\n";
        }
    }
    cout << COLOR_RESET;
}

// For View Attendance in student dashboard
void showAttendancePanel(Attendance *attendanceHead, const string &subject)
{
    clearTerminal();
    cout << COLOR_MAGENTA;
    printf("%s╔══════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s%-44s%s ║\n", indent(), COLOR_BLUE, centerText("ATTENDANCE RECORDS", 44).c_str(), COLOR_MAGENTA);
    printf("%s╠══════════════════════╦══════════╦════════════╣\n", indent());
    printf("%s║ %s%-20s%s ║ %s%-8s%s ║ %-10s ║\n", indent(),
           COLOR_BLUE, "DATE", COLOR_MAGENTA,
           COLOR_BLUE, "STATUS", COLOR_MAGENTA,
           "SUBJECT");
    printf("%s╠══════════════════════╬══════════╬════════════╣\n", indent());

    int total = 0, present = 0;
    Attendance *att = attendanceHead;

    while (att)
    {
        const char *statusText;
        const char *statusColor;

        if (att->present)
        {
            statusText = "Present";
            statusColor = COLOR_BRIGHT_GREEN;
        }
        else
        {
            statusText = "Absent";
            statusColor = COLOR_BRIGHT_RED;
        }

        printf("%s║ %-20s ║ %s%-8s%s ║ %-10s ║\n", indent(),
               att->date.c_str(),
               statusColor, statusText, COLOR_MAGENTA,
               subject.c_str());
        total++;
        if (att->present)
            present++;
        att = att->next;
    }

    printf("%s╚══════════════════════╩══════════╩════════════╝\n", indent());

    if (total > 0)
    {
        printf("%s%sAttendance Rate: %.1f%% (%d/%d)%s\n", indent(),
               COLOR_BRIGHT_YELLOW,
               (present * 100.0) / total, present, total,
               COLOR_RESET);
    }

    cout << COLOR_RESET;
    enter();
}

void showGradePanel(Grade *gradesHead, const string &subject)
{
    clearTerminal();
    cout << COLOR_MAGENTA;
    printf("%s╔═════════════════════════════════════════════╗\n", indent());
    printf("%s║ %s%-44s%s║\n", indent(), COLOR_BLUE, centerText("GRADE REPORT", 44).c_str(), COLOR_MAGENTA);
    printf("%s╠══════════════════════╦══════════════════════╣\n", indent());
    printf("%s║ %s%-20s%s ║ %-20s║\n", indent(),
           COLOR_BLUE, "SUBJECT", COLOR_MAGENTA,
           "GRADES (Latest First)");
    printf("%s╠══════════════════════╬══════════════════════╣\n", indent());

    // Count grades
    int count = 0;
    Grade *temp = gradesHead;
    while (temp)
    {
        if (temp->subject == subject)
            count++;
        temp = temp->next;
    }

    if (count == 0)
    {
        printf("%s║ %-20s ║ %-20s ║\n", indent(), subject.c_str(), "No grades available");
    }
    else
    {
        float *scores = new float[count];
        int index = 0;
        temp = gradesHead;

        while (temp)
        {
            if (temp->subject == subject)
                scores[index++] = temp->score;
            temp = temp->next;
        }

        string gradesStr;
        for (int i = count - 1; i >= 0; i--)
            gradesStr += to_string(scores[i]) + " ";

        printf("%s║ %-20s ║ %-20s ║\n", indent(), subject.c_str(), gradesStr.c_str());
        delete[] scores;
    }

    printf("%s╚══════════════════════╩══════════════════════╝\n", indent());
    cout << COLOR_RESET;
}

#endif // STUDENT_VIEWS_H