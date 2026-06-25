#pragma once
#include <vector>
#include <string>

enum class InputType {
    RANDOM,
    SORTED,
    REVERSE_SORTED,
    NEARLY_SORTED,
    DUPLICATES
};

std::string inputTypeName(InputType type);

std::vector<int> generateData(int n, InputType type, unsigned int seed = 42);
