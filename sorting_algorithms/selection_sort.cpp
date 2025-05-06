#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

bool default_cmp(int a,int b){
    return (a<b);
}

template <typename Type>
void selection_sort(vector<Type>& arr, bool (*cmp) (Type, Type) = default_cmp ){

    int n = arr.size();

    for(size_t i{}; i<n; i++){
        int min = i;

        for(size_t j{i+1}; j<n; j++){

            if(cmp(arr[j], arr[min])) min = j;
        }

        swap(arr[i], arr[min]);
    }
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
int main(){
    vector<int> nums = {8, 20, 2,1,4,19,7,11};

    selection_sort(nums);

    for(auto num : nums){
        cout<<num<<" ";
    }
    cout<<"\n";

    vector<string> names = {"Liam", "Sophia", "Noah", "Ava", "Ethan", "Isabella", "Mason", "Mia", "Logan", "Charlotte"};

    selection_sort(names, string_cmp);

    for(auto name : names){
        cout<<name << " ";
    }
    cout<<"\n";
    return 0;
}