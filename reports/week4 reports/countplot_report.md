CountPlot Example report

What the Code Does
The CountPlot utility is a  C++ program designed to process raw categorical data like survey votes or item lists and generate an organised frequency report in text. It takes a vector of strings, tallies how many times each unique choice appears using a digital scoreboard and outputs a  summary of the survey by showing its title and each item and its corresponding count.

Files and Functions Used

Files:

Plot.hpp / Plot.cpp; this was the parent class definition and implementation
CountPlot.hpp / CountPlot.cpp; this was the derived class handling specific tallying and summary work
main.cpp; this was the entry point where raw data is passed and is tested

Key Functions:

Plot Constructor; Initializes and stores the shared parent title (title_).
CountPlot Constructor; Accepts the raw data vector (categories_) and connects to the parent class
summary(); Gathers the counted map data, formats the title and tally lines using text gluing (+=), and returns the final result in string format.

Key C++ Concepts Used
Inheritance: Establishing a parent-child relationship where CountPlot gets its core structure from Plot.
Pure Virtual Functions (= 0): Making Plot an abstract parrent class that forces the child class to implement its own custom behaviors.
Access Modifiers like (protected:): This one allowed the derived child class to access parent variables like title_ directly while preventing outside code from seeing .
Containers (std::vector & std::map): Using vectors to store  data lists and std::map to count exactly how many times each item appears in the list
Multi File Compilation (g++): Compiling multiple translation units (main.cpp and CountPlot.cpp) together into a single executable binary.


Completed  Tasks
Architecture Design. I defined the roles of the parent class and the specialized counting child class.
Constructor Setup where we configured initialization lists to send titles up to the parent and safely store data vectors.


Challenges
Encapsulation errors were faced when trying to access title_, which was resolved by understanding C++ inheritance rules and updating the parent variable from private: to protected:.

Compilation of many files where the terminal was compiling the main.cpp alone not combined with the .cpp and .hpp files. This was resolved by opening an integrated terminal and typing the run command in there



AI Tool Used, Purpose, and Reason
AI Tool: Gemin

Purpose: it helped remind and explain to me the difference between private and protected. I also used it to learn hoow to open an integrated terminal to run my code in. I also used it to understand the countplot core implementation better and explain some complicated aspects like std::map. 

In conclusion, the example shows how core implementation code can beused in a practical example, making the program useful, easier to understand, maintain, and reuse with different datasets. 