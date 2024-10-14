/*
Implementar la clase CStack, utilizando el concepto de adaptors,
con las operaciones push, pop, top.

*/
#include <iostream>

using namespace std;

template <class T>
struct Node {
    Node<T> * next;
    T data;

    Node(T v, Node<T> *p = nullptr) {
        next = p;
        data = v;
    }
};

template <class T>
class CStack {
    Node<T> * top;
public:

    CStack() : top(nullptr) {}

    void push(T v) {
        top = new Node<T>(v, top);
    }

    bool pop() {
        if(!top) return false;
        Node<T> *temp = top;
        top = top->next;
        delete temp;
        return true;
    }

    void print(){
        Node<T> *p = top;
        cout<<"top -> ";
        while(p != nullptr) {
            cout<<p->data<<" -> ";
            p=p->next;
        }
        cout<<"nullptr\n";
    }
};


int main() {

    CStack<int> stack;

    stack.push(4);
    stack.push(2);
    stack.push(1);


    stack.print();


    return 0;
}
