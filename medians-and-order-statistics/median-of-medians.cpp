#include <iostream>
#include <vector>
#include <algorithm>  // for sort()
using namespace std;

// Find median of a small group (<=5 elements)
int findMedian(vector<int>& arr, int start, int size) {
    sort(arr.begin() + start, arr.begin() + start + size);
    return arr[start + size / 2];
}

// Partition using given pivot value
int partition(vector<int>& arr, int low, int high, int pivotValue) {
    int pivotIndex;
    for (pivotIndex = low; pivotIndex <= high; ++pivotIndex) {
        if (arr[pivotIndex] == pivotValue)
            break;
    }
    swap(arr[pivotIndex], arr[high]); // move pivot to end

    int i = low;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivotValue) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[high]); // move pivot to correct position
    return i;
}

// Median of Medians selection
int select(vector<int>& arr, int low, int high, int k) {
    int n = high - low + 1;

    // Base case: small array, just sort and return
    if (n <= 5) {
        sort(arr.begin() + low, arr.begin() + high + 1);
        return arr[low + k - 1];
    }

    // Step 1: Divide into groups of 5 and find medians
    vector<int> medians;
    for (int i = 0; i < n / 5; ++i) {
        medians.push_back(findMedian(arr, low + i * 5, 5));
    }

    // Handle leftover group (<5 elements)
    if (n % 5 != 0) {
        medians.push_back(findMedian(arr, low + (n / 5) * 5, n % 5));
    }

    // Step 2: Find median of medians
    int medianOfMedians = select(medians, 0, medians.size() - 1, (medians.size() + 1) / 2);

    // Step 3: Partition using median of medians
    int pivotIndex = partition(arr, low, high, medianOfMedians);
    int rank = pivotIndex - low + 1;

    // Step 4: Recurse accordingly
    if (k == rank)
        return arr[pivotIndex];
    else if (k < rank)
        return select(arr, low, pivotIndex - 1, k);
    else
        return select(arr, pivotIndex + 1, high, k - rank);
}

// Helper function
int kthSmallest(vector<int>& arr, int k) {
    return select(arr, 0, arr.size() - 1, k);
}

int main() {
    vector<int> arr = {12, 3, 5, 7, 4, 19, 26};

    int k = 3;
    cout << "The " << k << "-th smallest element is " << kthSmallest(arr, k) << endl;

    return 0;
}
