#include <iostream>
#include <thread>
#include <vector>

using namespace std;

long sum = 0;

void F1(int x, int n) {
    for ( int i = 0; i < n; i++)
        sum += x;
}

int main() {

    int i = 0, nThreads = thread::hardware_concurrency();
    vector<thread> ths(nThreads);
    cout<<"\n N° threads: "<<nThreads<<"\n";

    for(i = 0; i < nThreads; i++)
        ths[i] = thread(F1, i, 100000);

    for(i = 0; i < nThreads; i++)
        ths[i].join();


    cout<<"\n sum: "<<sum<<"\n";




    return 0;
}
