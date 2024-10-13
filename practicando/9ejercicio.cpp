/*
Implementar la clase CForwardList, que es una lista simplemente enlazada,
con las operaciones push_front, push_back, pop_front, pop_back, operator[].
*/
#include <exception>
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
struct Node {
    Node<T> *next;
    T data;
    Node(T v, Node<T> *n = nullptr){
        data = v;
        next = n;
    }
};

template <class T>
class CList {
public:
    Node<T> *head;
    int len = 0;
    CList() : head(nullptr) {}

    T operator[](int index){
        if(index >= len){
            throw out_of_range("Index out of range");
        }
        Node<T> *p = head;
        for(int i = 0; i < index; i++){
            p = p->next;
        }
        return p->data;
    }

    void push_front(T v){
        if(!head){
            head = new Node<T>(v, head);
            len++;
            return;
        }
        Node<T> *p = new Node<T>(v, head);
        head = p;
        len++;
    }

    void push_back(T v){
        if(!head){
            head = new Node<T>(v, head);
            len++;
            return;
        }
        Node<T> *p = head;
        for(; p->next != nullptr; p=p->next);
        p->next = new Node<T>(v);
        len++;
    }

    void pop_front(){
        if(!head) return;
        Node<T> *temp = head;
        head = head->next;
        delete temp;
        len--;
    }

    void pop_back(){
        if(!head) return;
        Node<T> *p = head;
        if(p->next == nullptr){
            head = nullptr;
            len--;
            return;
        }
        for(; p->next->next != nullptr; p=p->next);
        p->next = nullptr;
        delete p->next;
        len--;
    }


    void print() {
        Node<T> *p = head;
        cout<<"head -> ";
        while(p != nullptr) {
            cout<<p->data<<" -> ";
            p=p->next;
        }
        cout<<"nullptr\n";
    }

};


int main (){

    CList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.print();
    list.push_back(3);
    list.push_back(4);
    list.push_back(6);
    list.push_back(7);
    list.print();
    list.pop_front();
    list.pop_front();
    list.print();
    list.pop_back();
    list.pop_back();
    list.pop_back();

    list.push_back(3);
    list.push_back(4);
    list.push_back(6);
    list.push_back(7);
    list.print();
    cout<<"len: "<<list.len<<"\n";
    int x = list[0];
    cout<<"X: "<<x<<"\n";


  return 0;
}
