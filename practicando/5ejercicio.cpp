/*
Modificar el programa del punto 1, para que se pueda ordenar
de forma ascendente o descendente, utilizando punteros a funciones.
*/
#include <iostream>
using namespace std;

template <class T>
bool asc(T a, T b){
    return a < b;
}
template <class T>
bool desc(T a, T b){
    return a > b;
}

template <class T>
T* partition(T *ini, T*end, bool (*compare)(T, T)){
    T*p = ini;
    T*q = ini - 1;
    T *pivot = end;
    while(p <= (end)) {
        if(compare(*p, *pivot)){
            q++;
            std::swap(*q,*p);
        }
        p++;
    }
    std::swap(*(q+1),*pivot);
    return q+1;
}

template <class T>
void quickSort(T* ini, T* high, bool (*compare)(T, T)){
    if(ini < high){
        T *pi = partition(ini, high, compare);
        quickSort(ini, pi - 1, compare);
        quickSort(pi + 1, high, compare);
    }
}


int main(){
    int n = 10;
    int A[n] = {3,2,5,0,1,8,7,6,9,4};


    cout << "Array original:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n\n";

    // Ordenar en forma ascendente
    quickSort<int>(A, A + n - 1, asc);
    cout << "Array ordenado ascendente:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n\n";

    // Ordenar en forma descendente
    quickSort<int>(A, A + n - 1, desc);
    cout << "Array ordenado descendente:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";

    return 0;

}
