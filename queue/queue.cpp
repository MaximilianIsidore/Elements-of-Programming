#include <cassert>
#include <cstddef>
#include <iostream>

using namespace std;

template <typename Type>
class node{
    public:
        Type data;
        node* next = nullptr;
        node* back = nullptr;

        node(Type data): data(data){}
};

template <typename Type>
class queue{

    private:
        size_t size{0};
        node<Type>* _front = nullptr;
        node<Type>* _back = nullptr;

    public:
        queue() = default;

        ~queue(){

            while(size>0){
                pop();
            }
        }

        void push(Type data){
            node<Type>* new_node = new node(data);

            if(_front == nullptr){
                _front = _back = new_node;
            }else{
                _back->next = new_node;
                new_node->back = _back;
                _back = new_node;
            }

            size++;
        }

        void pop(){

            if(size>0){
                node<Type>* del_node = _front;

                _front = _front->next;

                if(_front) _front->back == nullptr;
                else _back = nullptr;

                delete del_node;
                size--;
            }
        }

        Type front(){
            assert(size>0);

            return _front->data;
        }

        bool empty() const{

            return size == 0;
        }

        size_t length() const{

            return size;
        }
};

int main() {
    queue<string> q;

    q.push("one");
    q.push("two");
    q.push("three");

    cout << "Front: " << q.front() << endl; // Should print "one"
    q.pop();

    cout << "Front after pop: " << q.front() << endl; // Should print "two"
    cout << "Queue size: " << q.length() << endl;

    return 0;
}
