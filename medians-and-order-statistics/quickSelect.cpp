#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
using namespace std;

// Partition like in Quicksort: arr[p..r]
// It returns the index of the pivot after partitioning
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // choose last element as pivot
    int i = low; // index of smaller element

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high]); // move pivot to correct position
    return i;
}

// Quickselect function
int quickselect(vector<int>& arr, int low, int high, int k) {
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    int order = pivotIndex - low + 1; // position of pivot in current subarray

    if (k == order)
        return arr[pivotIndex];
    else if (k < order)
        return quickselect(arr, low, pivotIndex - 1, k);
    else
        return quickselect(arr, pivotIndex + 1, high, k - order);
}

// Helper to use quickselect
int kthSmallest(vector<int>& arr, int k) {
    return quickselect(arr, 0, arr.size() - 1, k);
}

int main() {
    vector<int> arr = {7, 10, 4, 3, 20, 15};

    int k = 3;
    cout << "The " << k << "-th smallest element is " << kthSmallest(arr, k) << endl;

    return 0;
}
