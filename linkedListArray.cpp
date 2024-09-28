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
struct NodeArray {
    T data[5];
    int index = 0;
    NodeArray<T>* next;
    T *ptr = data;
    NodeArray(T v, NodeArray<T>* n = nullptr) {
        add(v);
        next = n;
    }

    void add(T v) {
        if (index < 5) {
            *ptr = v;
            ptr++;
            index++;

        } else {
            index = 0;
            ptr = &data[index];
            throw runtime_error("Node is full");
        }
    }

};


template <class T, class U>
class LinkedListArray {
private:
    NodeArray<T>* head = nullptr;
    U comparator;

public:
    int len = 0;
    LinkedListArray() : head(nullptr) {}

    void add(T v) {
        NodeArray<T>* pos = nullptr;
        if (!find(v, pos)) {
            if (!head) {
                head = new NodeArray<T>(v);
            } else if (pos->next == nullptr) {
                if (pos->index < 5) {
                    pos->add(v);
                } else {
                    pos->next = new NodeArray<T>(v, pos->next);
                }
            } else {
                pos->add(v);
            }
            len++;
        }
    }

    bool find(T &v, NodeArray<T>*& pos) {
        pos = nullptr;
        if (!head) return false;

        NodeArray<T>* p = head;
        while (p != nullptr) {
            for (int i = 0; i < p->index; i++) {
                if (p->data[i] == v) {
                    return true;
                }
                //ASC: a < b
                if(!comparator(p->data[i], v)) {
                    T cp = p->data[i];
                    p->data[i] = v;
                    v = cp;
                }
            }
            pos = p;

            p = p->next;
        }
        return false;
    }

    void del(T v) {
        NodeArray<T>* pos;
        cout<<"find:"<<find(v, pos)<<"\n";
        if (find(v, pos)) {
            if (pos == nullptr) {
                NodeArray<T>* temp = head;
                head = head->next;
                delete temp;
            }
            else {
                NodeArray<T>* temp = pos->next;
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
        NodeArray<T>* current = head;
        cout << "[head]";
        int nodeCount = 0;
        while (current != nullptr) {
            cout << " -> [";
            for (int i = 0; i < current->index; i++) {
                cout << current->data[i];
                if (i < current->index - 1) {
                    cout << ", ";
                }
            }
            cout << "]";
            current = current->next;
            nodeCount++;
        }
        cout << " -> [nullptr]" << endl;
    }

};

// *
// 1 -> 2 -> 3 -> 4
int main()
{

    LinkedListArray<int, ASC<int>> listAsc;

    for (int i = 10; i >= 0; i--) {
        listAsc.add(i);

    }








    cout << "\nLista ascendente: ";
    listAsc.print();
    cout<<"\nLEN: "<<listAsc.len<<"\n";



    int len = 2;
    nodo: cout<<len/5<<"\n";
    idnex: cout<<len%5<<"\n";


}
