/*
Aprender a utilizar las clases de STL queue<T>
*/
#include <iostream>
#include <queue>

int main() {
    // Crear una cola de enteros
    std::queue<int> q;

    // Añadir elementos a la cola (push)
    q.push(10);
    q.push(20);
    q.push(30);

    // Imprimir el tamaño de la cola
    std::cout << "Tamaño de la cola: " << q.size() << std::endl;

    // Acceder al elemento del frente (front) y al del final (back)
    std::cout << "Elemento al frente: " << q.front() << std::endl; // 10
    std::cout << "Elemento al final: " << q.back() << std::endl;   // 30

    // Eliminar el elemento del frente (pop)
    q.pop();
    std::cout << "Elemento al frente después de pop: " << q.front() << std::endl; // 20

    // Verificar si la cola está vacía
    if (q.empty()) {
        std::cout << "La cola está vacía." << std::endl;
    } else {
        std::cout << "La cola no está vacía." << std::endl;
    }

    return 0;
}
