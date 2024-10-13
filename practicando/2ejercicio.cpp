/*
Modificar el programa del punto 1, para que se pueda ordenar de
forma ascendente o descendente, utilizando polimorfismo.
*/
#include <iostream>
using namespace std;

// Clase base para el criterio de comparación
class Comparator {
public:
    virtual bool compare(int a, int b) = 0; // Método virtual puro
};

// Clase derivada para orden ascendente
class AscendingComparator : public Comparator {
public:
    bool compare(int a, int b) override {
        return a < b; // Menor que para orden ascendente
    }
};

// Clase derivada para orden descendente
class DescendingComparator : public Comparator {
public:
    bool compare(int a, int b) override {
        return a > b; // Mayor que para orden descendente
    }
};

// Función de partición que usa un comparador
template <class T>
T* partition(T *ini, T* end, Comparator* comp) {
    T* pivot = end; // Elegimos el último elemento como pivote
    T* q = ini - 1; // q apunta al último elemento menor que el pivote

    for (T* p = ini; p < end; p++) {
        if (comp->compare(*p, *pivot)) {
            q++;
            std::swap(*q, *p); // Intercambiamos el elemento menor
        }
    }
    std::swap(*(q + 1), *pivot); // Intercambiamos el pivote en su posición correcta
    return q + 1; // Retornamos la posición del pivote
}

// Función QuickSort que usa un comparador
template <class T>
void quickSort(T* ini, T* high, Comparator* comp) {
    if (ini < high) {
        T* pi = partition(ini, high, comp); // Particionamos y obtenemos el índice del pivote
        quickSort(ini, pi - 1, comp); // Llamada recursiva en la parte izquierda
        quickSort(pi + 1, high, comp); // Llamada recursiva en la parte derecha
    }
}

int main() {
    int n = 10;
    int A[n] = {3, 2, 5, 0, 1, 8, 7, 6, 9, 4};

    cout << "Array original:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n\n";

    // Elegir el comparador: Ascendente o Descendente
    Comparator* comp = new AscendingComparator();
    Comparator* comp2 = new DescendingComparator(); /// Cambia a DescendingComparator() para orden descendente

    quickSort(A, A + n - 1, comp); // Llamamos a quickSort

    cout << "Array ordenado asc:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
    quickSort(A, A + n - 1, comp2); // Llamamos a quickSort

    cout << "Array ordenado desc:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";

    delete comp; // Liberamos memoria
    delete comp2; // Liberamos memoria
    return 0;
}
