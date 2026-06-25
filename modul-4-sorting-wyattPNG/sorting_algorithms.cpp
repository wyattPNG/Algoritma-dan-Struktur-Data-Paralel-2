#include "sorting_algorithms.h"
#include <algorithm>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;

void bubble_sort(std::vector<int>& data, Metrics& m) {
    int n = data.size();
    auto start = Clock::now();

    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            m.comparisons++;
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
                m.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    m.time_ms = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

void selection_sort(std::vector<int>& data, Metrics& m) {
    int n = data.size();
    auto start = Clock::now();

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            m.comparisons++;
            if (data[j] < data[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(data[i], data[min_idx]);
            m.swaps++;
        }
    }

    m.time_ms = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

void insertion_sort(std::vector<int>& data, Metrics& m) {
    int n = data.size();
    auto start = Clock::now();

    for (int i = 1; i < n; ++i) {
        int key = data[i];
        int j = i - 1;

        while (j >= 0) {
            m.comparisons++;
            if (data[j] > key) {
                data[j + 1] = data[j];
                m.shifts++;
                --j;
            } else {
                break;
            }
        }
        
        if (j + 1 != i) {
            data[j + 1] = key;
            m.shifts++; 
        }
    }

    m.time_ms = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

void merge(std::vector<int>& data, int left, int mid, int right, std::vector<int>& temp, Metrics& m) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        m.comparisons++;
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = data[i++];
    }
    while (j <= right) {
        temp[k++] = data[j++];
    }

    for (int p = left; p <= right; ++p) {
        data[p] = temp[p];
    }
}

void merge_sort_helper(std::vector<int>& data, int left, int right, std::vector<int>& temp, Metrics& m) {
    m.recursive_calls++;
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    merge_sort_helper(data, left, mid, temp, m);
    merge_sort_helper(data, mid + 1, right, temp, m);
    merge(data, left, mid, right, temp, m);
}

void merge_sort(std::vector<int>& data, Metrics& m) {
    auto start = Clock::now();

    if (!data.empty()) {
        std::vector<int> temp(data.size());
        merge_sort_helper(data, 0, data.size() - 1, temp, m);
    }

    m.time_ms = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

int partition(std::vector<int>& data, int low, int high, Metrics& m) {
    int pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        m.comparisons++;
        if (data[j] < pivot) {
            ++i;
            std::swap(data[i], data[j]);
            m.swaps++;
        }
    }
    std::swap(data[i + 1], data[high]);
    m.swaps++;
    return i + 1;
}

void quick_sort_helper(std::vector<int>& data, int low, int high, Metrics& m) {
    m.recursive_calls++;
    if (low < high) {
        int pi = partition(data, low, high, m);
        quick_sort_helper(data, low, pi - 1, m);
        quick_sort_helper(data, pi + 1, high, m);
    }
}

void quick_sort(std::vector<int>& data, Metrics& m) {
    auto start = Clock::now();

    if (!data.empty()) {
        quick_sort_helper(data, 0, data.size() - 1, m);
    }

    m.time_ms = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

void radix_sort(std::vector<int>& data, Metrics& m) {
    if (data.empty()) return;
    auto start = Clock::now();

    int n = data.size();
    
    int max_val = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }

    std::vector<int> output(n);

    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        int count[10] = {0};

        for (int i = 0; i < n; ++i) {
            int digit = (data[i] / exp) % 10;
            count[digit]++;
            m.array_accesses++;
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
            m.array_accesses += 2;
        }

        for (int i = n - 1; i >= 0; --i) {
            int digit = (data[i] / exp) % 10;
            output[count[digit] - 1] = data[i];
            m.array_accesses += 2;
            
            count[digit]--;
            m.array_accesses++;
        }

        for (int i = 0; i < n; ++i) {
            data[i] = output[i];
            m.array_accesses++;
        }
    }

    m.time_ms = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}