Data Visualization Library Report
 Object-Oriented Programming Concepts

Encapsulation: The AxisData class uses private data members to store the axis range, label, ticks and numerical labels. Public getter and setter functions provide controlled access to this data.

Inheritance: The LabeledAxis class inherits from AxisData , reusing its existing properties and functions. It adds a unit data member to store the axis measurement unit.

Polymorphism: The printDetails() function is declared virtual in AxisData and overridden in LabeledAxis. When printAxis() receives a LabeledAxis object, the overridden function displays the standard axis information together with its measurement unit.

Conclusion: These additions extend the existing program to demonstrate encapsulation, inheritance and runtime polymorphism while retaining the original axis scaling and data management functionality.

![diagram](.pnimageg)

