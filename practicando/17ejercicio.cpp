/*
Implementar la clase CQueue, con las operaciones push, pop, top.
*/
#include <iostream>

using namespace std;

template <class T>
struct Node {
    Node<T> *next;
    T data;

    Node(T v, Node<T> *p = nullptr) {
        next = p;
        data = v;
    }
};

template <class T>
class CQueue {
public:
    Node<T> *head;
    Node<T> *tail;

    CQueue(): head(nullptr), tail(nullptr){}

    void push(T v){
        Node<T>* newNode = new Node<T>(v);
        if(!head){
            head = newNode;
            tail = newNode;
            newNode->next = nullptr;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool pop() {
        if(!head) return false;
        Node<T> * temp = head;
        if(head == tail){
            head = nullptr;
            tail = nullptr;
        } else{
            head = head->next;
        }
        delete temp;
        return true;
    }

    void print(){
        Node<T> * p = head;
        cout<<"head -> ";
        while(p != nullptr) {
            cout<<p->data<<" -> ";
            p = p->next;
        }
        cout<<"nullptr \n";
    }

};

int main(){

    CQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.pop();
    queue.pop();
    queue.pop();
    queue.pop();
    queue.pop();
    queue.pop();
    queue.push(4);
    queue.push(2);


    queue.print();


    return 0;
}
