/*
Modificar el programa del punto 3, para que se pueda
ordenar de forma ascendente o descendente,
utilizando function objects, y funciones inline.
*/

#include <iostream>
using namespace std;


template <class T>
class Asc {
public:
    inline bool operator()(T a, T b){
        return a < b;
    }
};
template <class T>
class Desc {
public:
    inline bool operator()(T a, T b){
        return a > b;
    }
};

template <class T, class C>
struct QuickSort {
    C comparator;
    T* partition(T *ini, T*end){
        T*p = ini;
        T*q = ini - 1;
        T *pivot = end;
        while(p <= (end)) {
            if(comparator(*p , *pivot)){
                q++;
                std::swap(*q,*p);
            }
            p++;
        }
        std::swap(*(q+1),*pivot);
        return q+1;
    }

    void sort(T* ini, T* high){
        if(ini < high){
            T *pi = partition(ini, high);
            sort(ini, pi - 1);
            sort(pi + 1, high);
        }
    }
};

int main() {

    int n = 10;
    int A[n] = {3, 2, 5, 0, 1, 8, 7, 6, 9, 4};

    QuickSort<int, Asc<int>> quick;
    quick.sort(A, A+n-1);


    cout << "Array ordenado asc:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";

    QuickSort<int, Desc<int>> quick2;
    quick2.sort(A, A+n-1);

    cout << "Array ordenado desc:\n";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
    return 0;
}
