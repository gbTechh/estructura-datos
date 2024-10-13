#include <iostream>
using namespace std;

template <class T>
T* partition(T *ini, T*end){
    T*p = ini;
    T*q = ini - 1;
    T *pivot = end;
    while(p <= (end)) {
        if(*p < *pivot){
            q++;
            std::swap(*q,*p);
        }
        p++;
    }
    std::swap(*(q+1),*pivot);
    return q+1;
}

template <class T>
void quickSort(T* ini, T* high){
    if(ini < high){
        T *pi = partition(ini, high);
        quickSort(ini, pi - 1);
        quickSort(pi + 1, high);
    }
}


int main(){
    int n = 10;
    int A[n] = {3,2,5,0,1,8,7,6,9,4};

    for (int i = 0; i < n; i++) {
        cout<<A[i]<<" ";
    }
    cout<<"\n\n";
    quickSort(A, A+n-1);
    for (int i = 0; i < n; i++) {
        cout<<A[i]<<" ";
    }
    cout<<"\n";

    return 0;

}
