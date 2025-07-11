#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int binarySearch(const vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        arr[mid] < target ? left = mid + 1 : right = mid - 1;
    }
    return -1;
}

int exponentialSearch(const vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < arr.size() && arr[i] <= target) i *= 2;
    return binarySearch(arr, i/2, min(i, (int)arr.size()-1), target);
}

int main() {
    int N, choice;
    
    cout << "Enter number of elements (recommend >= 10000): ";
    cin >> N;
    
    vector<int> arr(N);
    
    cout << "Choose input type:\n";
    cout << "1. Random Input\n";
    cout << "2. Manual Input\n";
    cout << "Choice (1/2): ";
    cin >> choice;
    
    if (choice == 1) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, N*10);
        for (int i = 0; i < N; i++) {
            arr[i] = dist(gen);
        }
    } 
    else if (choice == 2) {
        cout << "\nEnter " << N << " elements:\n";
        for (int i = 0; i < N; i++) {
            cout << "Element " << i+1 << ": ";
            cin >> arr[i];
        }
    } 
    else {
        cout << "Invalid choice";
        return 1;
    }
    
    sort(arr.begin(), arr.end());

    // Test cases
    const int targets[] = {
        arr[0],         // Best case
        arr[N/2],       // Average case
        arr.back(),     // Worst case
        -1              // Not found case
    };
    const char* cases[] = {"Best", "Average", "Worst", "Not Found"};

    // Measurement approach that guarantees non-zero times
    auto measure = [&](const string& name, int target) {
        const int batch_size = 10000; // Measure batches of operations
        volatile int dummy = 0; // Prevent optimization
        
        // Warm-up
        for (int i = 0; i < 1000; i++) {
            dummy += exponentialSearch(arr, target);
        }

        // Measure multiple batches
        int batches = 0;
        double total_ns = 0;
        
        auto start = high_resolution_clock::now();
        do {
            for (int i = 0; i < batch_size; i++) {
                dummy += exponentialSearch(arr, target);
            }
            batches++;
            auto end = high_resolution_clock::now();
            total_ns = duration_cast<nanoseconds>(end-start).count();
        } while (total_ns < 1000000); // Run until we have at least 1ms of data

        double avg_ns = total_ns / (batches * batch_size);
        cout << "| " << setw(12) << name << " | " 
             << setw(10) << fixed << setprecision(2) << avg_ns << " ns |\n";
    };

    cout << "\n=== Exponential Search Performance (N=" << N << ") ===\n";
    cout << "+--------------+------------+\n";
    cout << "| Case         | Time       |\n";
    cout << "+--------------+------------+\n";
    for (int i = 0; i < 4; i++) {
        measure(cases[i], targets[i]);
    }
    cout << "+--------------+------------+\n";

    return 0;
}