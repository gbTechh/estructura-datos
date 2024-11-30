/*TAREA PRIORITY QUEUE */
#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Definimos una estructura para representar un estudiante
struct Estudiante {
    string nombre;
    int promedio;
    Estudiante(string n, int p) : nombre(n), promedio(p) {}
    // Operador de comparación
    bool operator<(const Estudiante& otro) const {
        return promedio < otro.promedio;  // Ordenar por promedio
    }
};
/*Operaciones importantes a recordar:
push(elemento): Inserta un elemento
top(): Retorna el elemento de mayor prioridad
pop(): Elimina el elemento de mayor prioridad
empty(): Verifica si la cola está vacía
size(): Retorna el número de elementos */
int main() {
    // Creamos una cola de prioridad de estudiantes
    priority_queue<Estudiante> pq_estudiantes;
    // Insertamos algunos estudiantes
    pq_estudiantes.push(Estudiante("Juan", 85));
    pq_estudiantes.push(Estudiante("Ana", 92));
    pq_estudiantes.push(Estudiante("Pedro", 78));
    // Mostramos los estudiantes en orden de promedio (mayor a menor)
    while(!pq_estudiantes.empty()) {
        Estudiante est = pq_estudiantes.top();
        cout << est.nombre << ": " << est.promedio << endl;
        pq_estudiantes.pop();
    }
}
/*FIN TAREA PRIORITY QUEUE */
