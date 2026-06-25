#pragma once
#include <vector>
#include "metrics.h"

void bubble_sort    (std::vector<int>& data, Metrics& m);
void selection_sort (std::vector<int>& data, Metrics& m);
void insertion_sort (std::vector<int>& data, Metrics& m);
void merge_sort     (std::vector<int>& data, Metrics& m);
void radix_sort     (std::vector<int>& data, Metrics& m);
void quick_sort     (std::vector<int>& data, Metrics& m);
