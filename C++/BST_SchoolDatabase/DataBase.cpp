#include "DataBase.h"


DataBase::DataBase() { //intialize the student and faculty tables
    studentTable = new LazyBST<Student>();  
    facultyTable = new LazyBST<Faculty>();
  
}

DataBase::~DataBase() {
    delete studentTable;
    delete facultyTable;
}

void DataBase::printMenu() { // prints to console the menu options for the database
    cout << "\nDatabase Menu:\n";
    cout << "1. Print all students\n";
    cout << "2. Print all faculty\n";
    cout << "3. Find and display student information given the student id\n";
    cout << "4. Find and display faculty information given the faculty id\n";
    cout << "5. Add a new student\n";
    cout << "6. Delete a student given the id\n";
    cout << "7. Add a new faculty member\n";
    cout << "8. Delete a faculty member given the id\n";
    cout << "9. Change a student's advisor given the student id and the new faculty id\n";
    cout << "10. Remove an advisee from a faculty member given the ids\n";
    cout << "11. Exit\n";
    cout << "Enter your choice: ";
}

void DataBase::executeOption(int option) { // takes in the user input and executes the corresponding function menu option
    switch (option) {
        case 1:
            printAllStudents();
            break;
        case 2:
            printAllFaculty();
            break;
        case 3:
            findStudent();
            break;
        case 4:
            findFaculty();
            break;
        case 5:
            addStudent();
            break;
        case 6:
            deleteStudent();
            break;
        case 7:
            addFaculty();
            break;
        case 8:
            deleteFaculty();
            break;
        case 9:
            changeAdvisor();
            break;
        case 10:
            removeAdvisee();
            break;
        case 11:
            saveToFile();
            cout << "Exiting program.\n";
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    }
}

void DataBase::printAllStudents() { //prints all students in the student table
    studentTable->printTree();
}

void DataBase::printAllFaculty() { //prints all faculty in the faculty table
    facultyTable->printTree();
}

void DataBase::findStudent() {
    int id;
    cout << "Enter student ID: "; //finds student and faculty by id
    cin >> id;

    Student tempStudent(id, "", "", "", 0.0, 0); // Create a temporary student to hold the found student
    TreeNode<Student>* foundStudentNode = studentTable->find(tempStudent); // Get the node
    if (foundStudentNode != nullptr) {
        Student* foundStudent = &foundStudentNode->key; // Extract the student from the node
        cout << *foundStudent << endl;
    } else {
        cout << "Student not found.\n";
    }
}

void DataBase::findFaculty() { //finds faculty by id then assigns the faculty to the found faculty node
    int id;
    cout << "Enter faculty ID: ";
    cin >> id;

    Faculty tempFaculty(id, "", "", "");
    TreeNode<Faculty>* foundFacultyNode = facultyTable->find(tempFaculty); // Get the node
    if (foundFacultyNode != nullptr) {
        Faculty* foundFaculty = &foundFacultyNode->key; // Extract the faculty from the node
        cout << *foundFaculty << endl;
    } else {
        cout << "Faculty not found.\n";
    }
}

void DataBase::addStudent() { //adds a student to the student table
    int id;
    string name, level, major; //user passes in the student id, name, level, major, gpa, and advisor id
    double gpa;
    int advisorId;

    cout << "Enter student ID: ";
    cin >> id;
    cout << "Enter student name: ";
    cin.ignore(); // Ignore the newline character
    getline(cin, name);
    cout << "Enter student level: ";
    getline(cin, level);
    cout << "Enter student major: ";
    getline(cin, major);
    cout << "Enter student GPA: ";
    cin >> gpa;
    cout << "Enter advisor ID: ";
    cin >> advisorId;

    // Check if the advisor ID exists in the faculty table
    if (!facultyTable->contains(Faculty(advisorId, "", "", ""))) {
        cout << "Faculty with ID " << advisorId << " not found. Student not added.\n";
        return;
    }

    Student newStudent(id, name, level, major, gpa, advisorId);
    studentTable->insert(newStudent);

    // Update the list of advisees for the corresponding faculty member
    Faculty tempFaculty(advisorId, "", "", "");
    TreeNode<Faculty>* foundFacultyNode = facultyTable->find(tempFaculty);
    if (foundFacultyNode != nullptr) {
        Faculty* foundFaculty = &foundFacultyNode->key;
        foundFaculty->addAdvisee(id);
    } else {
        cout << "Faculty with ID " << advisorId << " not found. Student added without updating advisee list.\n";
    }
}

