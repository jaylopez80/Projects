// #include "MonoStack.h"

// template<typename T>
// MonoStack<T>::MonoStack(){ //default constructor
    
//     mSize = 64; //
//     top = -1;
//     order = 'i';
//     myArray = new T[mSize]; //dynamically allocate memory for the array
// }

// template<typename T>
// MonoStack<T>::MonoStack(int maxSize, char o){ //overloaded constructor
    
//     mSize = maxSize;
//     top = -1;
//     order = o; // either 'i' or 'd' for increasing or decreasing
//     myArray = new T[mSize];
// }

// template<typename T>
// MonoStack<T>::~MonoStack(){ //destructor
    
//     delete [] myArray; //delete the array
// }

// template<typename T> //push function
// void MonoStack<T>::push(T data){
    
//     if(isFull()){
//         cout << "stack resizing";
//         T *temp = new T[2 * mSize]; //allocate memory for the stack in an array by doubling the size

//         for(int i = 0; i < mSize; ++i){
//             temp[i] = myArray[i];//copy the elements from the old array to the new array
//         }
//         mSize *= 2;//update the size of the stack
//         delete[] myArray; //delete the old array
//         myArray = temp;// new array is now myArray
        
    
//     }
//     while (!isEmpty() && ((order == 'i' && data > myArray[top]) || (order == 'd' && data < myArray[top]))){
//         pop(); //pop the top value if the new value is greater than the top 
//     }
//     myArray[++top] = data;//add the new value to the stack
// }

// template<typename T> //pop function
// T MonoStack<T>::pop(){
//     if(isEmpty()){
//         throw runtime_error("Stack is empty, cant pop");
//     }
//     return myArray[top--];
// }

// template<typename T> //peek function
// T MonoStack<T>::peek(){
//     if(isEmpty()){
//         throw runtime_error("Stack is empty, cant peek");
//     }
//     return myArray[top];
// }

// template<typename T> //check if stack is empty
// bool MonoStack<T>::isEmpty(){
//     return (top == -1);
// }

// template<typename T> //check if stack is full
// bool MonoStack<T>::isFull(){
//     return (top == mSize - 1);
// }

// template<typename T> //returns the size of the stack
// int MonoStack<T>::getSize(){
//     return top + 1;
// }