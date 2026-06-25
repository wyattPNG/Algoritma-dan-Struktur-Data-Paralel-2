#include "data_generator.h"
#include <numeric>
#include <random>
#include <stdexcept>


std::string search_case_name(SearchCase sc) {
    switch (sc) {
        case SearchCase::BEST:    return "Best   ";
        case SearchCase::AVERAGE: return "Average";
        case SearchCase::WORST:   return "Worst  ";
        default:                  return "Unknown";
    }
}

std::vector<int> generate_sorted_data(int n) {
    if (n <= 0) throw std::invalid_argument("N harus > 0");
    std::vector<int> data(n);
    std::iota(data.begin(), data.end(), 1);
    return data;
}

int generate_target(const std::vector<int>& data,
                   SearchCase sc,
                   bool is_binary,
                   unsigned int seed)
{
    int n = (int)data.size();

    switch (sc) {
        case SearchCase::BEST:
            return is_binary ? data[n / 2] : data[0];

        case SearchCase::AVERAGE: {
            std::mt19937 rng(seed);
            std::uniform_int_distribution<int> dist(0, n - 1);
            return data[dist(rng)];
        }

        case SearchCase::WORST:
            return data[n - 1] + 9999;

        default:
            return -1;
    }
}
