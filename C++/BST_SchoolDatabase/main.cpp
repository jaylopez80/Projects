#include "DataBase.h"
#include <iostream>

using namespace std;

int main() {
    DataBase database;

    int choice;
    do {
        database.printMenu(); // calls the printMenu function to display the menu options for the database
        cin >> choice;

        database.executeOption(choice); // Call executeOption with the selected choice

    } while (choice != 11);
    database.saveToFile();

    return 0;
}


