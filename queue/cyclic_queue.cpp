#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>

using namespace std;

template <typename Type>
class node{

    public:
        Type data;
        node* next{nullptr};
    
        node(Type data): data(data){}
};

template <typename Type>
class cyclic_queue{

    private:
        size_t capacity;
        size_t size{0};
        node<Type>* _front = nullptr;
        node<Type>* _rear = nullptr;
    
    public:

        cyclic_queue(size_t capacity): capacity(capacity){}

        ~cyclic_queue(){
            while(size>0){
                dequeue();
            }
        }

        bool empty(){
            return size == 0;
        }

        bool isFull(){
            return size == capacity;
        }

        void enqueue(Type data){
            node<Type>* new_node = new node(data);

            if(empty()){
                _front = _rear = new_node;
                _rear->next = _front;
            }else if(isFull()){
                node<Type>* temp = _front;
                _front = _front->next;

                delete  temp;

                _rear->next = new_node;
                _rear = new_node;
                _rear->next = _front;
                
            }else{
                _rear->next = new_node;
                _rear = new_node;
                _rear->next = _front;
            }

            if(size<capacity){
                size++;
            }
        }

        void dequeue(){
            if(size>0){

                if(size == 1){
                    delete _front;
                    _front =_rear = nullptr;

                }else{
                     node<Type>* del_node = _front;
                    _front = _front->next;

                    delete del_node;

                    _rear->next = _front;
                }
               
                size --;
            }
        }

        Type front() const{
            assert(size>0);

            return _front->data;
        }
};

int main() {
    cyclic_queue<int> cq(3);
    cq.enqueue(1);
    cq.enqueue(2);
    cq.enqueue(3);
    cout << "Front: " << cq.front() << endl;  // Should be 1

    cq.enqueue(4);  // Overwrites 1
    cout << "Front after overwrite: " << cq.front() << endl; // Should be 2

    cq.dequeue();
    cout << "Front after dequeue: " << cq.front() << endl; // Should be 3

    return 0;
}
