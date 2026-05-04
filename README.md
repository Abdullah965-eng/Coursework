# Power Quality Waveform Analyser

This is my C project for the Programming for Engineers module. It reads sensor data from a CSV and checks if the 3-phase voltage is compliant with grid standards.

## link
https://github.com/Abdullah965-eng/Coursework.git

## How to Build
I used **CLion** and **CMake** to build this. 
1. Open the project in CLion.
2. Hit the 'Build' button (the hammer icon).
3. Run the program with the CSV file as an argument.

## Files
* `main.c` - Handles the command line and the main loop.
* `waveform.c/h` - All the math for RMS, Peak-to-Peak, and Clipping.
* `io.c/h` - Loading the CSV and saving the final report.

## Design Choices
* **Structs:** I used a `WaveformSample` struct to keep the CSV data organized so I don't have to pass 8 different arrays around.
* **Memory:** I used `malloc` to allocate the exact amount of space needed for the data after counting the rows in the file. This keeps it efficient.
* **Modular Code:** I split the math and the file I/O into different files to make it easier to debug specific parts.

## Extensions
* **Merit:** Added Standard Deviation to the phase analysis.
* **Distinction:** Implemented bitwise status flags (0x01 for clipping, 0x02 for out-of-tolerance).