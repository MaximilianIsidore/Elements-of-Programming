#include <cassert>
#include <cstddef>
#include <iostream>

using namespace std;

template <typename Type>
class node{
    public:
        Type data;
        node* next{nullptr};
        node* prev{nullptr};

        node(Type data): data(data){}
};

template <typename Type>
class dequeue{

    private:
        size_t size{0};
        node<Type>* _front {nullptr};
        node<Type>* _back {nullptr};
    
    public:
        dequeue() = default;

        ~dequeue(){
            while(size>0){
                deleteFront();
            }
        }

        void insertFront(Type data){

            node<Type>* new_node = new node(data);

            if(_front == nullptr){
                _front = _back = new_node;
            }else{
                new_node->prev = _front;
                _front->next = new_node;
                _front = new_node;
            }

            size++;
        }

        void insertBack(Type data){
            node<Type>* new_node = new node(data);

            if(_back == nullptr){
                _front = _back = new_node;
            }else{
                new_node->next = _back;
                _back->prev = new_node;
                _back = new_node;
            }

            size++;
        }

        void deleteFront(){
            if(size>0){
                node<Type>* del_node = _front;
                _front = _front->prev;
                delete  del_node;

                
                if(_front) _front -> next = nullptr;
                else _front = _back = nullptr;

                size--;
            }
        }

        void deleteBack(){
            if(size>0){
                node<Type>* del_node = _back;
                _back = _back->next;
                delete del_node;

                if(_back) _back ->prev = nullptr;
                else _front = _back = nullptr;

                size--;
                
            }
        }

        Type front() const{
            assert(size>0);

            return _front->data;
        }

        Type back() const{
            assert(size>0);

            return _back->data;
        }

        bool empty() const{
            return size == 0;
        }

        size_t length() const{
            return size;
        }

};

int main(){
    dequeue<int> dq;

    dq.insertFront(10);
    dq.insertBack(20);
    dq.insertFront(5);
    dq.insertBack(30);

    // Expected order (front to back): 5, 10, 20, 30
    cout << "Front: " << dq.front() << endl; // 5
    cout << "Back: " << dq.back() << endl;   // 30
    cout << "Length: " << dq.length() << endl; // 4

    dq.deleteFront();  // removes 5
    dq.deleteBack();   // removes 30

    // Remaining: 10, 20
    cout << "Front: " << dq.front() << endl; // 10
    cout << "Back: " << dq.back() << endl;   // 20
    cout << "Length: " << dq.length() << endl; // 2

    dq.deleteFront(); // removes 10
    dq.deleteBack();  // removes 20

    cout << "Empty? " << dq.empty() << endl; // 1 (true)




    dequeue<string> dq2;
    dq2.insertBack("A");
    dq2.insertBack("B");
    dq2.deleteBack(); // removes A
    dq2.insertFront("C");
    dq2.insertBack("D");

    // Should now be: C, B, D
    cout << "Front: " << dq2.front() << endl; // C
    cout << "Back: " << dq2.back() << endl;   // D


    return 0;
}