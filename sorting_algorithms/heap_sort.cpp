#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left<n && arr[left] > arr[largest])
        largest = left;

    if(right<n && arr[right] > arr[largest])
        largest = right;

    if(largest != i){
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to build a max-heap
void buildMaxHeap(vector<int>& arr, int n) {
    // Start from last non-leaf node and heapify each
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

// Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    buildMaxHeap(arr, n);

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);      // Move current root to end
        heapify(arr, i, 0);        // Heapify reduced heap
    }
}

// Helper function to print the array
void printArray(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

// Main function
int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};

    cout << "Original array: ";
    printArray(arr);

    heapSort(arr);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}