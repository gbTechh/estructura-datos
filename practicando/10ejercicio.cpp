//Aprender a utilizar la clase de STL list<T>
#include <iostream>
#include <list>

int main() {
    // Crear una lista vacía
    std::list<int> myList;

    // Insertar elementos en la lista
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    myList.push_front(5);

    // Imprimir los elementos
    std::cout << "Lista inicial: ";
    for (const int &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Eliminar elementos del frente y del final
    myList.pop_front();
    myList.pop_back();

    std::cout << "Después de pop_front y pop_back: ";
    for (const int &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Insertar un nuevo elemento en el segundo lugar (usando un iterador)
    auto it = myList.begin();
    ++it;  // Apuntar al segundo elemento
    myList.insert(it, 15);

    std::cout << "Después de insertar 15 en el segundo lugar: ";
    for (const int &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Eliminar el segundo elemento (usando un iterador)
    it = myList.begin();
    ++it;  // Apuntar al segundo elemento
    myList.erase(it);

    std::cout << "Después de eliminar el segundo elemento: ";
    for (const int &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Ordenar la lista
    myList.push_back(25);
    myList.push_back(10);
    myList.sort();

    std::cout << "Después de ordenar: ";
    for (const int &x : myList) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
