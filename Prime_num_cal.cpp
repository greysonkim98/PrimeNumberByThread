//Program name: "Prim_num_cal"                                                                                           
//Copyright (C) 2024 Minjae Kim                 
//                                                                             
//This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License  
//version 3 as published by the Free Software Foundation.                                                                    
//This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied         
//warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.     
//<https://www.gnu.org/licenses/>.
//
//Author information
//  Author name: Minjae Kim
//  Author email: minjaek@csu.fullerton.edu
//  Author CWID: 885206615
//  Author class: CPSC335
//
//Program information
//  Program name: PIDmanager
//  Programming languages: C++
//  Date of last update: 2024-09-29
//  Date of reorganization of comments: 2024-09-29
//  Files in this program: PIDmanager.cpp
//  Developed OS: Ubuntu 24.04.1 LTS
//  Tested OS: Ubuntu 24.04.1 LTS
//  Tested Compiler: g++ (Ubuntu 13.2.0-23ubuntu4) 13.2.0
//
//Program description
//  This program display all prime number less than user input number by using maximum available thread
//
//Reference: https://www.geeksforgeeks.org/command-line-arguments-in-cpp/ 
//           https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/
//           https://www.programiz.com/cpp-programming/examples/prime-number
//*******************************************************************************************************************************

#include <iostream>
#include <thread>
#include <vector>

// Global vector to store prime numbers
std::vector<int> all_primes;

// Checking prime number
bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Finding prime number in the vector
void find_primes(int start, int end, std::vector<int>& list) {
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            list.push_back(i);
        }
    }
}

int main(int argc, char *argv[]) {
    // Obtaining user input from command line
    if (argc != 2) {
        std::cerr << "Please enter number after command line.\n " << std::endl;
        return 1;
    }
    int max = std::stoi(argv[1]);
    if (max <2) {
        std::cerr << "There is no prime number less than 2." << std::endl;
        return 1;
    }
    
    // Obtain number of availble threads
    int num_threads = std::thread::hardware_concurrency();
    if (num_threads < 1) {
        std::cerr << "Not enough cores\n";
        return 1;
    }
    std::cout << "The number of threads: " << num_threads <<std::endl;

    // Allocate a chunk of number to each thread to work
    int chunk_size = max / num_threads;
    int remainder = max % num_threads;

    std::vector<std::thread> threads(num_threads);
    std::vector<std::vector<int>> prime_arrays(num_threads);

    for (int i = 0; i < num_threads; i++) {
        int start = i * chunk_size + 1;
        int end = (i + 1) * chunk_size;
        if (i == num_threads - 1) {
            end = max;
        }
        threads[i] = std::thread(find_primes, start, end, std::ref(prime_arrays[i]));
        std::cout << "Thread(" << i+1 << ") assigned number from " << start << " to " << end << std::endl;
    }

    // Thread working
    for (auto& thread : threads) {
        thread.join();
    }

    // Insert prime number which each thread local vector containning into global variable 'all_prime'
    all_primes.reserve(max);
    for (const auto& thread_primes : prime_arrays) {
        all_primes.insert(all_primes.end(), thread_primes.begin(), thread_primes.end());
    }

    // Print the prime numbers
    std::cout << "Prime numbers less than or equal to " << max << ":" << std::endl;
    for (auto prime : all_primes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}
