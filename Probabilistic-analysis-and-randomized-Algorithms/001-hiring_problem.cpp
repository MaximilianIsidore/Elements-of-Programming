#include <iostream>
#include <vector>
#include <algorithm> // for shuffle
#include <random>    // for random device and generator

int simulate_hiring(int n, std::mt19937 &gen) {
    std::vector<int> candidates(n);
    
    // Fill candidates with values 1 to n (where 1 = best)
    for (int i = 0; i < n; ++i) {
        candidates[i] = i + 1;
    }

    // Shuffle to simulate random arrival order
    std::shuffle(candidates.begin(), candidates.end(), gen);

    int best_so_far = n + 1; // no one interviewed yet, so set higher than any possible rank
    int hires = 0;

    // Interview each candidate
    for (int i = 0; i < n; ++i) {
        int rank = candidates[i];

        // If candidate is better (lower rank) than all before, hire them
        if (rank < best_so_far) { // this is the analysis part of the interview , on avg it takes log(n) time
            hires++;              //we hire and replace the old assitant with new one
            best_so_far = rank;
        }
    }

    return hires;
}

int main() {
    int n = 100;         // Number of candidates
    int trials = 10000;  // Run simulation multiple times for expected value

    std::random_device rd;
    std::mt19937 gen(rd());

    long long total_hires = 0;

    for (int i = 0; i < trials; ++i) {
        total_hires += simulate_hiring(n, gen);
    }

    double expected_hires = static_cast<double>(total_hires) / trials;

    std::cout << "Expected number of hires for " << n << " candidates over "
              << trials << " trials: " << expected_hires << std::endl;

    return 0;
}
