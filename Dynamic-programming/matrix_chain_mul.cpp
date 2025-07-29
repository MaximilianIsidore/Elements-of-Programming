#include <climits>
#include<iostream>
#include<vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int matrix_chain_recursive(vector<int>& p, int i, int j){

    if(i==j) return 0;

    int min_cost = INT_MAX;

    for(int k=i; k<j; k++){

        int cost = matrix_chain_recursive(p, i, k) +
                   matrix_chain_recursive(p, k + 1, j) +
                   p[i - 1] * p[k] * p[j];

        min_cost = min(min_cost, cost);
    }

    return min_cost;
}

int matrix_chain_tab(vector<int>& p){

    int n = p.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int len=2; len<n; len++){

        for(int i=1; i<(n-len + 1); i++){

            int j = i + len-1;
            dp[i][j] = INT_MAX;

            for(int k=i; k<j; k++){

                int cost = dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j];
                dp[i][j] = min(cost, dp[i][j]);
            }
        }
    }

    return dp[1][n-1];

}

int main(){

    vector<int> p ={10, 20, 30, 40, 30, 20, 10, 50, 60, 20, 30};

    auto start1 = high_resolution_clock::now();

    cout<<"From normal recursive solution : "<<matrix_chain_recursive(p,1, p.size()-1)<<"\n";

    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1);
    std::cout << "Elapsed: " << duration1.count() << " ms\n";

    auto start2 = high_resolution_clock::now();

    cout<<"From tabulation solution : "<<matrix_chain_tab(p)<<"\n";

    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);
    std::cout << "Elapsed: " << duration2.count() << " ms\n";
    


    return 0;
}