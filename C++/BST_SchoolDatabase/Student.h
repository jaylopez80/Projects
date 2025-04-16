#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Student {
public:
    Student();
    Student(int id, string name, string level, string majorVal, double gpa, int advisorId);
    virtual ~Student();

    int getId() const; //getters for student id, name, level, major, gpa, and advisor id
    string getName() const;
    string getLevel() const;
    string getMajor() const;
    double getGpa() const;
    int getAdvisorId() const;

    void setAdvisorId(int advisorId);

    // Overloaded operators for id comparison
    bool operator<(const Student& s) const;
    bool operator>(const Student& s) const;
    bool operator==(const Student& s) const;
    bool operator!=(const Student& s) const;

    // Overloaded output stream operator for displaying student information
    friend ostream& operator<<(ostream& os, const Student& student);

private: //member variables for student id, name, level, major, gpa, and advisor id
    int id;
    string name;
    string level;
    string majorVal;
    double gpa;
    int advisorId;
};

#endif 
