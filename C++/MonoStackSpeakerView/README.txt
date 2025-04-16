Jonathan Lopez

Compile command : g++ *.cpp -o views
Run: ./views input.txt
    For this project I implemented 2 classes consisting of a template MonoStack class derived from my genstack code and a Speakerview class that consisted
of a readSeating function for taking in the input file and a calculateView for determining the number of heights that could see the speaker. I used a
2D array to represent the seating arrangement in the speaker class, which is later used to read the file contents/heights 
into each column within the row array. I implemented the calculating of views by iterating through each row per column and using
the monotonically decreasing stack instance to store the unobstructed views. In order to achieve the correct output and ensure the 
heights were printed in the order from closest to the speaker to furthest, I used a tempStack that was monotonically increasing to 
reverse the order before popping each element. 
    

References:
https://www.geeksforgeeks.org/introduction-to-monotonic-stack-data-structure-and-algorithm-tutorials/
https://www.geeksforgeeks.org/set-position-with-seekg-in-cpp-language-file-handling/
https://www.geeksforgeeks.org/templates-cpp/
