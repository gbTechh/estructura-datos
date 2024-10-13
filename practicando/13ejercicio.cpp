/*
Implementar la clase CDeque, tomando como ejemplo la clase deque<T> de STL,
con las operaciones push_front, push_back, pop_front, pop_back, operator[].

*/
#include <iostream>
using namespace std;

template <class T>
class CDeque {
private:
    T * map;
    T * vec;
    int len;
    int capacity;
    int size_map, size_vec;
public:
    CDeque(int _size_map = 5, int _size_vec = 5) {
        size_map = _size_map;
        size_vec = _size_vec;
        T vec[size_vec];
        T map[size_map];
    }
    ~CDeque();
    void push_back(T v) {
        if(!len){

        }
    }
    void push_front(T v) {

    }
    T operator[](T index) {

    }



};

void print( CDeque* p)
{ //no modificar esta función
    for ( int i = 0; i < p->size; i++ )
        std::cout<<(*p)[i]<<" ";
    std::cout<<"\n";
}


int main() {

    CDeque<int> deque(4,4);

    print(deve)

    return 0;
}
