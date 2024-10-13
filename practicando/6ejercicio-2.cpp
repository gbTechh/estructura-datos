/*
Aprender a utilizar las clases de STL array<T> y vector<T>
*/
#include <iostream>
#include <vector> // Necesario para std::vector

int main() {
    // Declaración de un vector de enteros
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Añadir elementos al final
    vec.push_back(6);

    // Acceder a los elementos
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;

    // Eliminar el último elemento
    vec.pop_back();

    // Uso de funciones adicionales
    std::cout << "Tamaño del vector: " << vec.size() << std::endl;
    std::cout << "Capacidad del vector: " << vec.capacity() << std::endl;

    return 0;
}
