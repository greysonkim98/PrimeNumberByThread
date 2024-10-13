# Prim_num_cal

## Overview
`Prim_num_cal` is a C++ program that calculates and displays all prime numbers less than a user-specified input using the maximum number of available threads. The program divides the task of finding prime numbers among multiple threads, making use of concurrent programming for efficiency.

## Program Details
- **Program Name**: Prim_num_cal
- **Programming Language**: C++
- **Developed and Tested OS**: Ubuntu 24.04.1 LTS
- **Tested Compiler**: g++ (Ubuntu 13.2.0-23ubuntu4) 13.2.0
- **Last Updated**: 2024-09-29
- **Author**: Minjae Kim  
  - **Email**: minjaek@csu.fullerton.edu  
  - **CWID**: 885206615  
  - **Class**: CPSC335

## Features
- Efficiently calculates prime numbers less than the user input using multi-threading.
- Dynamically allocates the workload across available CPU threads to speed up execution.
- Implements prime checking for a range of numbers using concurrent threads.

## How to Run
1. **Compilation**:
   Use the following command to compile the program:
   ```bash
   g++ -std=c++11 -pthread -o Prim_num_cal PIDmanager.cpp
   ```
