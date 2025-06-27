#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//used for sorting numbers within a range.
void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    // Step 1: Find min and max values
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    // Step 2: Create count array with offset for negative numbers
    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);

    // Step 3: Count occurrences, shifted by minVal
    for (int num : arr) {
        count[num - minVal]++;
    }

    // Step 4: Reconstruct sorted array
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i]-- > 0) {
            arr[index++] = i + minVal;
        }
    }
}

int main() {
    vector<int> arr = { -5, 3, 0, -2, -5, 8, 3, -1 };

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    countingSort(arr);

    cout << "Sorted array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    return 0;
}
