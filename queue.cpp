#include <iostream>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T> *next;

    Node(T v) : data(v), next(nullptr) {}
};

template<class T>
class Queue {
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;

public:
    void push(T v) {
        Node<T>* newNode = new Node<T>(v);
        if (!tail) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode; 
        tail = newNode; 
    }

    bool pop(T &v) {
        if (head) {
            Node<T>* temp = head;
            v = temp->data;
            head = head->next;
            if (!head) { 
                tail = nullptr;
            }
            delete temp;
            return true;
        }
        return false;
    }

    void print() {
        Node<T>* current = head;
        cout << "front->";
        while (current != nullptr) {
            cout << current->data << "->";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    Queue<int> queue;
    queue.print();

    queue.push(3);
    queue.push(1);
    queue.push(5);
    queue.push(7);
    queue.push(9);

    int x = 0;
    queue.print();
    queue.pop(x);
    queue.print();
    cout << "valor borrado: " << x << "\n";

    return 0;
}
