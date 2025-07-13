#include <iostream>
#include <list>
using namespace std;

class HashTable {
private:
    int BUCKET;               // Number of buckets
    list<int>* table;         // Array of lists (chaining)

public:
    // Constructor
    HashTable(int b) {
        BUCKET = b;
        table = new list<int>[BUCKET];
    }

    // Hash function
    int hashFunction(int key) {
        return key % BUCKET;
    }

    // Insert key into hash table
    void insertItem(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    // Delete key from hash table
    void deleteItem(int key) {
        int index = hashFunction(key);
        // Find the key in the list and delete it
        table[index].remove(key);
    }

    // Display hash table
    void displayHash() {
        for (int i = 0; i < BUCKET; i++) {
            cout << i << " --> ";
            for (auto x : table[i])
                cout << x << " ";
            cout << endl;
        }
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }
};

// Driver code
int main() {
    // Create a hash table with 7 buckets
    HashTable h(7);

    // Insert some keys
    int keys[] = {15, 11, 27, 8, 12};
    for (int key : keys)
        h.insertItem(key);

    cout << "Initial hash table:\n";
    h.displayHash();

    // Delete a key
    h.deleteItem(12);

    cout << "\nAfter deleting 12:\n";
    h.displayHash();

    return 0;
}
