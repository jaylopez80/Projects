#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "MonoStack.h"

class SpeakerView{
private:
    double **seating; //2D array to store the seating arrangement
    string line; //string to store the heights from the file
    int rows; //number of rows
    int cols; //number of columns

public:
    SpeakerView(const string &filename); //constructor
       
    ~SpeakerView(); //destructor

    void readSeating(const string &filename); //read the seating arrangement from the file

    void calculateView(); //calculate the view of the speaker

};

#endif