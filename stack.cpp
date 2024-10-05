#include <iostream>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T> *next;

   Node(T v) : data(v), next(nullptr) {}

};

template<class T>
class Stack {
    private:
        Node<T> *top = nullptr;
    public:
        void push(T v) {
            Node<T>* newNode = new Node<T>(v);
            if (!top) {
                top = newNode;
                return;
            }
            newNode->next = top;
            top = newNode;
        }
        bool pop(T &v) {
            if(top) {
                Node<T>* temp = top;
                v  = temp->data;
                top = top->next;
                delete temp;
                return true;
            }
            return false;
        }
        // void poping() {
        //     if(top) {
        //         Node<T>* temp = top;
        //         top = top->next;
        //         delete temp;
        //     }
        // }
        void print() {
            Node<T>* current = top;
            cout << "top->";
            while (current != nullptr) {
                cout << current->data << "->";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }

};


int main () {

    Stack<int> stack;
    stack.print();

    stack.push(3);
    stack.push(1);
    stack.push(5);
    stack.push(7);
    stack.push(9);

    int x = 0;
    stack.print();
    stack.pop(x);
    stack.print();
    cout<<"valor borrado: "<<x<<"\n";



    return 0;
}
