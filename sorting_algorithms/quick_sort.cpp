#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool default_cmp(int a, int b){
    return a<=b;
}

template <typename Type>
int partition(vector<Type>& arr,int low, int high, bool (*cmp)(Type, Type)){

    Type pivot = arr[low];
    int i = low+1;
    int j = high;

    while(i<j){

        while(i<high && cmp(arr[i], pivot)) i++;
        while(j>low && !cmp(arr[j], pivot)) j--;

        if(i<j) swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);

    return j;
}

template <typename Type>
void quick_sort(vector<Type>& arr,int low, int high, bool (*cmp)(Type, Type) = default_cmp){

    if(low < high){
        int p_idx = partition(arr, low, high, cmp);

        quick_sort(arr, low, p_idx-1, cmp );
        quick_sort(arr, p_idx+1, high, cmp);
    }
}

template <typename Type>
void quick_sort(vector<Type>& arr, bool (*cmp)(Type, Type) = default_cmp){

    quick_sort(arr, 0, arr.size()-1, cmp);
}

bool string_cmp(string a, string b){

    size_t i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        while (i < a.size() && a[i] == ' ') i++;
        while (j < b.size() && b[j] == ' ') j++;

        if (i == a.size() || j == b.size()) break;

        char ca = tolower(a[i]);
        char cb = tolower(b[j]);

        if (ca <= cb) return true;
        if (ca > cb) return false;

        i++;
        j++;
    }

    // If characters are equal up to min length, shorter one is "less"
    return a.size() <= b.size();
}

int main(){

    vector<int> nums = {8, 20, 2, 1, 4, 19, 7, 11};

    quick_sort(nums); // Default ascending sort

    for (auto num : nums)
        cout << num << " ";
    cout << "\n";

    vector<string> names = {"Liam", "Sophia", "Noah", "Ava", "Ethan", "Isabella", "Mason", "Mia", "Logan", "Charlotte"};

    quick_sort(names, string_cmp);

    for(auto name : names){
        cout<<name << " ";
    }
    cout<<"\n";
    return 0;
}