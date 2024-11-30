/*TAREA DISJKTRA */
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility> // para std::pair
using namespace std;

// Estructura para representar un nodo y su distancia
struct Nodo {
    int id;
    int distancia;

    // Constructor
    Nodo(int _id, int _distancia) : id(_id), distancia(_distancia) {}

    // Operador de comparación para la priority_queue
    // Queremos que el nodo con menor distancia tenga mayor prioridad
    bool operator>(const Nodo& otro) const {
        return distancia > otro.distancia;
    }
};

class Grafo {
private:
    int V; // Número de vértices
    // Lista de adyacencia: vector de pares (destino, peso)
    vector<vector<pair<int, int>>> adyacencia;

public:
    // Constructor: inicializa el grafo con V vértices
    Grafo(int vertices) : V(vertices) {
        adyacencia.resize(V);
    }

    // Agregar una arista al grafo
    void agregarArista(int origen, int destino, int peso) {
        adyacencia[origen].push_back({destino, peso});
        adyacencia[destino].push_back({origen, peso}); // Si el grafo es no dirigido
    }

    // Implementación del algoritmo de Dijkstra
    vector<int> dijkstra(int inicio) {
        // Cola de prioridad para mantener los nodos por visitar
        // Usamos greater para que sea un min-heap (menor distancia tiene mayor prioridad)
        priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;
        // Vector de distancias, inicialmente infinito
        vector<int> distancias(V, numeric_limits<int>::max());
        // Vector para guardar el camino
        vector<int> previo(V, -1);
        // La distancia al nodo inicial es 0
        distancias[inicio] = 0;
        pq.push(Nodo(inicio, 0));
        // Mientras haya nodos por procesar
        while (!pq.empty()) {
            // Obtener el nodo con menor distancia
            int u = pq.top().id;
            int dist_u = pq.top().distancia;
            pq.pop();
            // Si ya encontramos una distancia menor, continuamos
            if (dist_u > distancias[u]) continue;
            // Explorar todos los vecinos del nodo actual
            for (const auto& vecino : adyacencia[u]) {
                int v = vecino.first;        // ID del nodo vecino
                int peso = vecino.second;     // Peso de la arista
                // Si encontramos un camino más corto al vecino
                if (distancias[u] + peso < distancias[v]) {
                    // Actualizamos la distancia
                    distancias[v] = distancias[u] + peso;
                    previo[v] = u;  // Guardamos el camino
                    // Agregamos el vecino a la cola de prioridad
                    pq.push(Nodo(v, distancias[v]));
                }
            }
        }

        // Imprimir los caminos
        for (int i = 0; i < V; i++) {
            if (i != inicio) {
                cout << "Camino más corto de " << inicio << " a " << i << ": ";
                imprimirCamino(previo, i);
                cout << " (distancia: " << distancias[i] << ")\n";
            }
        }
        return distancias;
    }

    // Función auxiliar para imprimir el camino
    void imprimirCamino(const vector<int>& previo, int destino) {
        if (previo[destino] == -1) {
            cout << destino;
            return;
        }
        imprimirCamino(previo, previo[destino]);
        cout << " -> " << destino;
    }
};

int main() {
    // Crear un grafo de ejemplo con 6 vértices
    Grafo g(6);

    // Agregar aristas (origen, destino, peso)
    g.agregarArista(0, 1, 4);
    g.agregarArista(0, 2, 2);
    g.agregarArista(1, 2, 1);
    g.agregarArista(1, 3, 5);
    g.agregarArista(2, 3, 8);
    g.agregarArista(2, 4, 10);
    g.agregarArista(3, 4, 2);
    g.agregarArista(3, 5, 6);
    g.agregarArista(4, 5, 3);

    cout << "Caminos más cortos desde el vértice 0:\n";
    g.dijkstra(0);

    return 0;
}

/*FIN TAREA DISJKTRA */
