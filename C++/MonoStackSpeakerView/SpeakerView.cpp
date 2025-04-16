#include "SpeakerView.h"

SpeakerView::SpeakerView(const string &filename){ //constructor takes in a string filename
    readSeating(filename);
}
SpeakerView::~SpeakerView(){ // destructor
    for(int i = 0; i < rows; ++i){ 
        delete[] seating[i]; // delete the array of doubles for each row
    }
    delete[] seating; // delete the array of double pointers
}


void SpeakerView::readSeating(const string &filename) {
    ifstream file(filename); // open the file
    if (!file.is_open()) { // check if the file is open
        throw runtime_error("Unable to open file.");
    }

    //count number of lines/rows and the number of heights in the first line/columns
    rows = 0;
    cols = 0;
    while (getline(file, line)) {
        ++rows;
        int count = 0; 
        for (int i = 0; i < line.length(); ++i) { 
            if (line[i] == ' ') {// checks for spaces in the line
                ++count;
            }
        }
        ++count;  // adds 1 for the last height in the line
        if (count > cols) { 
            cols = count; //updates cols to the number of heights in the line
        }
    }

    file.clear();
    file.seekg(0); //move to the beginning of the file

    
    seating = new double *[rows]; // allocate 2d array for seating arrangement/rows&columns
    for (int i = 0; i < rows; ++i) {
        seating[i] = new double[cols];
    }

    
    for (int i = 0; i < rows; ++i) { //
        for (int j = 0; j < cols; ++j) { 
            if (!(file >> seating[i][j])) { //reads the height from the file to position or error reading file
                throw runtime_error("Error reading file.");
            }
        }
    }

    file.close(); // Close the file
}


void SpeakerView::calculateView() {
    cout << "Calculating the view of the speaker\n";
    for (int j = 0; j < cols; ++j) {
        MonoStack<double> views(rows, 'd'); // creates a decreasing stack for the heights
        MonoStack<double> tallestHeights(rows, 'i'); //create another temporary stack to hold tallest heights
        int count = 0; // hold number of people that can see the speaker

        cout << "In column " << j << " there are ";

    
        for (int i = 0; i < rows; ++i) { //loop through the rows
            double height = seating[i][j];
            if (views.isEmpty() || height >= views.peek()) {
                views.push(height);
                tallestHeights.push(height); //tallest heights onto the temporary stack
                ++count;
            }
        }

        cout << count << " that can see. Their heights are: ";

        //prints all heights of people who can see the speaker in reverse order
        while (!tallestHeights.isEmpty()) {
            cout << tallestHeights.pop() << " inches";
            if (!tallestHeights.isEmpty()) {
                cout << ", ";
            }
        }
        cout << ".\n";
    }
}
