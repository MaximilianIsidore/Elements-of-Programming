#include <cassert>
#include <cstddef>
#include <iostream>

using namespace std;

template <typename Type>
class node {
public:
    Type data;
    node* next = nullptr;
    node* back = nullptr;

    node(Type data) : data(data) {}
};

template <typename Type>
class stack {
private:
    size_t size {0};
    node<Type>* _head = nullptr;
    node<Type>* _top = nullptr;

public:
    stack() = default;

    ~stack() {
        while (size > 0) {
            pop();
        }
    }

    void push(Type data) {
        node<Type>* new_node = new node<Type>(data);
        if (_head == nullptr) {
            _head = _top = new_node;
        } else {
            _top->next = new_node;
            new_node->back = _top;
            _top = new_node;
        }
        size++;
    }

    void pop() {
        if (size == 0) return;

        node<Type>* del_node = _top;
        _top = _top->back;

        if (_top) _top->next = nullptr;
        else _head = nullptr;

        delete del_node;
        size--;
    }

    Type back() {
        assert(size > 0);
        return _top->data;
    }

    bool empty() const {
        return size == 0;
    }

    size_t length() const {
        return size;
    }
};


int main(){
    stack<int> intStack;

    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    cout << "Top: " << intStack.back() << endl; // Should print 30

    intStack.pop();
    cout << "Top after pop: " << intStack.back() << endl; // Should print 20

    stack<string> strStack;

    strStack.push("hello");
    strStack.push("world");
    strStack.push("C++");

    cout << "Top: " << strStack.back() << endl; // Should print "C++"

    strStack.pop();
    cout << "Top after pop: " << strStack.back() << endl; // Should print "world"


    return 0;
}