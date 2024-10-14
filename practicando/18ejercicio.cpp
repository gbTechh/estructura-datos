/*
Implementar la clase CSortedList, que es una clase simplemente enlazada,
ordenada, y que no admite elementos repetidos.
*/
#include <iostream>
using namespace std;

template <class T>
struct Asc {
    bool operator()(T a , T b){
        return a < b;
    }
};
template <class T>
struct Desc {
    bool operator()(T a , T b){
        return a > b;
    }
};

template <class T>
struct Node {
    Node<T> * next;
    T data;

    Node(T v, Node<T> *p = nullptr){
        data = v;
        next = p;
    }
};

template <class T, class C>
class CSortedList {
public:
    C comp;
    Node<T> * head;

    CSortedList(): head(nullptr) {}

    void add(T v){
        Node<T> * pos = nullptr;
        if(!find(v, pos)){
            if(!pos){
                head = new Node<T>(v, head);
            } else {
                pos->next = new Node<T>(v, pos->next);
            }
        }
    }

    bool find(T v, Node<T> * &pos){
        Node<T> * p = head;
        pos = nullptr;
        for(; p && comp(p->data, v); pos = p,p = p->next);
        if(p && p->data == v){
            return true;
        }
        return false;
    }

    bool del(T v){
        Node<T> * temp = nullptr;
        Node<T> * pos = nullptr;
        if(!find(v, pos)){
            return false;
        }
        if(pos == nullptr){
            head = nullptr;
        }else {
            temp = pos->next;
            pos->next = pos->next->next;
        }
        delete temp;
        return true;
    }

    void print(){
        Node<T> * p = head;
        cout<<"head -> ";
        while(p != nullptr){
            cout<<p->data<<" -> ";
            p = p->next;
        }
        cout<<"nullptr\n";
    }
};


int main(){

    CSortedList<int, Asc<int>> list;
    list.add(1);
    list.add(3);
    list.add(2);
    list.add(6);
    list.add(5);
    list.del(6);
    list.del(5);
    list.del(3);
    list.del(2);
    list.del(1);




    list.print();



    return 0;
}
