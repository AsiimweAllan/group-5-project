The purpose of this project was to learn how to develop a histogram program using C++. The work began with understanding what a histogram is and how it represents the frequency of values in a dataset. The program was then developed and improved to explore fundamental C++ programming concepts, including arrays, loops, classes, access specifiers, encapsulation, inheritance, and polymorphism.
The project also involved attempting to compile and run the program in Visual Studio Code (VS Code), identifying compilation problems, and understanding the importance of a correctly configured programming environment.


A histogram is a graphical representation of the distribution of data. It shows how frequently different values occur in a dataset.
In this project, a text-based histogram was used. Instead of drawing bars on a graph, the program displays asterisks (`*`) to represent the frequency of each value. A value that occurs more frequently is represented by more asterisks.
For example, the dataset used in the program was:
{2, 3, 3, 4, 4, 4, 5, 5}
The program counts the number of occurrences of each value and displays the results using asterisks.

The first version of the program used a procedural approach. It stored the dataset in an array, used loops to count the occurrences of each value, and displayed the results.

The main programming concepts used in this version were:
-Arrays:Used to store the dataset and frequency counts.
-Loops: Used to examine the dataset and display the histogram.
-Counters: Used to record how many times each value occurred.
-Output statements: Used to display the histogram in the console.
This approach introduced the basic logic required to construct the histogram before moving on to object-oriented programming.

Compilation and Debugging in Visual Studio Code
During development, attempts to compile and run the program in VS Code produced errors. Even a simple test program was affected, suggesting that the problem might have involved the compiler configuration, task settings, or execution environment rather than the histogram logic alone.
Troubleshooting involved checking the source code, examining the terminal output, and considering the compiler and task configuration. This stage highlighted the importance of distinguishing between errors in a program's logic and problems with the development environment.

Transition to Object-Oriented Programming
The project was subsequently redesigned to demonstrate object-oriented programming. Instead of placing all the program's operations directly inside main(), the design introduced two classes:
1. HistogramBase — the base class that stores the dataset and declares a virtual display function.
2. TextHistogram — the derived class that calculates frequencies and displays the histogram.
This design separates the general features of a histogram from the specific way the histogram is displayed.

Classes, Data Members, and Member Functions
HistogramBase
The HistogramBase class stores the dataset in an integer array named data and records the number of elements in the variable size.
Its constructor initializes the dataset. The class also declares a pure virtual function named display(), which requires a derived class to provide an implementation.
The data members are declared as protected, allowing the derived class to access them while preventing ordinary external access.

TextHistogram
The TextHistogram class inherits from HistogramBase. It contains an array named frequency to store the occurrence count of each value.
The private member function countFrequencies() initializes the frequency array and calculates the number of occurrences of each dataset value. The public member function display() prints the histogram.

Encapsulation
Encapsulation involves grouping data and related operations inside a class while controlling access to its members.
In the project, the frequency array and the countFrequencies() function are declared private in TextHistogram. This prevents ordinary code outside the class from accessing them directly.
The display() function is declared public, allowing the histogram to be displayed through the class's public interface.
The data and size members of HistogramBase are declared protected. This allows TextHistogram to use them through inheritance.
The program therefore demonstrates how access specifiers control access to class members.

Inheritance
Inheritance allows one class to acquire accessible members from another class
The project uses the declaration:
class TextHistogram : public HistogramBase
Here, TextHistogram is the derived class, while HistogramBase is the base class. Public inheritance establishes an *is-a* relationship in which TextHistogram is a specific kind of histogram.
The derived class can access the protected data and size members of the base class. It also provides its own implementation of the display function.
Inheritance helps organize related functionality and reduces the need to place every responsibility in a single class.

Polymorphism
Polymorphism allows a common interface to be used with different implementations.
In this project, HistogramBase declares display() as a pure virtual function. The TextHistogram class overrides this function with instructions for displaying the histogram as text.
In main(), a pointer of type HistogramBase refers to a TextHistogram object. When ptr->display() is called, C++ invokes the overridden function in TextHistogram.
This demonstrates runtime polymorphism through a base-class pointer and a virtual function.

Program Execution
The program creates a TextHistogram object. Its constructor initializes the frequency counts using the dataset inherited from HistogramBase.
A base-class pointer is then assigned the address of the derived-class object. Calling display() through this pointer prints the histogram.
For the dataset {2, 3, 3, 4, 4, 4, 5, 5}, the expected output is:
HISTOGRAM
1:
2: *
3: **
4: ***
5: **
```
The output shows that value 1 occurs zero times, value 2 occurs once, value 3 occurs twice, value 4 occurs three times, and value 5 occurs twice.


 Class Layout Diagrams
The class diagrams should show each class, its data members, member functions, access specifiers, and inheritance relationship.

The project provided an opportunity to understand the relationship between program logic, object-oriented design, and the development environment.

The initial compilation difficulties showed the importance of examining compiler messages and checking the configuration of VS Code. The redesign also demonstrated that a program can be developed incrementally, beginning with a simple procedural solution and later introducing classes and object-oriented principles.


The project began with the implementation of a simple text-based histogram and progressed toward an object-oriented design. It covered the use of arrays and loops to count data frequencies, the organization of data and functions into classes, and the application of encapsulation, inheritance, and polymorphism.
The project also emphasized the importance of testing, debugging, and documenting the design of a C++ program. Further improvement could include allowing users to enter their own datasets or displaying histograms using different formats.
