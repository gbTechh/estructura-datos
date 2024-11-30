#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

mutex m;
long sum = 0;

void F1(int x, int n) {
    int k = 0;
    for ( int i = 0; i < n; i++){
        if(++k % 100 == 0){
            m.lock();
            sum += x;
            m.unlock();
        }else {
            sum += x;
        }

    }
}

int main() {

    int i = 0, nThreads = thread::hardware_concurrency();
    vector<thread> ths(nThreads);
    cout<<"\n N° threads: "<<nThreads<<"\n";

    for(i = 0; i < nThreads; i++)
        ths[i] = thread(F1, i+1, 10000);

    for(i = 0; i < nThreads; i++)
        ths[i].join();


    cout<<"\n sum: "<<sum<<"\n";




    return 0;
}
