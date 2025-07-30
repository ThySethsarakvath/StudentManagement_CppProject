#ifndef FILE_IO_H
#define FILE_IO_H

#include "addStudent.h"
#include "student.h"
#include <fstream>
#include <cstring> // for strtok
#include <sys/stat.h>

using namespace std;

void createDataDirectory()
{
    mkdir("../Data");
}

// Helper function to count tokens in a CSV line
int countTokens(const char *line)
{
    int count = 0;
    bool inToken = false;
    while (*line)
    {
        if (*line != ',' && !inToken)
        {
            inToken = true;
            count++;
        }
        else if (*line == ',')
        {
            inToken = false;
        }
        line++;
    }
    return count;
}

void saveAllData(StudentList *list)
{
    createDataDirectory();

    ofstream studentFile("../Data/students.csv");
    ofstream gradeFile("../Data/grades.csv");
    ofstream attendanceFile("../Data/attendance.csv");

    // Write headers
    studentFile << "ID,Password,Name,Gender,Age,Major,Subject\n";
    gradeFile << "StudentID,Subject,Score\n";
    attendanceFile << "StudentID,Date,Present\n";

    Student *current = list->head;
    while (current)
    {
        // Save student
        studentFile << current->id << ","
                    << current->password << ","
                    << current->name << ","
                    << current->gender << ","
                    << current->age << ","
                    << current->major << ","
                    << current->subject << "\n";

        // Save grades
        Grade *grade = current->gradesHead;
        while (grade)
        {
            gradeFile << current->id << ","
                      << grade->subject << ","
                      << grade->score << "\n";
            grade = grade->next;
        }

        // Save attendance
        Attendance *att = current->attendanceHead;
        while (att)
        {
            string presenceValue;
            if (att->present)
            {
                presenceValue = "1";
            }
            else
            {
                presenceValue = "0";
            }

            attendanceFile << current->id << ","
                           << att->date << ","
                           << presenceValue << "\n";
            att = att->next;
        }

        current = current->next;
    }
}

void loadAllData(StudentList *list)
{
    // Load students
    ifstream studentFile("../Data/students.csv");
    if (studentFile)
    {
        char line[256];
        studentFile.getline(line, 256); // Skip header

        while (studentFile.getline(line, 256))
        {
            if (countTokens(line) < 7)
                continue;

            char *tokens[7];
            int i = 0;
            char *token = strtok(line, ",");

            while (token && i < 7)
            {
                tokens[i++] = token;
                token = strtok(NULL, ",");
            }

            if (i == 7)
            {
                addStudent(list,
                           tokens[0],       // ID
                           tokens[1],       // Password
                           tokens[2],       // Name
                           tokens[3],       // Gender
                           atoi(tokens[4]), // Age
                           tokens[5],       // Major
                           tokens[6]        // Subject
                );
            }
        }
    }

    // Load grades
    ifstream gradeFile("../Data/grades.csv");
    if (gradeFile)
    {
        char line[256];
        gradeFile.getline(line, 256); // Skip header

        while (gradeFile.getline(line, 256))
        {
            if (countTokens(line) < 3)
                continue;

            char *tokens[3];
            int i = 0;
            char *token = strtok(line, ",");

            while (token && i < 3)
            {
                tokens[i++] = token;
                token = strtok(NULL, ",");
            }

            if (i == 3)
            {
                Student *s = list->head;
                while (s && strcmp(s->id.c_str(), tokens[0]) != 0)
                {
                    s = s->next;
                }

                if (s)
                {
                    Grade *newGrade = new Grade();
                    newGrade->subject = tokens[1];
                    newGrade->score = atof(tokens[2]);
                    newGrade->next = nullptr;

                    if (!s->gradesHead)
                    {
                        s->gradesHead = newGrade;
                    }
                    else
                    {
                        Grade *last = s->gradesHead;
                        while (last->next)
                            last = last->next;
                        last->next = newGrade;
                    }
                }
            }
        }
    }

    // Load attendance
    ifstream attendanceFile("../Data/attendance.csv");
    if (attendanceFile)
    {
        char line[256];
        attendanceFile.getline(line, 256); // Skip header

        while (attendanceFile.getline(line, 256))
        {
            if (countTokens(line) < 3)
                continue;

            char *tokens[3];
            int i = 0;
            char *token = strtok(line, ",");

            while (token && i < 3)
            {
                tokens[i++] = token;
                token = strtok(NULL, ",");
            }

            if (i == 3)
            {
                Student *s = list->head;
                while (s && strcmp(s->id.c_str(), tokens[0]) != 0)
                {
                    s = s->next;
                }

                if (s)
                {
                    Attendance *newAtt = new Attendance();
                    newAtt->date = tokens[1];
                    newAtt->present = strcmp(tokens[2], "1") == 0;
                    newAtt->next = nullptr;

                    if (!s->attendanceHead)
                    {
                        s->attendanceHead = newAtt;
                    }
                    else
                    {
                        Attendance *last = s->attendanceHead;
                        while (last->next)
                            last = last->next;
                        last->next = newAtt;
                    }
                }
            }
        }
    }
}

#endif // FILE_IO_H