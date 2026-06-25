#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "metrics.h"
#include "data_generator.h"
#include "sorting_algorithms.h"
#include "reporter.h"

static const std::vector<int> N_VALUES = { 100, 1'000, 10'000 };

static const std::vector<InputType> INPUT_TYPES = {
    InputType::RANDOM,
    InputType::SORTED,
    InputType::REVERSE_SORTED,
    InputType::NEARLY_SORTED,
    InputType::DUPLICATES,
};

static const unsigned int SEED = 42;
using SortFn = std::function<void(std::vector<int>&, Metrics&)>;

static const std::vector<std::pair<std::string, SortFn>> ALGORITHMS = {
    { "Bubble Sort",    bubble_sort    },
    { "Selection Sort", selection_sort },
    { "Insertion Sort", insertion_sort },
    { "Merge Sort",     merge_sort     },
    { "Quick Sort",     quick_sort     },
    { "Radix Sort",     radix_sort     },
};


int main() {
    std::cout << "=================================================\n";
    std::cout << "      SORTING ALGORITHM - ANALYSIS\n";
    std::cout << "=================================================\n";

    for (const auto& [name, sortFn] : ALGORITHMS) {
        std::cout << "\n>> " << name << "\n";
        printTableHeader();

        for (int n : N_VALUES) {
            for (const auto& inputType : INPUT_TYPES) {
                std::vector<int> data = generateData(n, inputType, SEED);

                Metrics m;
                m.algorithm_name = name;
                m.input_type     = inputTypeName(inputType);
                m.n              = n;

                sortFn(data, m);
                printMetrics(m);
            }
        }
    }

    std::cout << "\nDone.\n";
    return 0;
}