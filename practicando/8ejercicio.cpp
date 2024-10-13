//Aprender a utilizar la clase de STL forward_list<T>
#include <iostream>
#include <forward_list>

int main() {
    // Declarar una lista enlazada de enteros
    std::forward_list<int> flist = {1, 2, 3, 4, 5};

    // Recorrer e imprimir la lista
    for (int &n : flist) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    flist.push_front(7);
    for (int &n : flist) {
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
