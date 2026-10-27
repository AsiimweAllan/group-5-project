#include <iostream>
#include <vector>
#include <string>
#include "CountPlot.hpp" // connects to your header file so main.cpp knnows what survey::CountPlot is

int main() {
    //  list of votes for our assesment preference poll
    std::vector<std::string> assesment_votes = { // looks through the choices list and gives them to the program to process
        "presentations", "assignments", "presentations", "tests", "assignments", "assignments"
    };

    // make the CountPlot object inside the survey namespace
    survey::CountPlot pollPlot(assesment_votes);

     //call the function to compile the map counts and prints a summary report
    std::cout << pollPlot.summary() << std::endl; //call the function to compile the map counts and prints a summary report
    

    return 0;
}