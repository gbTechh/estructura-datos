/*
GRAFOS2: Consdiere el siguiente programa. La matriz del programa representa un grafo, siendo cada casilelro un nodo
y sus vecinos los casilleros arriba, abajo, izquierda y derecha; notese que en las esquinas los nodos tiene 2 del os 4 veceinos mencionados.
Los caracteres marcadoscon#, son barreras y por lo tanto no es un vecino del nodo adyacente(sigue el tratamiento de una esquina). Asi entnediendo que esto es un grafo,
encuentre el camino mas corto entre 'a'(2,13) y 'b'(14,1), y marque este camino con el caracter 'x'. DE la misma forma,
encuentre el camino mas corto entre 'c'(2,1) y 'd'(13,13, y marque este camino con el caracter 'y'. Cada busqueda debe ser realziada dentro de una thread separada. Realizar todo su codigo dentro de la funcion llamada proc())
*/
#include <iostream>
#include <thread>
#include <queue>
#include <map>
#include <vector>
#include <mutex>
#include <algorithm>

using namespace std;

// Matriz global que representa el laberinto
char g[16][16] =
{
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ','c',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','b',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ','a',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','d',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};

// Mutex para proteger el acceso a la matriz global
std::mutex mtx;

// Estructura para representar una posición en la matriz
struct Position {
    int x, y;
    Position() : x(0), y(0) {}  // Constructor por defecto
    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Función para encontrar el camino más corto entre dos puntos
vector<Position> findShortestPath(Position start, Position end, char marker) {
    // Vectores para representar los 4 movimientos posibles: arriba, derecha, abajo, izquierda
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    queue<Position> q;                    // Cola para BFS
    map<Position, Position> parent;       // Mapa para reconstruir el camino

    // Inicializar BFS desde el punto de inicio
    q.push(start);
    parent[start] = start;

    // BFS
    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        // Si llegamos al destino, terminamos la búsqueda
        if (current == end) {
            break;
        }

        // Probar los 4 movimientos posibles
        for (int i = 0; i < 4; i++) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            Position next(newX, newY);

            // Verificar si la nueva posición es válida y no ha sido visitada
            if (newX >= 0 && newX < 16 && newY >= 0 && newY < 16 &&
                g[newX][newY] != '#' && parent.find(next) == parent.end()) {
                q.push(next);
                parent[next] = current;
            }
        }
    }

    // Reconstruir el camino
    vector<Position> path;
    if (parent.find(end) != parent.end()) {
        Position current = end;
        while (!(current == start)) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
    }

    // Marcar el camino en la matriz
    mtx.lock();  // Bloquear el mutex antes de modificar la matriz global
    for (const Position& pos : path) {
        if (g[pos.x][pos.y] != 'a' && g[pos.x][pos.y] != 'b' &&
            g[pos.x][pos.y] != 'c' && g[pos.x][pos.y] != 'd') {
            g[pos.x][pos.y] = marker;
        }
    }
    mtx.unlock();  // Desbloquear el mutex

    return path;
}

// Función para imprimir la matriz
void print() {
    int x, y;
    std::cout << "\n";
    for (x = 0; x < 16; x++) {
        for (y = 0; y < 16; y++)
            std::cout << g[x][y] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Función principal que crea y maneja los threads
void proc() {
    // Definir las posiciones de inicio y fin para ambos caminos
    Position startAB(13, 2);    // posición de 'a'
    Position endAB(1, 14);      // posición de 'b'
    Position startCD(1, 2);     // posición de 'c'
    Position endCD(13, 13);     // posición de 'd'

    // Crear threads para buscar ambos caminos concurrentemente
    thread t1([&]() {
        findShortestPath(startAB, endAB, 'x');
    });

    thread t2([&]() {
        findShortestPath(startCD, endCD, 'y');
    });

    // Esperar a que ambos threads terminen
    t1.join();
    t2.join();
}

// Función main
int main() {
    print();      // Imprimir estado inicial
    proc();       // Procesar y encontrar caminos
    print();      // Imprimir resultado final
    return 0;
}
//FIN GRAFOS 2 ---CAMINO MAS CORTO X----
