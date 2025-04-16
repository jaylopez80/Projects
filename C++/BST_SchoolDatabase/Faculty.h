#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include <string>
#include <list>
#include<fstream>
using namespace std;

class Faculty {
public:
    Faculty();
    Faculty(int id, string name, string level, string department);
    virtual ~Faculty();

    int getId() const;
    string getName() const;
    string getLevel() const;
    string getDepartment() const;
    list<int> getAdvisees() const; // Return a copy of the list of advisees

    void addAdvisee(int studentId); // Add a student to the list of advisees
    void removeAdvisee(int studentId);

    // Overloaded operators for comparison of faculty id
    bool operator<(const Faculty& f) const;
    bool operator>(const Faculty& f) const;
    bool operator==(const Faculty& f) const;
    bool operator!=(const Faculty& f) const;

    // Overloaded output stream operator
    friend ostream& operator<<(ostream& os, const Faculty& faculty);

private:
    int id; //memeber variables name, level, department, and advisees for faculty
    string name;
    string level;
    string department;
    list<int> advisees;
};

#endif 
