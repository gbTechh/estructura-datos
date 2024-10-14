/*
Implementar la clase CList, que es una lista doblemente enlazada,
con las operaciones push_front, push_back, pop_front, pop_back, operator[].
*/
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(T v, Node<T>*p = nullptr, Node<T>*n = nullptr){
        data = v;
        prev = p;
        next = n;
    }
};

template <class T>
class CList {
public:
    Node<T> * head;
    Node<T> * tail;
    int len = 0;

    CList () : head(nullptr), tail(nullptr) {}

    T& operator[](int index){
        if(index >= len) {
            throw out_of_range("Indice fuera del rango");
        }
        Node<T> *p = head;
        for(int i = 0; i < index; i++){
            p = p->next;
        };
        cout<<"p data: "<<p->data<<"\n";
        return p->data;
    }

    void push_front(T v) {
        Node<T> *newNode = new Node<T>(v);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else{
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        len++;
    }

    void push_back(T v){
        Node<T> *newNode = new Node<T>(v);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        len++;
    }

    void pop_front(){
        if(!head) return;
        Node<T> *temp = head;
        if(head == tail){
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        len--;
    }

    void pop_back(){
        if(!head) return;
        Node<T> *temp = tail;
        if(head == tail){
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        len--;
    }

    void print() {
        Node<T> *p = head;
        cout<<"head <-> ";
        while(p !=nullptr){
            cout<<p->data<<" <-> ";
            p = p->next;
        }
        cout<<"nullptr\n";
    }


};

int main(){

    CList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.pop_front();
    list.pop_back();

    int x = list[1];

    list.print();


    return 0;
}
