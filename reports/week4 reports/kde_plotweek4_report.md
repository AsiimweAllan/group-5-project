Week 4 Report

This week, I continued working on my KDE component . I reviewed the code to make sure the KDE calculations and the evaluateRange() function were working correctly.

I also worked on testing the component, including checking how it handles invalid inputs such as empty data, zero bandwidth, and invalid range values. The tests ran successfully without errors.

The evaluateRange() function generates coordinate pairs containing x-values and their corresponding density values. These points can be used by the group's plotting system to draw a KDE curve.

 The main KDE calculations, range evaluation, and input validation are implemented and tested. The remaining step is to ensure that the component works correctly when integrated with the group's plotting system.