/*
Implementar el metodo rangeSearch del stack ordenado.
Notar que debe funcionar con ambos functores.
El resultado debe salir igual que la imagen output
Codear dentro del metodo rangeSearch
Pueden crear nuevas funciones o metodos si lo desean
pero no medifiquen el main ni los otros metodos existentes
Impriman el resultado, no retornen nada (void)
*/

#include <iostream>
using namespace std;

template <class T>
struct Ascending {
    bool operator()(T a, T b) {
        return a < b;
    }
};

template <class T>
struct Descending {
    bool operator()(T a, T b) {
        return a > b;
    }
};

template <class T>
class Node {
public:
    T value;
    Node* next;

    Node(T value, Node* next = nullptr) {
        this->value = value;
        this->next = next;
    }
};

template <class T, class Comparator = Ascending<T>>
class OrderedStack {
private:
    Node<T>* head = nullptr;
    Comparator compare;

public:
    bool find(T val, Node<T>**& p) {
        for (p = &head; *p && compare((*p)->value, val); p = &((*p)->next));
        return *p && (*p)->value == val;
    }

    void push(T val) {
        Node<T>** p;
        find(val, p);

        Node<T>* newNode = new Node<T>(val, *p);
        *p = newNode;
    }

    void pop() {
        if (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pop(T val) {
        Node<T>** p;
        if (find(val, p)) {
            Node<T>* temp = *p;
            *p = (*p)->next;
            delete temp;
        }
    }

    void print() {
        cout << "HEAD -> ";
        for (Node<T>* p = head; p; p = p->next) cout << p->value << " -> ";
        cout << "NULL\n";
    }

    T top() {
        if (this->head) return this->head->value;
        cout << "Empty Stack!" << endl;
        return 0;
    }

    void rangeSearch(T minVal, T maxVal) {

        // Codea aqui :D
        // Imprime el resultado dentro de este metodo, no devuelvas nada (void)



    }
};

int main() {
    // Test with Ascending Order
    cout << "----- Ascending Order Tests -----\n";
    OrderedStack<int, Ascending<int>> ascStack;

    // Push elements into the ascending stack
    ascStack.push(5);
    ascStack.push(3);
    ascStack.push(8);
    ascStack.push(1);
    ascStack.push(10);

    cout << "Initial Ascending Stack:\n";
    ascStack.print();  // Expect: 1 -> 3 -> 5 -> 8 -> 10 -> NULL

    // Test rangeSearch with a range that includes some elements
    cout << "Range Search [3, 8]:\n";
    ascStack.rangeSearch(3, 8);  // Expect: 3 5 8

    // Test rangeSearch with a range that excludes all elements
    cout << "Range Search [11, 20]:\n";
    ascStack.rangeSearch(11, 20);  // Expect: (empty line)

    // Test rangeSearch with a range that includes only one element
    cout << "Range Search [5, 5]:\n";
    ascStack.rangeSearch(5, 5);  // Expect: 5

    // Test rangeSearch with a range that covers all elements
    cout << "Range Search [1, 10]:\n";
    ascStack.rangeSearch(1, 10);  // Expect: 1 3 5 8 10

    // Test rangeSearch with a range that starts from an element not in the stack
    cout << "Range Search [4, 10]:\n";
    ascStack.rangeSearch(4, 10);  // Expect: 5 8 10


    // Test with Descending Order
    cout << "\n----- Descending Order Tests -----\n";
    OrderedStack<int, Descending<int>> descStack;

    // Push elements into the descending stack
    descStack.push(5);
    descStack.push(3);
    descStack.push(8);
    descStack.push(1);
    descStack.push(10);

    cout << "Initial Descending Stack:\n";
    descStack.print();  // Expect: 10 -> 8 -> 5 -> 3 -> 1 -> NULL

    // Test rangeSearch with a range that includes some elements
    cout << "Range Search [3, 8]:\n";
    descStack.rangeSearch(3, 8);  // Expect: 8 5 3

    // Test rangeSearch with a range that excludes all elements
    cout << "Range Search [11, 20]:\n";
    descStack.rangeSearch(11, 20);  // Expect: (empty line)

    // Test rangeSearch with a range that includes only one element
    cout << "Range Search [5, 5]:\n";
    descStack.rangeSearch(5, 5);  // Expect: 5

    // Test rangeSearch with a range that covers all elements
    cout << "Range Search [1, 10]:\n";
    descStack.rangeSearch(1, 10);  // Expect: 10 8 5 3 1

    // Test rangeSearch with a range that starts from an element not in the stack
    cout << "Range Search [4, 10]:\n";
    descStack.rangeSearch(4, 10);  // Expect: 10 8 5


    return 0;
}
