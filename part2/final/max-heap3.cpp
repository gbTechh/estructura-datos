/*
HEAP TERNARIO: Considere la siguiente secuencia de números: {30,35,40,50,43,36,60,51,70,90,66,77,23,21,49,88,73}.
Si insertamos esta secuencia en un MaxHeap basado en la topología de un árbol binario (2 hijos), quedaría como en la imagen 1.
Por otro lado, si insertamos esta misma secuencia en un MaxHeap basado en la topología de un árbol ternario (3 hijos), quedaría
como en la imagen 2. En esta pregunta se pide que a partir del siguiente código inicial
(preg_heap.cpp), se implemente una clase en C++ para representar un MaxHeap basado en un árbol ternario.
*/
/*
En el caso de nuestro MaxHeap ternario, usamos el deque porque:
Necesitamos acceso aleatorio eficiente para comparar padres e hijos
La estructura del heap crece y se reduce dinámicamente
Podemos acceder a cualquier elemento en O(1);
std::deque<int> heap;
heap.push_back(90);  // Raíz
heap.push_back(88);  // Hijo izquierdo
heap.push_back(77);  // Hijo medio
heap.push_back(73);  // Hijo derecho

// Acceder al padre y sus hijos
int padre = heap[0];           // 90
int hijoIzquierdo = heap[1];   // 88
int hijoMedio = heap[2];       // 77
int hijoDerecho = heap[3];     // 73
*/
#include <iostream>
#include <deque>
#include <vector>

template <class T>
class CMaxHeap3 {
public:
    void push(int n);
    int top();
    void pop();
    void print();
private:
    std::deque<T> heap;

    // Helper methods for heap operations
    int parent(int i) { return (i - 1) / 3; }  // Get parent index
    int leftChild(int i) { return 3 * i + 1; } // Get left child index
    int middleChild(int i) { return 3 * i + 2; } // Get middle child index
    int rightChild(int i) { return 3 * i + 3; } // Get right child index
    void heapifyUp(int i);   // Restore heap property upwards
    void heapifyDown(int i); // Restore heap property downwards
};

template <class T>
int CMaxHeap3<T>::top() {
    if (heap.empty()) return 0;
    return heap.front();
}

template <class T>
void CMaxHeap3<T>::push(int x) {
    // Add the new element at the end
    heap.push_back(x);
    // Restore heap property by moving it up if needed
    heapifyUp(heap.size() - 1);
}

template <class T>
void CMaxHeap3<T>::heapifyUp(int i) {
    // While we're not at the root and parent is smaller
    while (i > 0 && heap[parent(i)] < heap[i]) {
        // Swap with parent
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template <class T>
void CMaxHeap3<T>::heapifyDown(int i) {
    int largest = i;
    int left = leftChild(i);
    int middle = middleChild(i);
    int right = rightChild(i);
    int size = heap.size();

    // Compare with left child
    if (left < size && heap[left] > heap[largest])
        largest = left;

    // Compare with middle child
    if (middle < size && heap[middle] > heap[largest])
        largest = middle;

    // Compare with right child
    if (right < size && heap[right] > heap[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        // Recursively heapify the affected sub-tree
        heapifyDown(largest);
    }
}

template <class T>
void CMaxHeap3<T>::pop() {
    if (heap.empty()) return;

    // Replace root with last element
    heap[0] = heap.back();
    heap.pop_back();

    // Restore heap property if heap is not empty
    if (!heap.empty()) {
        heapifyDown(0);
    }
}

template <class T>
void CMaxHeap3<T>::print() {
    for (auto i = heap.begin(); i != heap.end(); ++i)
        std::cout << *i << " ";
    std::cout << "\n";
}

int main() {
    CMaxHeap3<int> h;
    std::vector<int> vpush = {30,35,40,50,43,36,60,51,70,90,66,77,23,21,49,88,73};
    for (auto i : vpush)
        h.push(i);
    h.print();
    for (int j = 0; j < 5; j++)
        h.pop();
    h.print();
}

/*FIN HEAP TERNARIO */
