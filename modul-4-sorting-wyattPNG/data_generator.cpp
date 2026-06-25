#include "data_generator.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

std::string inputTypeName(InputType type) {
    switch (type) {
        case InputType::RANDOM:         return "Random";
        case InputType::SORTED:         return "Sorted";
        case InputType::REVERSE_SORTED: return "Reverse Sorted";
        case InputType::NEARLY_SORTED:  return "Nearly Sorted";
        case InputType::DUPLICATES:     return "Many Duplicates";
        default:                        return "Unknown";
    }
}

std::vector<int> generateData(int n, InputType type, unsigned int seed) {
    if (n <= 0) throw std::invalid_argument("N harus > 0");

    std::mt19937 rng(seed);
    std::vector<int> data(n);

    switch (type) {

        case InputType::RANDOM: {
            std::uniform_int_distribution<int> dist(1, n * 10);
            for (auto& x : data) x = dist(rng);
            break;
        }

        case InputType::SORTED: {
            std::iota(data.begin(), data.end(), 1);
            break;
        }

        case InputType::REVERSE_SORTED: {
            std::iota(data.begin(), data.end(), 1);
            std::reverse(data.begin(), data.end());
            break;
        }

        case InputType::NEARLY_SORTED: {
            std::iota(data.begin(), data.end(), 1);
            int swaps = std::max(1, n / 20);
            std::uniform_int_distribution<int> idx(0, n - 1);
            for (int i = 0; i < swaps; i++) {
                std::swap(data[idx(rng)], data[idx(rng)]);
            }
            break;
        }

        case InputType::DUPLICATES: {
            int range = std::max(2, n / 10);
            std::uniform_int_distribution<int> dist(1, range);
            for (auto& x : data) x = dist(rng);
            break;
        }
    }

    return data;
}
