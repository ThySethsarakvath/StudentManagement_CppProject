#ifndef FILE_IO_H
#define FILE_IO_H

#include "addStudent.h"
#include "student.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <sys/stat.h> // For directory creation

using namespace std;

// Helper function to create data directory
void createDataDirectory() {
    mkdir("../Data"); // Creates directory if it doesn't exist
}

void saveAllData(StudentList* list) {
    createDataDirectory();
    
    // Save students
    ofstream studentFile("../Data/students.csv");
    if (!studentFile.is_open()) {
        cerr << "Error opening students.csv for writing!" << endl;
        return;
    }
    studentFile << "ID,Password,Name,Gender,Age,Major,Subject\n";
    
    // Save grades
    ofstream gradeFile("../Data/grades.csv");
    if (!gradeFile.is_open()) {
        cerr << "Error opening grades.csv for writing!" << endl;
        return;
    }
    gradeFile << "StudentID,Subject,Score\n";
    
    // Save attendance
    ofstream attendanceFile("../Data/attendance.csv");
    if (!attendanceFile.is_open()) {
        cerr << "Error opening attendance.csv for writing!" << endl;
        return;
    }
    attendanceFile << "StudentID,Date,Present\n";

    Student* current = list->head;
    while (current) {
        // Save student info
        studentFile << current->id << ","
                   << current->password << ","
                   << current->name << ","
                   << current->gender << ","
                   << current->age << ","
                   << current->major << ","
                   << current->subject << "\n";
        
        // Save grades
        Grade* grade = current->gradesHead;
        while (grade) {
            gradeFile << current->id << ","
                     << grade->subject << ","
                     << grade->score << "\n";
            grade = grade->next;
        }
        
        // Save attendance
        Attendance* att = current->attendanceHead;
        while (att) {
            attendanceFile << current->id << ","
                         << att->date << ","
                         << (att->present ? "1" : "0") << "\n";
            att = att->next;
        }
        
        current = current->next;
    }
}

void loadAllData(StudentList* list) {
    // Load students
    ifstream studentFile("../Data/students.csv");
    if (!studentFile.is_open()) {
        cerr << "Note: students.csv not found (will create new file on save)" << endl;
    } else {
        string line;
        getline(studentFile, line); // Skip header
        
        while (getline(studentFile, line)) {
            vector<string> tokens;
            string token;
            istringstream tokenStream(line);
            
            while (getline(tokenStream, token, ',')) {
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 7) {
                addStudent(list, 
                          tokens[0], // ID
                          tokens[1], // Password
                          tokens[2], // Name
                          tokens[3], // Gender
                          stoi(tokens[4]), // Age
                          tokens[5], // Major
                          tokens[6]  // Subject
                );
            }
        }
    }
    
    // Load grades
    ifstream gradeFile("../Data/grades.csv");
    if (!gradeFile.is_open()) {
        cerr << "Note: grades.csv not found" << endl;
    } else {
        string line;
        getline(gradeFile, line); // Skip header
        
        while (getline(gradeFile, line)) {
            vector<string> tokens;
            string token;
            istringstream tokenStream(line);
            
            while (getline(tokenStream, token, ',')) {
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 3) {
                Student* s = list->head;
                while (s && s->id != tokens[0]) s = s->next;
                
                if (s) {
                    Grade* newGrade = new Grade{tokens[1], stof(tokens[2]), nullptr};
                    
                    // Add to end of grade list
                    if (!s->gradesHead) {
                        s->gradesHead = newGrade;
                    } else {
                        Grade* last = s->gradesHead;
                        while (last->next) last = last->next;
                        last->next = newGrade;
                    }
                }
            }
        }
    }
    
    // Load attendance
    ifstream attendanceFile("../Data/attendance.csv");
    if (!attendanceFile.is_open()) {
        cerr << "Note: attendance.csv not found" << endl;
    } else {
        string line;
        getline(attendanceFile, line); // Skip header
        
        while (getline(attendanceFile, line)) {
            vector<string> tokens;
            string token;
            istringstream tokenStream(line);
            
            while (getline(tokenStream, token, ',')) {
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 3) {
                Student* s = list->head;
                while (s && s->id != tokens[0]) s = s->next;
                
                if (s) {
                    Attendance* newAtt = new Attendance{
                        tokens[1], 
                        tokens[2] == "1", 
                        nullptr
                    };
                    
                    // Add to end of attendance list
                    if (!s->attendanceHead) {
                        s->attendanceHead = newAtt;
                    } else {
                        Attendance* last = s->attendanceHead;
                        while (last->next) last = last->next;
                        last->next = newAtt;
                    }
                }
            }
        }
    }
}

#endif // FILE_IO_H