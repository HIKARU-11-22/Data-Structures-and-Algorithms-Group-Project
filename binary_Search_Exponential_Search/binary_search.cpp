#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

// Binary Search Function
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Measure runtime (microseconds) averaged over repeat runs
double measureTime(const vector<int>& arr, int target, int repeat = 10000) {
    auto start = high_resolution_clock::now();
    for (int i = 0; i < repeat; ++i)
        binarySearch(arr, target);
    auto end = high_resolution_clock::now();
    return duration_cast<duration<double, micro>>(end - start).count() / repeat;
}

int main() {
    int n;
    cout << "Enter number of random integers to generate: ";
    cin >> n;

    // Generate random sorted data
    vector<int> data;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100000);

    for (int i = 0; i < n; ++i)
        data.push_back(dist(gen));

    sort(data.begin(), data.end());

    // Display sorted array
    cout << "\nSorted Random Numbers:\n";
    for (int val : data)
        cout << val << " ";
    cout << "\n";

    // Manual Search
    int target;
    cout << "\nEnter number to search: ";
    cin >> target;

    int index = binarySearch(data, target);
    double userTime = measureTime(data, target);

    if (index != -1)
        cout << "Element found at index " << index << " (0-based indexing).\n";
    else
        cout << "Element not found in the array.\n";

    cout << "Time taken (average over 10000 runs): " << userTime << " microseconds.\n";

    // Runtime Analysis
    cout << "\n--- Binary Search Runtime Analysis ---\n";

    int bestTarget = data[n / 2];   // Middle element
    int avgTarget = data[n / 3];    // One-third element
    int worstTarget = 300000;       // Not present

    double bestTime = measureTime(data, bestTarget);
    double avgTime = measureTime(data, avgTarget);
    double worstTime = measureTime(data, worstTarget);

    cout << "Best Case (Middle Element: " << bestTarget << ") - Time: " << bestTime << " microseconds\n";
    cout << "Average Case (Random Element: " << avgTarget << ") - Time: " << avgTime << " microseconds\n";
    cout << "Worst Case (Not Found: " << worstTarget << ") - Time: " << worstTime << " microseconds\n";

    return 0;
}

