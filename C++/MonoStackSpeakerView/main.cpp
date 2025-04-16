#include "SpeakerView.h"

int main(int argc, char *argv[]){
   
    try{
        SpeakerView* view = new SpeakerView(argv[1]); // create a new speaker view object (view)
        view->calculateView();
        delete view; // deallocate the memory
    }
    catch(runtime_error &except){
        cerr<< "Error: " << except.what() << endl;
        return 1;
    }
    return 0;
}