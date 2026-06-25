#include "reporter.h"
#include <iostream>
#include <iomanip>

static const int W_ALG   = 16;
static const int W_INPUT = 16;
static const int W_N     = 8;
static const int W_STAT  = 14;
static const int W_TIME  = 16;

void printTableHeader() {
    std::cout << std::left
              << std::setw(W_ALG)   << "Algorithm"
              << std::setw(W_INPUT) << "Input Type"
              << std::setw(W_N)     << "N"
              << std::setw(W_STAT)  << "Comparisons"
              << std::setw(W_STAT)  << "Swaps"
              << std::setw(W_STAT)  << "Shifts"
              << std::setw(W_STAT)  << "Rec.Calls"
              << std::setw(W_STAT)  << "Arr.Access"
              << std::setw(W_TIME)  << "Time(ms)"
              << "\n";
    std::cout << std::string(W_ALG + W_INPUT + W_N + W_STAT*5 + W_TIME, '-') << "\n";
}

void printMetrics(const Metrics& m) {
    std::cout << std::left
              << std::setw(W_ALG)   << m.algorithm_name
              << std::setw(W_INPUT) << m.input_type
              << std::setw(W_N)     << m.n
              << std::setw(W_STAT)  << m.comparisons
              << std::setw(W_STAT)  << m.swaps
              << std::setw(W_STAT)  << m.shifts
              << std::setw(W_STAT)  << m.recursive_calls
              << std::setw(W_STAT)  << m.array_accesses
              << std::fixed << std::setprecision(6)
              << std::setw(W_TIME)  << m.time_ms
              << "\n";
}