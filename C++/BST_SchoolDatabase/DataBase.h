#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include "Faculty.h"
#include <fstream>
#include "LazyBST.h"

class DataBase {
public:
    DataBase();
    ~DataBase();

    void printMenu(); // prints to console the menu options for the database
    void executeOption(int option);// takes in the user input and executes the corresponding function menu option
    void printAllStudents();// prints all students from the student table
    void printAllFaculty(); // prints all faculty from the faculty table
    void printAllFacultyHelper(TreeNode<Faculty>* node); // Helper function for printAllFaculty
    void findStudent(); //finds student and faculty by id
    void findFaculty();
    void addStudent(); //adds and deletes students and faculty by id
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisor(); //changes the advisor of a student using the student id and the new faculty id
    void removeAdvisee();
    void saveToFile(); //saves the database to a file after the user exits the program

private:
    LazyBST<Student> *studentTable; // LazyBST for students
    LazyBST<Faculty> *facultyTable; // LazyBST for faculty

    
};

#endif
