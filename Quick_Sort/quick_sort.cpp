#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> sizes = {10000, 50000, 100000, 20000, 60000};
    srand(time(0));

    for (int size : sizes) {
        vector<int> arr(size);
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 100000;
        }

        auto start = high_resolution_clock::now();
        quickSort(arr, 0, size - 1);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Input Size: " << size << " --> Time Taken: " << duration.count() << " ms" << endl;
    }

    return 0;
}