
#include <iostream>
#include <vector>
#include "KDE.h"

// the program doesnt cslc average, intsead it calculates the density of marks around each score

int main()
{
    // Marks of the  six students
    std::vector<double> marks = {45, 50, 52, 55, 60, 65};

    // Create a KDE object with bandwidth 5(band widith is a part of the KDE  math implementation)
    KDE kde(marks, 5.0); // here, KDE is the class, while kde is the object created from it
    // the class is like a blue print while the object is the thing created using the blue print

    // these are scores whose density we want to analyse    
    std::vector<double> scores = {40, 50, 55, 60, 70}; // this one can store multiple values in variable and grow or shrink

    std::cout << "Student Exam Mark Density\n";
    

    for (double score : scores) { // the loop goes through every value stored in the scores vector one at a time
        std::cout << "Score: " << score
                  << " | Density: "
                  << kde.evaluate(score) << '\n';
    }

    return 0;
}
