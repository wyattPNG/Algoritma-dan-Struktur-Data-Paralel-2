#pragma once
#include <string>
#include <chrono>

struct Metrics {
    std::string algorithm_name;
    std::string input_type;
    int n;

    long long comparisons    = 0;
    long long swaps          = 0;
    long long shifts         = 0;   // for insertion sort
    long long recursive_calls = 0;  // for merge sort & quick sort
    long long array_accesses = 0;   // for counting sort & radix sort

    long double time_ms = 0.0;

    void reset() {
        comparisons     = 0;
        swaps           = 0;
        shifts          = 0;
        recursive_calls = 0;
        array_accesses  = 0;
        time_ms         = 0.0;
    }
};
