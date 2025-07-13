#include <iostream>
#include <vector>
using namespace std;

enum ProbingMethod {
    LINEAR,
    QUADRATIC,
    DOUBLE_HASHING
};

class OpenAddressingHashTable {
private:
    vector<int> table;
    vector<bool> occupied;
    int size;
    ProbingMethod method;
    int R; // Used for double hashing

public:
    OpenAddressingHashTable(int s, ProbingMethod m) {
        size = s;
        table.assign(size, -1);
        occupied.assign(size, false);
        method = m;
        R = size - 2; // R should be a prime < size for double hashing
    }

    // Primary hash function
    int h1(int key) {
        return key % size;
    }

    // Secondary hash for double hashing
    int h2(int key) {
        return R - (key % R);  // must not be zero
    }

    // Compute index with selected probing
    int probe(int key, int i) {
        switch (method) {
            case LINEAR:
                return (h1(key) + i) % size;
            case QUADRATIC:
                return (h1(key) + i*i) % size;
            case DOUBLE_HASHING:
                return (h1(key) + i * h2(key)) % size;
        }
        return -1;
    }

    // Insert key
    void insert(int key) {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (!occupied[index]) {
                table[index] = key;
                occupied[index] = true;
                return;
            }
        }
        cout << "Hash table overflow, couldn't insert " << key << endl;
    }

    // Search key
    int search(int key) {
        for (int i = 0; i < size; i++) {
            int index = probe(key, i);
            if (!occupied[index]) return -1; // Not found
            if (table[index] == key) return index;
        }
        return -1; // Not found
    }

    // Display table
    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " --> ";
            if (occupied[i]) cout << table[i];
            else cout << "EMPTY";
            cout << endl;
        }
    }
};

// Driver
int main() {
    // Choose probing method: LINEAR, QUADRATIC, or DOUBLE_HASHING
    ProbingMethod method = DOUBLE_HASHING;

    OpenAddressingHashTable ht(11, method);

    // Insert keys
    int keys[] = {22, 41, 53, 46, 30, 13, 1};
    for (int key : keys)
        ht.insert(key);

    cout << "Hash Table (" 
         << (method == LINEAR ? "Linear" :
             method == QUADRATIC ? "Quadratic" : "Double Hashing")
         << " Probing):\n";
    ht.display();

    // Search for a key
    int keyToFind = 53;
    int index = ht.search(keyToFind);
    if (index != -1)
        cout << "Key " << keyToFind << " found at index " << index << endl;
    else
        cout << "Key " << keyToFind << " not found.\n";

    return 0;
}
