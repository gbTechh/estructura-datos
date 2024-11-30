#include <cstdio>
#include <iostream>
#include <thread>

using namespace std;

void F1(char c, int n) {
    for ( int i = 0; i < n; i++)
        cout<<c;
}

int main() {
    std::thread t(F1, 'c', 5);

    t.join();

    cout<<"\n";




    return 0;
}
