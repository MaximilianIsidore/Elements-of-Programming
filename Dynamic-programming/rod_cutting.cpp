#include <complex>
#include<iostream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

int rod_cut_recursive(vector<int>& p, int n ){

    if(n == 0) return 0;

    int max_val = INT_MIN;
    for(int i=1; i<=n; i++){
        max_val = max(max_val, p[i-1]+rod_cut_recursive(p, n-i));
    }

    return max_val;
}

//Memoization (Top-Down)
int rod_cutting_topdown(vector<int>& p, int n, vector<int>& mem){
    if(n==0) return 0;

    if(mem[n] != -1) return mem[n];

    int max_val = INT_MIN;
    for(int i=1; i<=n; i++){
        max_val = max(max_val, p[i-1]+rod_cut_recursive(p, n-i));
    }

    mem[n] = max_val;

    return mem[n];

}

int rod_cutting_topdown(vector<int>& p , int n){
    vector<int> mem(n+1, -1);
    return rod_cutting_topdown(p, n, mem);
}

//Tabulation (Bottom-Up)
int rod_cutting_tab(vector<int>& p, int n){
    vector<int> dp (n+1, 0);

    for(int i=1; i<=n; i++){
        int max_val = INT_MIN;

        for(int j=1; j<=i; j++){
            max_val = max(max_val, p[j-1] + dp[i-j]);
        }

        dp[i] = max_val;
    }

    return dp[n];
}

int main(){
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int n = prices.size();

    auto start1 = high_resolution_clock::now();

    cout<<"From normal recursive solution : "<<rod_cut_recursive(prices, n)<<"\n";

    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1);
    std::cout << "Elapsed: " << duration1.count() << " ms\n";


    auto start2 = high_resolution_clock::now();
    cout<<"From memoization solution : "<<rod_cutting_topdown(prices, n)<<"\n";
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);
    std::cout << "Elapsed: " << duration2.count() << " ms\n";

    auto start3 = high_resolution_clock::now();

    cout<<"From tabulation solution : "<<rod_cutting_tab(prices,  n)<<"\n";

    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(end3 - start3);
    std::cout << "Elapsed: " << duration3.count() << " ms\n";
    
    return 0;
}