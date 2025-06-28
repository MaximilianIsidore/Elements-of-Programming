#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//for floats in range [0, 1)
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 0) return;

    // Step 1: Create empty buckets
    vector<vector<float>> buckets(n);

    // Step 2: Put elements into buckets
    for (int i = 0; i < n; i++) {
        int index = n * arr[i]; // index in range 0 to n-1
        buckets[index].push_back(arr[i]);
    }

    // Step 3: Sort each bucket
    for (int i = 0; i < n; i++) {
        sort(buckets[i].begin(), buckets[i].end());
    }

    // Step 4: Concatenate all buckets into original array
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (float val : buckets[i]) {
            arr[idx++] = val;
        }
    }
}

int main() {
    vector<float> arr = {0.25, 0.36, 0.58, 0.41, 0.29, 0.22, 0.99};

    cout << "Original array:\n";
    for (float num : arr) cout << num << " ";
    cout << "\n";

    bucketSort(arr);

    cout << "Sorted array:\n";
    for (float num : arr) cout << num << " ";
    cout << "\n";

    return 0;
}
