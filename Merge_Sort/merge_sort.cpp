#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
using namespace std;
using namespace chrono;
void generateRandomNumbers(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;   
    int leftArr[n1], rightArr[n2];
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
int main() {
    int n;
    cout << "Enter the number of random integers to generate: ";
    cin >> n;   
    if (n <= 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }
    int arr[n];
    generateRandomNumbers(arr, n);
    cout << "Generated numbers: ";
    displayArray(arr, n);
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();
    cout << "Sorted array: ";
    displayArray(arr, n);
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Time taken by merge sort: " << duration.count() << " microseconds" << endl;
    return 0;
}