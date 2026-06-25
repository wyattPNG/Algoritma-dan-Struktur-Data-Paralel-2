#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "metrics.h"
#include "data_generator.h"
#include "searching_algorithms.h"
#include "reporter.h"


static const std::vector<int> N_VALUES = { 1'000, 10'000, 100'000, 1'000'000 };

static const std::vector<SearchCase> CASES = {
    SearchCase::BEST,
    SearchCase::AVERAGE,
    SearchCase::WORST,
};

static const unsigned int SEED = 42;

using SearchFn = std::function<void(const std::vector<int>&, int, Metrics&)>;

static const std::vector<std::pair<std::string, SearchFn>> ALGORITHMS = {
    { "Linear Search", linear_search },
    { "Binary Search", binary_search },
};

int main() {
    std::cout << "\n";
    std::cout << "=================================================\n";
    std::cout << "      SEARCHING ALGORITHM - ANALYSIS\n";
    std::cout << "=================================================\n";

    for (const auto& [name, searchFn] : ALGORITHMS) {
        std::cout << "\n>> " << name << "\n";
        print_table_header();

        bool is_binary = (name == "Binary Search");

        for (int n : N_VALUES) {
            std::vector<int> data = generate_sorted_data(n);

            for (const auto& sc : CASES) {
                int target = generate_target(data, sc, is_binary, SEED);

                Metrics m;
                m.algorithm_name = name;
                m.input_type     = search_case_name(sc);
                m.n              = n;

                searchFn(data, target, m);
                print_metrics(m);
            }

            print_separator();
        }
    }

    std::cout << "\nDone.\n";
    return 0;
}
