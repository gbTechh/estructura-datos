/*
Aprender a utilizar las clases de STL stack<T>
*/
#include <iostream>
#include <stack>

int main() {
    // Crear una pila de enteros
    std::stack<int> myStack;

    // Insertar elementos en la pila
    myStack.push(10);  // Pila: 10
    myStack.push(20);  // Pila: 10, 20
    myStack.push(30);  // Pila: 10, 20, 30

    // Mostrar el elemento en la parte superior
    std::cout << "Top element: " << myStack.top() << std::endl;  // Salida: 30

    // Eliminar el elemento en la parte superior
    myStack.pop();  // Elimina 30, ahora la pila es: 10, 20

    // Mostrar el nuevo elemento en la parte superior
    std::cout << "New top element: " << myStack.top() << std::endl;  // Salida: 20

    // Tamaño de la pila
    std::cout << "Size of the stack: " << myStack.size() << std::endl;  // Salida: 2

    // Verificar si la pila está vacía
    if (myStack.empty()) {
        std::cout << "The stack is empty!" << std::endl;
    } else {
        std::cout << "The stack is not empty." << std::endl;  // Salida: The stack is not empty.
    }

    return 0;
}
