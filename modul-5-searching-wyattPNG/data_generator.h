#pragma once
#include <vector>
#include <string>


enum class SearchCase {
    BEST,
    AVERAGE,
    WORST
};

std::string search_case_name(SearchCase sc);

std::vector<int> generate_sorted_data(int n);

int generate_target(const std::vector<int>& data,
                   SearchCase sc,
                   bool is_binary,
                   unsigned int seed = 42);
