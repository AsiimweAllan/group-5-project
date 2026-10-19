

DATA VISUALISATION LIBRARY
 Week 2; axis scaling and implementation
1.Introduction
This project involves developing a data visualization library using C++. Last week, we created an AxisData structure and implemented printAxis(). This week, we extended the program by introducing a class and implementing axis scaling.
2. Class Structure
The program contains a class called AxisData, which stores the minimum and maximum values, axis label, tick values and tick labels.
The class has five private data members: minValue, maxValue, axisLabel, ticks and labels. These are private to protect the data from direct external access.
Its public member functions include setRange(), setAxisLabel(), setTicks(), setLabels() and getter functions. These allow the program to modify and retrieve axis information. The constructor initializes the default axis range.
3. Implementation and Use
The axis.hpp file declares the class and functions, while axis.cpp implements them. The axis_example.cpp file creates an AxisData object, sets its values and tests the functions.
The printAxis() function displays the axis information, while scaleValue() calculates a normalized position using:
Scaled value = (value − minimum) / (maximum − minimum)
For an axis ranging from 0 to 100, the value 50 produces a scaled position of 0.5
4. Conclusion
This week's work extends the original program by introducing a class with private data members and public member functions. Axis scaling was also implemented and tested, providing a foundation for future graphing features.

