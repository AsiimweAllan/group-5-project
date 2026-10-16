#week2 report on Testing

#Testing was carried on the KDE_plot_test
```The test was to check boundary conditions on the code to see some things that may prevent it from correct operation
```The tests are supposed to check how dense the data is around a specific value and thus the test shows that an empty constructor is rejected.

```Since the program feature has no real unit test yet, an assertion based test that checks the KDE maths is used as the test

#Checks
1. Empty inputs
2. Invalid bandwidth
3. Correct Peak Values
4. Density being higher near far data

#Failures
```Theres a failure caused by an implemenation detail where the constant of PI used is 3.14159, so the test needs to match the exact Gaussian normalization

#Achieved this week
1. Carried out tests on KDE plots to understand the working conditions
2. Figured out failures in the codes

#Prospects for next week
1. Report and correct failures in the KDE plots so that they are fixed
2. Carry out tests on data_intake and count_test

Submitted by Asiimwe Allan Mark
