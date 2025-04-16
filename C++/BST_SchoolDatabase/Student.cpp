#include "Student.h"

//default constructor intializes with default values
Student::Student() : id(0), name(""), level(""), majorVal(""), gpa(0.0), advisorId(0) {}

//overloaded constructor with id, name, level, major, gpa, and advisor id
Student::Student(int id, string name, string level, string majorVal, double gpa, int advisorId)
    : id(id), name(name), level(level), majorVal(majorVal), gpa(gpa), advisorId(advisorId) {}

Student::~Student() {}

//getters for student id, name, level, major, gpa, and advisor id
int Student::getId() const {
    return id;
}

string Student::getName() const {
    return name;
}

string Student::getLevel() const {
    return level;
}

string Student::getMajor() const {
    return majorVal;
}

double Student::getGpa() const {
    return gpa;
}

int Student::getAdvisorId() const {
    return advisorId;
}

void Student::setAdvisorId(int advisorId) {
    this->advisorId = advisorId;
}

//overloaded operators for student id comparison
bool Student::operator<(const Student& s) const {
    return id < s.id;
}

bool Student::operator>(const Student& s) const {
    return id > s.id;
}

bool Student::operator==(const Student& s) const {
    return id == s.id;
}
bool Student::operator!=(const Student& s) const {
    return id != s.id;
}

//overloaded stream to print out student information
ostream& operator<<(ostream& os, const Student& student) {
    os << "Student ID: " << student.id << endl;
    os << "Name: " << student.name << endl;
    os << "Level: " << student.level << endl;
    os << "Major: " << student.majorVal << endl;
    os << "GPA: " << student.gpa << endl;
    os << "Advisor ID: " << student.advisorId << endl;
    return os;
}
