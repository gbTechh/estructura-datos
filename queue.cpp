#include <iostream>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T> *next;

    Node(T v) : data(v), next(nullptr) {}

};

template<class T>
class Cola {
    private:
        Node<T> *head = nullptr;
        Node<T> *tail = nullptr;
    public:
        void push(T v) {

        }
        bool pop(T &v) {

        }
        // void poping() {
        //     if(top) {
        //         Node<T>* temp = top;
        //         top = top->next;
        //         delete temp;
        //     }
        // }
        void print() {
            Node<T>* current = head;
            cout << "head->";
            while (current != nullptr) {
                cout << current->data << "->";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }

};


int main () {

    Cola<int> cola;
    cola.print();

    cola.push(3);
    cola.push(1);
    cola.push(5);
    cola.push(7);
    cola.push(9);

    int x = 0;
    cola.print();
    cola.print();
    cout<<"valor borrado: "<<x<<"\n";



    return 0;
}
