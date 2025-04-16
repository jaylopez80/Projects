#include "Faculty.h"

//initalize constructor with id, name, level, and department
Faculty::Faculty() : id(0), name(""), level(""), department("") {}

Faculty::Faculty(int id, string name, string level, string department)
    : id(id), name(name), level(level), department(department) {}

Faculty::~Faculty() {}

//getters and setters for faculty
int Faculty::getId() const {
    return id;
}

string Faculty::getName() const {
    return name;
}

string Faculty::getLevel() const {
    return level;
}

string Faculty::getDepartment() const {
    return department;
}

list<int> Faculty::getAdvisees() const {
    return advisees;
}

void Faculty::addAdvisee(int studentId) {
    advisees.push_back(studentId);
}

void Faculty::removeAdvisee(int studentId) {
    advisees.remove(studentId);
}
//overloaded operators for faculty id comparison
bool Faculty::operator<(const Faculty& f) const {
    return id < f.id;
}

bool Faculty::operator>(const Faculty& f) const {
    return id > f.id;
}

bool Faculty::operator==(const Faculty& f) const {
    return id == f.id;
}
bool Faculty::operator!=(const Faculty& f) const {
    return id != f.id;
}

//overloaded stream to print out faculty
ostream& operator<<(ostream& os, const Faculty& faculty) {//
    os << "Faculty ID: " << faculty.id << endl;
    os << "Name: " << faculty.name << endl;
    os << "Level: " << faculty.level << endl;
    os << "Department: " << faculty.department << endl;
    os << "Advisees' IDs: ";
    for (int advisee : faculty.advisees) {
        os << advisee << " ";
    }
    os << endl;
    return os;
}
