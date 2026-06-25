#pragma once
#include <string>
#include <chrono>


struct Metrics {
    std::string algorithm_name;
    std::string input_type;
    int n;

    long long comparisons = 0;
    long long found_index = -1; // -1 for not found

    long double time_us = 0.0;

    void reset() {
        comparisons  = 0;
        found_index  = -1;
        time_us      = 0.0;
    }
};
