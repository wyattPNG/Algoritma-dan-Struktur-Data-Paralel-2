#include "reporter.h"
#include <iostream>
#include <iomanip>


const int W_ALG   = 16;
const int W_CASE  = 10;
const int W_N     = 10;
const int W_CMP   = 14;
const int W_IDX   = 14;
const int W_TIME  = 16;

void print_separator() {
    std::cout << std::string(W_ALG + W_CASE + W_N + W_CMP + W_IDX + W_TIME, '-') << "\n";
}

void print_table_header() {
    print_separator();
    std::cout << std::left
              << std::setw(W_ALG)  << "Algorithm"
              << std::setw(W_CASE) << "Case"
              << std::setw(W_N)    << "N"
              << std::setw(W_CMP)  << "Comparisons"
              << std::setw(W_IDX)  << "Found Index"
              << std::setw(W_TIME) << "Time(us)"
              << "\n";
    print_separator();
}

void print_metrics(const Metrics& m) {
    std::string found = (m.found_index == -1)
                      ? "Not Found"
                      : std::to_string(m.found_index);

    std::cout << std::left
              << std::setw(W_ALG)  << m.algorithm_name
              << std::setw(W_CASE) << m.input_type
              << std::setw(W_N)    << m.n
              << std::setw(W_CMP)  << m.comparisons
              << std::setw(W_IDX)  << found
              << std::fixed << std::setprecision(3)
              << std::setw(W_TIME) << m.time_us
              << "\n";
}
