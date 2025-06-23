#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Struct to hold the result
struct SubarrayResult {
    int low;
    int high;
    int sum;
};

// Find max subarray that crosses the midpoint
SubarrayResult findMaxCrossingSubarray(const vector<int>& arr, int low, int mid, int high) {
    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = mid;

    for (int i = mid; i >= low; --i) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    int maxRight = mid + 1;

    for (int j = mid + 1; j <= high; ++j) {
        sum += arr[j];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = j;
        }
    }

    return {maxLeft, maxRight, leftSum + rightSum};
}

// Recursive function to find maximum subarray
SubarrayResult findMaximumSubarray(const vector<int>& arr, int low, int high) {
    if (low == high) {
        return {low, high, arr[low]}; // base case: one element
    }

    int mid = (low + high) / 2;

    SubarrayResult left = findMaximumSubarray(arr, low, mid);
    SubarrayResult right = findMaximumSubarray(arr, mid + 1, high);
    SubarrayResult cross = findMaxCrossingSubarray(arr, low, mid, high);

    if (left.sum >= right.sum && left.sum >= cross.sum)
        return left;
    else if (right.sum >= left.sum && right.sum >= cross.sum)
        return right;
    else
        return cross;
}

int main() {
    vector<int> arr = {13, -3, -25, 20, -3, -16, -23,
                       18, 20, -7, 12, -5, -22, 15, -4, 7};

    SubarrayResult result = findMaximumSubarray(arr, 0, arr.size() - 1);

    cout << "Maximum Subarray Sum: " << result.sum << endl;
    cout << "Start Index: " << result.low << ", End Index: " << result.high << endl;

    return 0;
}
