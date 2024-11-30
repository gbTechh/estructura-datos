#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

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



mutex m;
long sum = 0;

void F1(int x, int n) {
    int k = 0;
    for ( int i = 0; i < n; i++){
        if(++k % 100 == 0){
            m.lock();
            sum += x;
            m.unlock();;
        }else {
            sum += x;
        }

    }
}

int main() {

    int i = 0, nThreads = thread::hardware_concurrency();
    vector<thread> ths(nThreads);
    cout<<"\n N° threads: "<<nThreads<<"\n";

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

    for(i = 0; i < nThreads; i++)
        ths[i] = thread(F1, i+1, 10000);

    for(i = 0; i < nThreads; i++)
        ths[i].join();


    cout<<"\n sum: "<<sum<<"\n";




    return 0;
}
