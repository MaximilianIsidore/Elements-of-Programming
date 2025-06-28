#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Get maximum value in array
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// Stable Counting Sort by digit
void countingSortByDigit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0);

    // Count occurrences by current digit
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Build cumulative count
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build output array (stable)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    // Copy sorted values back to original array
    arr = output;
}

// Radix Sort
void radixSort(vector<int>& arr) {
    int maxVal = getMax(arr);
    
    // Apply counting sort to each digit (1, 10, 100, ...)
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortByDigit(arr, exp);
}

int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    radixSort(arr);

    cout << "Sorted array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    return 0;
}
