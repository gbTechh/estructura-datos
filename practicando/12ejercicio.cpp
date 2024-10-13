/*
Aprender a utilizar la clase de STL deque<T>
*/
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> dq;

    // Insertar elementos en ambos extremos
    dq.push_back(10);  // [10]
    dq.push_front(20); // [20, 10]
    dq.push_back(30);  // [20, 10, 30]
    dq.push_front(40); // [40, 20, 10, 30]

    // Imprimir elementos
    cout << "Deque: ";
    for (int i = 0; i < dq.size(); i++) {
        cout << dq[i] << " ";
    }
    cout << endl;

    // Acceso a elementos
    cout << "Front: " << dq.front() << endl; // 40
    cout << "Back: " << dq.back() << endl;   // 30

    // Eliminar elementos de ambos extremos
    dq.pop_front();  // [20, 10, 30]
    dq.pop_back();   // [20, 10]

    // Imprimir elementos después de eliminar
    cout << "Deque after pop: ";
    for (int i = 0; i < dq.size(); i++) {
        cout << dq[i] << " ";
    }
    cout << endl;

    return 0;
}
