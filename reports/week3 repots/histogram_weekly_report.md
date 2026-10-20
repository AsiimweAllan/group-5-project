1. Introduction
The histogram program is designed to count the frequency of numbers in an array and display the results using stars. The program demonstrates encapsulation, inheritance, and polymorphism through two classes: HistogramBase and TextHistogram.

2. Classes Used in the Program
HistogramBase
This is the base class. It stores the original data and its size. It also declares a pure virtual function called display(), which requires derived classes to provide their own implementation.

TextHistogram
This is the derived class that inherits from HistogramBase. It calculates the frequency of each number and displays the histogram in the console.

3. Data Members and Member Functions
HistogramBase
Protected data member
-data[8]: Stores the input numbers.
-size: Stores the number of elements in the array.

Public member functions
-HistogramBase(): Initializes the input data and array size.
-display(): A pure virtual function that defines the interface for displaying the histogram.
-HistogramBase(): A virtual destructor.

TextHistogram
Private data members
- frequency[6]: Stores the number of occurrences of each value.

Private member function
-countFrequencies(): Initializes the frequency array and counts the occurrences of the input values.

Public member functions
-TextHistogram(): Calls countFrequencies() to calculate the frequencies when an object is created.
-display(): Overrides the base class's virtual function and prints the histogram using stars.

4. Encapsulation
Encapsulation is demonstrated by keeping frequency and countFrequencies() private in the TextHistogram class. This prevents code outside the class from accessing them directly. The public display() function provides a way to show the calculated results without exposing the internal frequency array.
The data and size members are protected in the base class, allowing the derived class to use them while restricting direct access from unrelated external code.

5. Inheritance
Inheritance is demonstrated when TextHistogram inherits publicly from HistogramBase. The derived class can access the protected members data and size without declaring them again.
This reduces repetition and allows the program to separate the general histogram data from the specific process of counting and displaying frequencies.

6. Polymorphism
Polymorphism is demonstrated through the virtual function display(). The base class declares this function as pure virtual, while the derived class provides its implementation.
In the main() function, a pointer of type HistogramBase points to a TextHistogram object. When ptr->display() is called, C++ executes the overridden function in TextHistogram. This demonstrates runtime polymorphism.

7. Program Execution
The program creates a TextHistogram object. The constructor calculates the frequency of each number in the input array. The program then uses a base-class pointer to call the display function.
The output shows that the number 2 occurs once, 3 occurs twice, 4 occurs three times, and 5 occurs twice. Each star represents one occurrence of a number.

8. Conclusion
The program demonstrates how object-oriented programming can organize a histogram application into classes. Encapsulation controls access to internal data, inheritance allows the derived class to reuse members of the base class, and polymorphism allows the overridden display function to be called through a base-class pointer.