void DataBase::deleteStudent() {
    int id;
    cout << "Enter student ID to delete: ";
    cin >> id;

    Student tempStudent(id, "", "", "", 0.0, 0); 
    if (studentTable->contains(tempStudent)) {
        studentTable->deleteNode(tempStudent);
        cout << "Student with ID " << id << " deleted.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void DataBase::addFaculty() {
    int id;
    string name, level, department;

    cout << "Enter faculty ID: ";
    cin >> id;
    cout << "Enter faculty name: ";
    cin.ignore(); // Ignore the newline character
    getline(cin, name);
    cout << "Enter faculty level: ";
    getline(cin, level);
    cout << "Enter faculty department: ";
    getline(cin, department);

    Faculty newFaculty(id, name, level, department);
    facultyTable->insert(newFaculty);
}

void DataBase::deleteFaculty() {
    int id;
    cout << "Enter faculty ID to delete: ";
    cin >> id;

    Faculty tempFaculty(id, "", "", "");
    if (facultyTable->contains(tempFaculty)) {
        facultyTable->deleteNode(tempFaculty);
        cout << "Faculty with ID " << id << " deleted.\n";
    } else {
        cout << "Faculty not found.\n";
    }
}

void DataBase::changeAdvisor() {
    int studentId, advisorId;
    cout << "Enter student ID: ";
    cin >> studentId;
    cout << "Enter new faculty ID: ";
    cin >> advisorId;

    // Check if the new advisor ID exists in the faculty table
    if (!facultyTable->contains(Faculty(advisorId, "", "", ""))) {
        cout << "New advisor with ID " << advisorId << " not found. Advisor not changed.\n";
        return;
    }

    // Get the student node and update the advisor ID
    Student tempStudent(studentId, "", "", "", 0.0, 0);
    TreeNode<Student>* foundStudentNode = studentTable->find(tempStudent);
    if (foundStudentNode != nullptr) {
        Student* foundStudent = &foundStudentNode->key;
        int oldAdvisorId = foundStudent->getAdvisorId();
        foundStudent->setAdvisorId(advisorId);

        // Update the list of advisees for the old advisor
        Faculty oldAdvisor(oldAdvisorId, "", "", "");
        TreeNode<Faculty>* oldAdvisorNode = facultyTable->find(oldAdvisor);
        if (oldAdvisorNode != nullptr) {
            Faculty* oldAdvisor = &oldAdvisorNode->key;
            oldAdvisor->removeAdvisee(studentId);
        } else {
            cout << "Old faculty with ID " << oldAdvisorId << " not found. Faculty not removed from old advisor's list.\n";
        }

        // Update the list of advisees for the new advisor
        TreeNode<Faculty>* newAdvisorNode = facultyTable->find(Faculty(advisorId, "", "", ""));
        if (newAdvisorNode != nullptr) {
            Faculty* newAdvisor = &newAdvisorNode->key;
            newAdvisor->addAdvisee(studentId);
        }
    }
}

void DataBase::removeAdvisee() {
    int facultyId, studentId;
    cout << "Enter faculty ID: ";
    cin >> facultyId;
    cout << "Enter student ID to remove: ";
    cin >> studentId;

    Faculty tempFaculty(facultyId, "", "", "");
    TreeNode<Faculty>* foundFacultyNode = facultyTable->find(tempFaculty); // Get the node
    if (foundFacultyNode != nullptr) {
        Faculty* foundFaculty = &foundFacultyNode->key; // Extract the faculty from the node
        foundFaculty->removeAdvisee(studentId);
        cout << "Advisee removed from faculty ID " << facultyId << endl;
    } else {
        cout << "Faculty not found.\n";
    }
}

void DataBase::saveToFile() {
    ofstream outFile("runLog.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    outFile << "Student Database:\n";
    studentTable->printTreeToFile(outFile); // Using printTreeToFile

    outFile << "\nFaculty Database:\n";
    facultyTable->printTreeToFile(outFile); // Using printTreeToFile

    outFile.close();
}