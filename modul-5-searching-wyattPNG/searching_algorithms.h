#pragma once
#include <vector>
#include "metrics.h"


void linear_search(const std::vector<int>& data, int target, Metrics& m);
void binary_search(const std::vector<int>& data, int target, Metrics& m);
