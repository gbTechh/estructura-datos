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
    NodeArray(T v, NodeArray<T>* n = nullptr) {
        add(v);
        next = n;
    }

    void add(T v) {
        if (index < 5) {
            data[index++] = v;
        }
        else {
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
    int index = 0;
    LinkedListArray() : head(nullptr) {}

    void add(T v) {
        NodeArray<T>* pos = nullptr;
        if (!find(v, pos)) {
            if (!head) {
                head = new NodeArray<T>(v);
            }
            else if (pos->next == nullptr) {
                if (pos->index < 5) {
                    pos->add(v);
                }
                else {
                    pos->next = new NodeArray<T>(v, pos->next);
                }
            }
            else {
                pos->add(v);
            }
            len++;
        }
    }

    bool find(T& v, NodeArray<T>*& pos, bool isDelete = false) {
        pos = nullptr;
        if (!head) return false;
        NodeArray<T>* p = head;
        while (p != nullptr) {
            for (int i = 0; i < p->index; i++) {
                if (p->data[i] == v) {
                    index = i;
                    pos = p;
                    return true;
                }
                //ASC: a < b
                if (!comparator(p->data[i], v) && !isDelete) {
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

    void del(T &v) {
        NodeArray<T>* pos = nullptr;
        NodeArray<T>* current = nullptr;
        NodeArray<T>* p = head;
        if (find(v, pos, true)) {
            while (pos != nullptr) {
                for (int i = index; i < pos->index; i++) {
                    if(i == 4){
                        pos->data[i] = pos->next->data[0];
                        index = 0;
                    } else {
                        pos->data[i] = pos->data[i+1];
                    }
                }
                if(pos->next == nullptr){
                    current = pos;
                }
                pos = pos->next;
            }
            current->index = current->index - 1;
            len--;
        }
        else {
            cout << "Elemento no encontrado\n";
        }
    }
    void print() {
        NodeArray<T>* current = head;
        cout << "[head]";
        while (current != nullptr) {
            cout << " -> [";
            for (int i = 0; i < current->index; i++) {
                cout << current->data[i];
                if (i < current->index - 1) {
                    cout << ", ";
                }

            }
            if(current->index < 5)  {
                for(int j = current->index; j < 5; j ++){
                    cout<<", _";
                }
            }
            cout << "]";
            current = current->next;
        }
        cout << " -> [nullptr]" << endl;
    }

};


int main()
{

    LinkedListArray<int, ASC<int>> listAsc;

    listAsc.add(15);
    listAsc.add(13);
    listAsc.add(12);
    listAsc.add(11);
    listAsc.add(10);
    listAsc.add(9);
    listAsc.add(8);
    listAsc.add(7);
    listAsc.add(6);
    listAsc.add(4);
    listAsc.add(3);
    listAsc.add(2);
    listAsc.add(1);

    cout << "\nLista ascendente: ";
    listAsc.print();
    cout << "\nLista ascendente: ";

    listAsc.add(20);
    listAsc.add(21);
    listAsc.add(22);
    listAsc.add(23);
    listAsc.add(24);
    listAsc.add(25);
    listAsc.print();

    int x = 4;
    listAsc.del(x);
    x = 1;
    listAsc.del(x);

    listAsc.print();



}
