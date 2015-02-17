# QuorumCalculator

## Description
Allows a club to input a CSV file and determine which of their members are currently considered voting members. The program is written in C++.

### For Deployment
Download the .cpp file, compile it into and executable, and run the program using the following usage guidelines:
`./executable_name <file name> <number of meetings> [meetings to pool]`

## Expected CSV File
The program (currently) assumes that the input follows a format of the following:
* Each line is the total attendance for a meeting
* Each name is delimted by a comma
* Later lines denote more recent meetings

## TODOs
* Add options for file input
* Allow exporting to files
* GUI (possibly)