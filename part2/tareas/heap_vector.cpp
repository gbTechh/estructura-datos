/*TAREA HEAP VECTOR */
/*
[80,72,30,62,55,10,20,47,73]
73: i = 8;
padre: (i-1)/2 = x=> (3): 62
padre del padre: (x-1)/2 = 1 (72) , el 3 es una variable j
padre del padre: (3-1)/2 = 1 (72) , el 3 es una variable j
hijos:
(j+1) * 2
(j+1) * 2 - 1

*/
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class great {
public:
    bool operator()(T A, T B) {
        return A > B;
    }
};

template <class T>
class lessi {
public:
    bool operator()(T A, T B) {
        return A < B;
    }
};

template <class T, class U>
struct CHeap {
    vector<T> heap;
    T max();
    void push(T x);
    T pop();
    U orden;
    void print();
};

template<class T, class U>
void CHeap<T, U>::push(T x) {
    if (heap.empty()) {
        heap.push_back(x);
    }
    else {
        heap.push_back(x);
        int i = heap.size() - 1;
        while (true) {
            int comp = (i - 1) / 2;
            if (orden(heap[i], heap[comp])) {
                swap(heap[i], heap[comp]);
                i = comp;
            }
            else { break; }
            if (i == 0) { break; }
        }
    }
}

template<class T, class U>
T CHeap<T, U>::max() {
    return heap.front();
}

template<class T, class U>
T CHeap<T, U>::pop() {
    int j = 0;
    int last = heap.size() - 1;
    swap(heap[last], heap[j]);
    heap.resize(last);

    while (true) {

        int h1 = j * 2 + 1;
        int h2 = j * 2 + 2;
        int next = j;

        if (h1 < heap.size() && orden(heap[h1], heap[j])) {
            next = h1;
        }
        if (h2 < heap.size() && orden(heap[h2], heap[next])) {
            next = h2;
        }
        if (next == j) break;
        swap(heap[j], heap[next]);
        j = next;
    }
    return heap.front();
}

template<class T, class U>
void CHeap<T, U>::print() {
    for (auto& value : heap) {
        cout << value << " ";
    }
    cout << endl;
}
int main() {
    CHeap<int, lessi<int>> max_heap;
    max_heap.push(80);
    max_heap.push(72);
    max_heap.push(30);
    max_heap.push(55);
    max_heap.push(10);
    max_heap.push(20);
    max_heap.push(47);
    max_heap.push(62);
    max_heap.push(73);
    max_heap.print();
    max_heap.pop();
    max_heap.print();
    return 0;
}
/*FIN TAREA HEAP VECTOR */
