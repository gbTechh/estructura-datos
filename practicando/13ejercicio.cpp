/*
Implementar la clase CDeque, tomando como ejemplo la clase deque<T> de STL,
con las operaciones push_front, push_back, pop_front, pop_back, operator[].

*/
#include <iostream>
using namespace std;

template <class T>
class CDeque {
private:
    T ** map;
    T * vec;
    int len;
    int size_map, size_vec;
    int len_map;
public:
    CDeque(int _size_map = 5, int _size_vec = 5) {
        size_map = _size_map;
        size_vec = _size_vec;
        map = new T*[size_map];
        for (int i = 0; i < size_map; ++i) {
            map[i] = new T[size_vec];
        }
    }

    ~CDeque() {

    }

    T operator[](T index) {

    }

    void push_back(T v) {
        if(!len){
            int index_map = size_map / 2;
            int index_vec = size_vec / 2;
            vec = vec + index_vec;
            *vec = v;
            map = map + index_map;
            *map = vec;
            len++;
            len_map++;
        }
    }

    void push_front(T v) {

    }

    void print() {
        T ** p = map;
        for ( int i = 0; i < len_map; i++ ){
            cout<<*(map[i])<<" ,"<<endl;
        }
    }


};



int main() {

    CDeque<int> deque;
    deque.push_back(10);
    deque.print();

    return 0;
}
