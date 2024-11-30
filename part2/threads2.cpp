#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void F1(char c, int n) {
    for ( int i = 0; i < n; i++)
        cout<<c;
}

int main() {

    int i = 0, nThreads = thread::hardware_concurrency();
    vector<thread> ths(nThreads);

    for(i = 0; i < nThreads; i++)
        ths[i] = thread(F1, char('a'+i), 10000000);

    for(i = 0; i < nThreads; i++)
        ths[i].join();


    cout<<"\n";




    return 0;
}
