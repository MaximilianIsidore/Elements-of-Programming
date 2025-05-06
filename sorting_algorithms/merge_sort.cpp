#include <iostream>
#include <vector>
#include <functional> // for std::less
using namespace std;

// Default comparator as a template

bool default_cmp(int a, int b) {
    return a <= b;
}

template <typename Type>
void merge(vector<Type>& arr, int left, int right, int mid, bool (*cmp)(Type, Type)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Type> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (cmp(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename Type>
void merge_sort(vector<Type>& arr, int left, int right, bool (*cmp)(Type, Type)) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid, cmp);
    merge_sort(arr, mid + 1, right, cmp);
    merge(arr, left, right, mid, cmp);
}

template <typename Type>
void merge_sort(vector<Type>& arr, bool (*cmp)(Type, Type) = default_cmp) {
    merge_sort(arr, 0, arr.size() - 1, cmp);
}

bool string_cmp(string a, string b){

    size_t i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        while (i < a.size() && a[i] == ' ') i++;
        while (j < b.size() && b[j] == ' ') j++;

        if (i == a.size() || j == b.size()) break;

        char ca = tolower(a[i]);
        char cb = tolower(b[j]);

        if (ca < cb) return true;
        if (ca > cb) return false;

        i++;
        j++;
    }

    // If characters are equal up to min length, shorter one is "less"
    return a.size() < b.size();
}


int main() {
    vector<int> nums = {8, 20, 2, 1, 4, 19, 7, 11};

    merge_sort(nums); // Default ascending sort

    for (auto num : nums)
        cout << num << " ";
    cout << "\n";

    vector<string> names = {"Liam", "Sophia", "Noah", "Ava", "Ethan", "Isabella", "Mason", "Mia", "Logan", "Charlotte"};

    merge_sort(names, string_cmp);

    for(auto name : names){
        cout<<name << " ";
    }
    cout<<"\n";

    return 0;
}
