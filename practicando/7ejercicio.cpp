/*
Implementar la clase CVector, que es vector de datos,
que se redimensiona cuando necesita más espacio,
con las operaciones push_front, push_back, pop_front, pop_back, operator[].
*/
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class CVector {
private:
    T *arr;
    std::size_t capacity = 0;
    void resize(){
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* newArr = new T[capacity];
        for (std::size_t i = 0; i < len; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    void move(){
        capacity = capacity + 1;
        T* newArr = new T[capacity];
        for(std::size_t i = 0; i < len; i++){
            newArr[i + 1] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
public:
    std::size_t len = 0;
    CVector(int x){
        capacity = x;
        arr = new T[capacity];
    }
    CVector(){
        capacity = 1;
        arr = new T[capacity];
    }
    ~CVector(){
        delete[] arr;
    }
    T& operator[](std::size_t ind){
        if(ind >= len){
           throw std::out_of_range("INDEX FUERA DEL RANGO");
        }
        return arr[ind];
    }
    void push_front(T v){
        if(len == 0){
            arr[0] = v;
            len++;
            return;
        }
        move();
        arr[0] = v;
        len++;
    }
    void push_back(T v){
        if(len == 0){
            arr[0] = v;
            len++;
            return;
        }
        if(len >= capacity){
            resize();
        }
        arr[len] = v;
        len++;
    }

    void pop_back() {
        if (len == 0) return;
        len--;
    }

    void pop_front(){
        if (len == 0) return;
        T* newArr = new T[capacity];
        for(std::size_t i = 0; i < len; i++){
            newArr[i] = arr[i + 1];
        }
        delete[] arr;
        arr = newArr;
        len--;
    }

};

// [2,3,4,5]
int main(){
    CVector<int> vector;

    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);
    vector.push_back(5);
    vector.push_back(6);
    vector.push_back(7);
    vector.push_back(8);
    vector.push_back(9);
    vector.pop_front();

    cout<<"vector size: "<<vector.len<<"\n";

    cout<<"vector [0]:"<<vector[0]<<endl;



    for(int i= 0; i < vector.len; i++){
        if(i != vector.len - 1){
            cout<<vector[i]<<", ";
        } else{
            cout<<vector[i];
        }
    }
    cout<<"\n";

    return 0;
}
