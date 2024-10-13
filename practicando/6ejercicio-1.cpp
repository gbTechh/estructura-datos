/*
Aprender a utilizar las clases de STL array<T> y vector<T>
*/
#include <iostream>
#include <array>

int main(){

    std::array<int, 5>arr={1,2,3,5,6};

    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout<<"\n";

    std::cout << "Primer elemento: " << arr.front() << std::endl;
    std::cout << "Último elemento: " << arr.back() << std::endl;
    std::cout << "Tamaño del array: " << arr.size() << std::endl;
    std::cout << "AT: " << arr.at(4) << std::endl;

    //SWAP
    std::array<int,5> first = {10, 20, 30, 40, 50};
    std::array<int,5> second = {11, 22, 33, 44, 55};
    first.swap(second);
    std::cout << "first:";
    for (int& x : first) std::cout << ' ' << x;
    std::cout << '\n';
    std::cout << "second:";
    for (int& x : second) std::cout << ' ' << x;
    std::cout << '\n';


    //REND (REVERSE)
    std::array<int,4> myarray = {4, 26, 80, 14} ;

    std::cout << "myarray contains:";
    for ( auto rit=myarray.rbegin() ; rit < myarray.rend(); ++rit )
        std::cout << ' ' << *rit;

    std::cout << '\n';

    return 0;
}
