#include <iostream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

class HashTable {
private:
    int BUCKET;
    list<int>* table;

    // Constants for Universal Hashing
    int p = 10000019;  // A large prime
    int a, b;

    // Constant for Multiplication Method
    const float A = 0.618033f; // ≈ (√5 - 1)/2

public:
    enum HashType { DIVISION, MULTIPLICATION, UNIVERSAL };
    HashType hashType;

    HashTable(int bucketSize, HashType ht) {
        BUCKET = bucketSize;
        table = new list<int>[BUCKET];
        hashType = ht;
        srand(time(0));  // Seed for randomness

        // Random a, b for Universal Hashing
        a = 1 + rand() % (p - 1);
        b = rand() % p;
    }

    // Division Method
    int hash_division(int key) {
        return key % BUCKET;
    }

    // Multiplication Method
    int hash_multiplication(int key) {
        float frac = fmod(key * A, 1.0);
        return int(BUCKET * frac);
    }

    // Universal Hashing Method
    int hash_universal(int key) {
        return ((a * key + b) % p) % BUCKET;
    }

    // General hash function dispatcher
    int hashFunction(int key) {
        switch (hashType) {
            case DIVISION: return hash_division(key);
            case MULTIPLICATION: return hash_multiplication(key);
            case UNIVERSAL: return hash_universal(key);
        }
        return -1; // fallback
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    void display() {
        for (int i = 0; i < BUCKET; ++i) {
            cout << i << " --> ";
            for (auto x : table[i])
                cout << x << " ";
            cout << endl;
        }
    }

    ~HashTable() {
        delete[] table;
    }
};

int main() {
    int keys[] = {123, 432, 213, 654, 952, 341, 222};

    // Choose a hash method here
    HashTable::HashType method = HashTable::UNIVERSAL;

    // Create table
    HashTable ht(7, method);

    // Insert keys
    for (int key : keys)
        ht.insert(key);

    // Display table
    cout << "Hash Table (" << (method == HashTable::DIVISION ? "Division" :
                                method == HashTable::MULTIPLICATION ? "Multiplication" : "Universal")
         << " method):\n";
    ht.display();

    return 0;
}
