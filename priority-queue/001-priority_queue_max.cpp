#include <iostream>
#include <vector>
using namespace std;

class PriorityQueue {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left] > heap[largest]) largest = left;
            if (right < size && heap[right] > heap[largest]) largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else break;
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.empty()) throw runtime_error("Priority Queue is empty!");

        int maxVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return maxVal;
    }

    int peek() const {
        if (heap.empty()) throw runtime_error("Priority Queue is empty!");
        return heap[0];
    }

    bool isEmpty() const {
        return heap.empty();
    }

    void printHeap() const {
        for (int val : heap)
            cout << val << " ";
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;

    pq.insert(10);
    pq.insert(5);
    pq.insert(30);
    pq.insert(20);

    cout << "Max: " << pq.peek() << endl; // 30
    pq.printHeap();

    while (!pq.isEmpty()) {
        cout << "Extracted: " << pq.extractMax() << endl;
    }

    return 0;
}
