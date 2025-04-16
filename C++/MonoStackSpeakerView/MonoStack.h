#ifndef MONOSTACK_H  
#define MONOSTACK_H

#include <iostream> //pre-processor directory
#include <exception>
using namespace std;

template<typename T>
class MonoStack{

    public:
        MonoStack();
        MonoStack(int maxSize, char o); // overloaded constructor
        ~MonoStack(); //destructor

        //core functions
        void push (T data); //aka insert at the top
        T pop(); //aka remove from the top
        T peek(); //aka top() in the stack but doesn't remove

        //aux functions
        int getSize();
        bool isEmpty();
        bool isFull();

    private:
        int top; // var keeping track of top
        int mSize; //max size of my stack
        char order; //order of the stack
        T *myArray; //pointer to the array holding the stack

};
template<typename T>
MonoStack<T>::MonoStack(){ //default constructor
    
    mSize = 64; //
    top = -1;
    order = 'i';
    myArray = new T[mSize]; //dynamically allocate memory for the array
}

template<typename T>
MonoStack<T>::MonoStack(int maxSize, char o){ //overloaded constructor
    
    mSize = maxSize;
    top = -1;
    order = o; // either 'i' or 'd' for increasing or decreasing
    myArray = new T[mSize];
}

template<typename T>
MonoStack<T>::~MonoStack(){ //destructor
    
    delete [] myArray; //delete the array
}

template<typename T> //push function
void MonoStack<T>::push(T data){
    
    if(isFull()){
        cout << "stack resizing";
        T *temp = new T[2 * mSize]; //allocate memory for the stack in an array by doubling the size

        for(int i = 0; i < mSize; ++i){
            temp[i] = myArray[i];//copy the elements from the old array to the new array
        }
        mSize *= 2;//update the size of the stack
        delete[] myArray; //delete the old array
        myArray = temp;// new array is now myArray
        top = mSize - 1;
        
    
    }
    while (!isEmpty() && ((order == 'i' && data < myArray[top]) || (order == 'd' && data > myArray[top]))){
        pop(); //pop until new element is greater than the top of the stack or less than the top of the stack
    }
    myArray[++top] = data;//add the new value to the stack
    // cout << "pushed " << data << endl;//debugging print
}


template<typename T> //pop function
T MonoStack<T>::pop(){
    if(isEmpty()){
        throw runtime_error("Stack is empty, cant pop");
    }
    return myArray[top--];
}

template<typename T> //peek function
T MonoStack<T>::peek(){
    if(isEmpty()){
        throw runtime_error("Stack is empty, cant peek");
    }
    return myArray[top];
}

template<typename T> //check if stack is empty
bool MonoStack<T>::isEmpty(){
    return (top == -1);
}

template<typename T> //check if stack is full
bool MonoStack<T>::isFull(){
    return (top == mSize - 1);
}

template<typename T> //returns the size of the stack
int MonoStack<T>::getSize(){
    return top + 1;

}
#endif