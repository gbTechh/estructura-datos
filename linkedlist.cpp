#include <iostream>
using namespace std;

template <class T>
class ASC {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};

template <class T>
class DESC {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};


template<class T>
struct Node {
    T data;
    Node<T>* next;
    Node(T v, Node<T>* n = nullptr) {
        data = v;
        next = n;
    }
};


template <class T, class U>
class LinkedList {
private:
    Node<T>* head = nullptr;
    U comparator;
public:
    LinkedList() : head(nullptr) {}

    void add(T v) {
        /*Node<T>* newNode = new Node<T>(v);

        if (head == nullptr || comparator(head->data, v)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node<T>* pos = nullptr;
        if (find(v, pos)) {
            delete newNode;
            return;
        }

        newNode->next = pos->next;
        pos->next = newNode;*/
        Node<T>* pos = nullptr;
        if (!find(v, pos))
        {
            if (!pos)
                head = new Node<T>(v, head);
            else
                pos->next = new Node<T>(v, pos->next);
        }
    }


    bool find(T v, Node<T>*& pos) {
        //Node<T>* current = null;//head;
        pos = nullptr;
        Node<T>* p = head;
        for (; p && comparator(p->data, v); pos = p, p = p->next);
        if (p && p->data == v) {
            return true;
        }
        return false;

        /*while (current != nullptr && !comparator(current->data, v)) {
            if (current->data == v) {
                return true;
            }
            pos = current;
            current = current->next;
        }

        return false;*/
    }

    void del(T v) {
        Node<T>* pos;
        if (find(v, pos)) {
            if (pos == nullptr) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
            }
            else {
                Node<T>* temp = pos->next;
                pos->next = temp->next;
                delete temp;
            }
            cout << "Elemento " << v << " eliminado.\n";
        }
        else {
            cout << "Elemento " << v << " no encontrado.\n";
        }
    }
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

// *
// 1 -> 2 -> 3 -> 4
int main()
{

    LinkedList<int, ASC<int>> listAsc;
    listAsc.add(3);
    listAsc.add(1);
    listAsc.add(3);
    listAsc.add(4);
    listAsc.add(2);

    cout << "\nLista ascendente: ";
    listAsc.print();

    LinkedList<char, DESC<char>> listDesc;
    listDesc.add('a');
    listDesc.add('t');
    listDesc.add('f');
    listDesc.add('b');
    listDesc.add('e');

    cout << "\nLista descendente: ";
    listDesc.print();

    cout << "\nMetodo delete (lista descendente): ";
    listDesc.del('c');
    listDesc.del('a');
    listDesc.print();




}
