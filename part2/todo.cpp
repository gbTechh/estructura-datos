// AVL MAXHEIGHT - THREADS
//IMPLEMENTAR el metodo MaxNodeHeight para calcular la altura de un nodo cualquiera
//Luego utilizar el metodo MaxNodeHeight en el metodo MaxHeight para calcular la altura
//maxma de todo el arbol, este metodo debe ser implementaod utilizando 4 threads
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CAVLNode
{
    CAVLNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0;  }
    int value;
    CAVLNode* nodes[2];
};
////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAVLTree
{
public:
    CAVLTree();
    ~CAVLTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    int MaxNodeHeight(CAVLNode* n);
    int MaxHeight();

private:
    bool Find(int x, CAVLNode**& p);
    CAVLNode** Rep(CAVLNode** p);
    void InOrder(CAVLNode* n);
    CAVLNode* m_root;
};

CAVLTree::CAVLTree()
{   m_root = 0; }

CAVLTree::~CAVLTree()
{}

bool CAVLTree::Find(int x, CAVLNode**& p)
{
    for ( p = &m_root ; *p && (*p)->value != x ; p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CAVLTree::Insert(int x)
{
    CAVLNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CAVLNode(x);
    return 0;
}
bool CAVLTree::Remove(int x)
{
    CAVLNode** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CAVLNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CAVLNode* t = *p;
    *p = (*p)->nodes[ !(*p)->nodes[0] ];
    delete t;
    return 1;
}

CAVLNode** CAVLTree::Rep(CAVLNode** p)
{
    bool b = rand()%2;
    for( p = &( (*p)->nodes[b] ); (*p)->nodes[!b]; p = &( (*p)->nodes[!b] ) );
    return p;
}

void CAVLTree::InOrder(CAVLNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CAVLTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}
//======================================================
void MaxNodeHeightThread(CAVLNode* n, int& height) {
    if (!n) {
        height = 0;
        return;
    }
    queue<CAVLNode*> cola;
    cola.push(n);
    height = 0;

    while(!cola.empty()) {
        int level = cola.size();
        for(int i = 0; i < level; i++){
            CAVLNode* current = cola.front();
            cola.pop();
            if(current->nodes[0]){
                cola.push(current->nodes[0]);
            }
            if(current->nodes[1]){
                cola.push(current->nodes[1]);
            }
        }
        height++;
    }
}
//======================================================
int CAVLTree::MaxNodeHeight(CAVLNode* n) {
    int h;
    MaxNodeHeightThread(n, h);
    return h;
}
int CAVLTree::MaxHeight()
{
    if(m_root == nullptr) return 0;

    /*trhead */
    int nt = 4;
    int xheight[4] = {0,0,0,0};
    vector<thread> ths(nt);

    /*cola */
    queue<CAVLNode*> cola;
    cola.push(m_root);
    int h = 1;
    int hroot = 0;
    while(!cola.empty()) {
        int level = cola.size();
        if(h<3){
            for(int i = 0; i < level; i++){
                CAVLNode* current = cola.front();
                cola.pop();
                if(current->nodes[0]){
                    cola.push(current->nodes[0]);
                }
                if(current->nodes[1]){
                    cola.push(current->nodes[1]);
                }
            }
            hroot = h;

        }else{
            int height;
            //puede ser level: for(int i = 0; i < level; i++)
            for(int i = 0; i < 4; i++){
                CAVLNode* current = cola.front();
                cola.pop();
                ths[i] = thread(MaxNodeHeightThread, current, ref(xheight[i]));
            }
            //puede ser level: for(int i = 0; i < level; i++)
            for(int i = 0; i < 4; i++)
                ths[i].join();

        }

        h+=1;

    }

    int maxHeight = 0;
    for(int i = 0; i < nt; i++) {
        if(xheight[i] > maxHeight)
            maxHeight = xheight[i];
    }

    return maxHeight  + hroot;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    // int v[150] = {239, 389, 128, 46, 235, 65, 423, 417, 121, 451, 396, 331, 158, 100, 95, 353, 470, 207, 453, 156, 98, 160, 373, 44, 313, 284, 152, 131, 236, 340, 369, 408, 411, 174, 141, 69, 96, 451, 259, 28, 234, 158, 168, 100, 379, 1, 487, 307, 182, 486, 385, 221, 30, 305, 41, 115, 415, 227, 166, 85, 220, 446, 127, 66, 316, 298, 144, 446, 65, 425, 241, 160, 215, 346, 212, 341, 44, 452, 226, 168, 132, 230, 448, 173, 174, 483, 59, 237, 436, 28, 472, 2, 142, 194, 203, 355, 410, 78, 418, 489, 220, 258, 19, 411, 373, 216, 311, 31, 411, 357, 334, 205, 118, 471, 252, 291, 389, 40, 389, 437, 36, 134, 475, 401, 448, 133, 30, 251, 456, 220, 417, 302, 256, 34, 120, 115, 318, 459, 110, 251, 392, 360, 261, 389, 450, 122, 308, 188, 212, 37};
    // CAVLTree t;
    // for ( int i = 0; i < 150; i++ )
    //     t.Insert(v[i]);
    // t.Print();
    // cout<<"Max Height is: "<<t.MaxHeight()<<endl;
    //
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000000); // Rango de números entre 1 y 100000

    CAVLTree t;

    // Medir tiempo de inserción
    auto start_insert = chrono::high_resolution_clock::now();

    // Insertar 10000 números aleatorios
    for(int i = 0; i < 10000000; i++) {
        t.Insert(dis(gen));
    }

    auto end_insert = chrono::high_resolution_clock::now();
    chrono::duration<double> insert_time = end_insert - start_insert;

    cout << "Tiempo de inserción: " << fixed << setprecision(4)
            << insert_time.count() << " segundos" << endl;
    // Medir tiempo de cálculo de altura
    auto start_height = chrono::high_resolution_clock::now();

    int height = t.MaxHeight();
    auto end_height = chrono::high_resolution_clock::now();
    chrono::duration<double> height_time = end_height - start_height;

    cout << "Altura máxima: " << height << endl;
    cout << "Tiempo de cálculo de altura: " << fixed << setprecision(4)
            << height_time.count() << " segundos" << endl;
    //t.Print();
    return 0;
}
// FIN AVL MAXHEIGHT - THREADS
/*
GRAFOS 1: implementar la funcion printTRavelEdge la cua dlebe imprimir todos
los recorridos psoibles partiendo de un nodo, en el cual debera recorrer
todas las aristas sin repetir el paso por una arista,
es posible repetir el paso por un nodo mas de una vez
*/

#include <iostream>
#include <vector>
using namespace std;

// Estructura de datos para almacenar nodos de lista de adyacencia
struct Node
{
	int val;
	Node* next;
};

// Estructura de datos para almacenar una arista de grafo
struct Edge {
	int src, dest;
};

class Graph
{
	// Función para asignar un nuevo nodo para la lista de adyacencia
	Node* getAdjListNode(int dest, Node* head)
	{
		Node* newNode = new Node;
		newNode->val = dest;
		// apunta nuevo nodo a la cabeza actual
		newNode->next = head;
		return newNode;
	}
	int N;	// número total de nodos en el grafo

public:


	Node** head;

	Graph(Edge edges[], int n, int N)
	{

		head = new Node * [N]();
		this->N = N;

		// inicializar el puntero de cabeza para todos los vértices
		for (int i = 0; i < N; i++) {
			head[i] = nullptr;
		}

		// agregar aristas al grafo dirigido
		// se insertan aristas de ida y vuelta
		for (unsigned i = 0; i < n; i++)
		{
			int src = edges[i].src;
			int dest = edges[i].dest;

			// insertar al principio
			Node* newNode = getAdjListNode(dest, head[src]);
			// apuntar el puntero de la cabeza al nuevo nodo
			head[src] = newNode;
			newNode = getAdjListNode(src, head[dest]);
			// cambia el puntero de la cabeza para que apunte al nuevo nodo
			head[dest] = newNode;

		}
	}

	// Destructor
	~Graph() {
		for (int i = 0; i < N; i++) {
			delete[] head[i];
		}
		delete[] head;
	}


};

// Función para imprimir todos los vértices vecinos de un vértice dado
void printList(Node* ptr)
{
	while (ptr != nullptr)
	{
		cout << "-> " << ptr->val << " ";
		ptr = ptr->next;
	}
	cout << endl;
}
void recursiveTravel(Graph& graph, vector<int>& path, vector<pair<int,int>>& usedEdges, int currentNode, int N) {
    // Si el camino es muy largo y no hemos cubierto todas las aristas, retornamos
    if (path.size() > 7) {
        return;
    }
    // Obtenemos la lista de adyacencia del nodo actual
    Node* current = graph.head[currentNode];

    // Recorremos todos los nodos adyacentes
    while (current != nullptr) {
        int nextNode = current->val;
        // Verificamos si esta arista ya fue usada
        pair<int,int> edge = make_pair(min(currentNode, nextNode), max(currentNode, nextNode));
        bool edgeUsed = false;
        for (const auto& usedEdge : usedEdges) {
            if (usedEdge == edge) {
                edgeUsed = true;
                break;
            }
        }
        // Si la arista no ha sido usada, la agregamos al camino
        if (!edgeUsed) {
            // Agregamos la arista al registro de aristas usadas
            usedEdges.push_back(edge);
            // Agregamos el siguiente nodo al camino
            path.push_back(nextNode);

            // Si hemos usado todas las aristas (7 en total), imprimimos el camino
            if (usedEdges.size() == 7) {
                cout << "Camino encontrado: ";
                for (int node : path) {
                    cout << node << " -> ";
                }
                cout << "FIN\n";
            } else {
                // Continuamos el recorrido desde el siguiente nodo
                recursiveTravel(graph, path, usedEdges, nextNode, N);
            }

            // Backtracking: removemos la última arista y nodo añadidos
            usedEdges.pop_back();
            path.pop_back();
        }
        current = current->next;
    }
}

void printTravelEdge(Graph& graph, int startNode, int N) {
    vector<int> path;                    // Para guardar el camino actual
    vector<pair<int,int>> usedEdges;     // Para registrar las aristas usadas
    // Iniciamos el camino con el nodo de inicio
    path.push_back(startNode);
    cout << "\nBuscando caminos desde el nodo " << startNode << ":\n";
    recursiveTravel(graph, path, usedEdges, startNode, N);
}
// Implementación de grafos
int main()
{
	// un array de aristas del grafo según el diagrama
	Edge edges[] =
	{
		// par `(x, y)` representa una arista de `x` a` y`
		{ 0, 1 }, { 0, 2 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 4 }, { 3, 4 }
	};

	// número total de nodos en el grafo
	int N = 5;

	// calcula el número total de aristas
	int n = sizeof(edges) / sizeof(edges[0]);

	// construir grafo
	Graph graph(edges, n, N);
	// imprimir la representación de la lista de adyacencia de un grafo
	for (int i = 0; i < N; i++)
	{
		// imprimir el vértice dado
		cout << i << " --";
		// imprime todos sus vértices vecinos
		printList(graph.head[i]);
	}

	//prueba de recorridos de aristas
	for (int i = 0; i < N; i++)
	{
		// imprimir el vértice de inicio
		cout << "\nPartiendo del nodo " << i << endl;
		// imprime el recorrido de todas las aristas sin repetir
		//printTravelEdge(graph.head[i], N);
		printTravelEdge(graph, i, N);
	}

	return 0;
}
/****FIIIIIN GRAFOS 1 ---- CAMINO EULERIANO NODOS */
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
/*
MATRIZ DISPERSA 2 - LIST: Considere el siguiente programa preg_sparse_matrix.cpp. En la clase SparseMatrix implemente el método set
que permita ingresar y actualizar elementos dentro de la Matriz Dispersa, la que debe ser implementada en
una lista enlazada de elementos Nodo. En método print, imprime los elementos dentro de la lista enlazada
que representa la matriz dispersa. En Main se proporciona una prueba en donde se llenará los elementos y
sus respectivas llamadas a la función print para comprobar el correcto funcionamiento de la matriz Dispersa.
En la clase SparseMatrix puede adicionar los métodos que considere pertinentes, sin embargo no debe
modificarse el método print.
*/
#include <iostream>

using namespace std;

class Nodo
{
public:
    int fil;
    int col;
    int dato;
    Nodo* next;
};

class SparseMatrix
{
public:
    Nodo* Mat = NULL;
    void set(int fil, int col, int dato);
    void print();
};

void SparseMatrix::set(int fil, int col, int dato) {
    // Si el dato es cero, debemos eliminar el nodo si existe
    if (dato == 0) {
        // Caso especial: lista vacía
        if (!Mat) return;

        // Caso especial: primer nodo debe ser eliminado
        if (Mat->fil == fil && Mat->col == col) {
            Nodo* temp = Mat;
            Mat = Mat->next;
            delete temp;
            return;
        }

        // Buscar y eliminar el nodo si existe
        for (Nodo* p = Mat; p->next != NULL; p = p->next) {
            if (p->next->fil == fil && p->next->col == col) {
                Nodo* temp = p->next;
                p->next = p->next->next;
                delete temp;
                return;
            }
        }
        return;
    }

    // Si la lista está vacía, crear el primer nodo
    if (!Mat) {
        Mat = new Nodo();
        Mat->fil = fil;
        Mat->col = col;
        Mat->dato = dato;
        Mat->next = NULL;
        return;
    }

    // Buscar si ya existe un nodo en esa posición
    for (Nodo* p = Mat; p != NULL; p = p->next) {
        if (p->fil == fil && p->col == col) {
            // Actualizar el dato existente
            p->dato = dato;
            return;
        }
    }

    // Si no existe, crear nuevo nodo al inicio de la lista
    Nodo* nuevo = new Nodo();
    nuevo->fil = fil;
    nuevo->col = col;
    nuevo->dato = dato;
    nuevo->next = Mat;
    Mat = nuevo;
}

void SparseMatrix::print()
{
    cout << "------Mat-----"<<endl;
    for (Nodo* p = Mat; p; p = p->next)
        cout << "[" << p->fil << "][" << p->col << "] = " << p->dato << endl;
    cout << "------FIN Mat-----"<<endl;
}

int main()
{
    SparseMatrix SM;

    int a[10][10] = { {0,10,20,30,40,50,60,70,80,90},
{10,20,30,40,50,60,70,0,80,90},
{10,20,30,0,50,60,70,80,90,0},
{20,10,90,0,10,20,60,70,80,0},
{30,20,90,10,20,30,70,0,80,10},
{30,20,0,10,20,30,70,80,90,10},
{80,20,20,20,0,60,0,90,90,0},
{70,10,30,30,0,70,70,80,80,0},
{0,20,30,20,10,70,0,80,80,10},
{80,20,90,30,10,0,80,90,90,10},
    };

    int b[10][10] = { {10,0,0,0,0,0,0,0,0,0},
{0,20,0,0,0,0,0,0,0,0},
{0,0,30,0,0,0,0,0,0,0},
{0,0,0,40,0,0,0,0,0,0},
{0,0,0,0,50,0,0,0,0,0},
{0,0,0,0,0,60,0,0,0,0},
{0,0,0,0,0,0,70,0,0,0},
{0,0,0,0,0,0,0,80,0,0},
{0,0,0,0,0,0,0,0,90,0},
{0,0,0,0,0,0,0,0,0,100},
    };

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, a[i][j]);

    SM.print();

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, b[i][j]);

    SM.print();

}
/*FIN MATRIZ DISPERSA 2 - LIST */
/*
MATRIZ DISPERSA 1: Considere el
siguiente programa representa una estructura "Sparse Matrix"
Implemente los metodos set, y get de la clase CSMatrix de tal manera
que el main funcione correctamente. Esta clase CSMatrix debe ser creada
sobre la base de la clase map STL
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class CSMatrix
{
public:
    CSMatrix(int dx, int dy);
    bool set(int x, int y, int value);
    int get(int x, int y);
    void print();

private:
    vector<map<int,int>> matrix; // declarando matrix
    int dimx, dimy;
};

CSMatrix::CSMatrix(int dx, int dy)
{
    dimx = dx; dimy = dy;
    matrix.resize(dimx);

}

bool CSMatrix::set(int x, int y, int value)
{
    // si value es 0 borrar, si no actualizar
    if(x >= dimx || y >= dimy || x < 0 || y < 0)
        return false;
    auto &map = matrix[x];

    if(value == 0) {
        map.erase(y);
        return true;
    }
    map[y] = value;

    return true;
}

int CSMatrix::get(int x, int y)
{
    if(x >= dimx || y >= dimy || x < 0 || y < 0)
        return 0;
    auto &map = matrix[x];
    int val = map[y];
    auto it = map.find(y);  // Busca sin insertar
    return (it != map.end()) ? it->second : 0;
}

void CSMatrix::print()
{
    std::cout << "\n";
    for (int x = 0; x < dimx; x++)
    {
        for (int y = 0; y < dimy; y++)
        {
            std::cout << get(x,y) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main()
{
    CSMatrix m(8,8);
    m.set(2, 1, 5);
    m.set(2, 3, 2);
    m.set(2, 5, 7);
    m.set(5, 3, 9);
    m.set(7, 3, 12);
    m.set(1, 4, 3);
    m.set(2, 4, 0);
    m.set(5, 5, 8);
    m.set(3, 6, 1);
    m.print();
    m.set(1, 4, 0);
    m.set(2, 3, 0);
    m.set(4, 3, 0);
    m.set(0, 1, 0);
    m.print();
    std::cout << "\n 0,0 => " << m.get(0, 0);
    std::cout<< "\n 3,5 => " << m.get(3, 5);
    std::cout<< "\n 7,3 => " << m.get(7, 3);

    cout<<"\n";
 }
/*FIN MATRIZ DISPERSA 1 - USO DE MAP */
/**
MATRIZ DISPERSA 3 - STL : Se pide implementar los metodos SET y GET
de la matriz, apra que las instrucicones del main funcionen correcamente
*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <class T, T NE>
class CSparseMatrix
{
    typedef unsigned int uint;
    typedef T value_type;
public:
    CSparseMatrix(uint xdim, uint ydim);
    void Set(uint x, uint y, T value);
    T    Get(uint x, uint y);
    void Print();

private:
    vector< list<T> > matrix;
    uint m_XDim, m_YDim;
};

template <class T, T NE>
CSparseMatrix<T,NE>::CSparseMatrix(uint xdim, uint ydim)
{
    m_XDim = xdim; m_YDim = ydim;
    matrix.resize(m_XDim);
}

template <class T, T NE>
void CSparseMatrix<T,NE>::Set(uint x, uint y, T value)
{
    // Verificar límites de la matriz
    if (x >= m_XDim || y >= m_YDim) return;

    // Obtener referencia a la lista en la fila x
    list<T>& row = matrix[x];

    // Si el valor es NE (elemento nulo), debemos eliminar el par si existe
    if (value == NE) {
        // Recorrer la lista de dos en dos buscando la coordenada y
        for (auto it = row.begin(); it != row.end(); ) {
            auto coord = it;  // Primer elemento del par (coordenada y)
            auto val = ++it;  // Segundo elemento del par (valor)

            if (coord != row.end() && val != row.end() && *coord == y) {
                // Eliminar tanto la coordenada como el valor
                it = row.erase(coord, ++val);
                return;
            }
        }
        return;
    }

    // Para insertar o actualizar un valor no nulo
    for (auto it = row.begin(); it != row.end(); ) {
        auto coord = it;      // Coordenada y actual
        auto val = ++it;      // Valor actual

        if (coord != row.end() && val != row.end()) {
            if (*coord == y) {
                // Actualizar valor existente
                *val = value;
                return;
            }
            ++it;  // Avanzar al siguiente par
        }
    }

    // Si llegamos aquí, debemos insertar un nuevo par
    row.push_back(y);    // Insertar coordenada y
    row.push_back(value); // Insertar valor
}

template <class T, T NE>
typename CSparseMatrix<T,NE>::value_type CSparseMatrix<T,NE>::Get(uint x, uint y)
{
    // Verificar límites de la matriz
    if (x >= m_XDim || y >= m_YDim) return NE;

    // Obtener referencia a la lista en la fila x
    const list<T>& row = matrix[x];

    // Recorrer la lista de dos en dos buscando la coordenada y
    auto it = row.begin();
    while (it != row.end()) {
        T coord = *it;    // Coordenada y
        ++it;
        if (it == row.end()) break;  // Verificación de seguridad
        T val = *it;      // Valor
        ++it;

        if (coord == y) return val;
    }

    // Si no encontramos la coordenada, retornar el elemento nulo
    return NE;
}

template <class T, T NE>
void CSparseMatrix<T,NE>::Print()
{
    int xi, yi;
    for (yi = 0; yi < m_YDim; yi++)
    {
        for (xi = 0; xi < m_XDim; xi++)
        {
            T value = Get(yi,xi);
            cout<< value<<" ";
        }
        cout<<endl;
    }
    cout<<"---"<<endl;
}
int main(int argc, const char * argv[])
{
    CSparseMatrix<int,0> m(5,5);

    m.Set(0,0,2);   m.Set(2,0,0);   m.Set(3,1,5);
    m.Set(1,2,6);   m.Set(2,2,7);   m.Set(3,2,0);
    m.Set(4,2,9);   m.Set(1,3,1);   m.Set(0,4,0);
    m.Set(3,4,8);
    m.Print();

    m.Set(3,1,0);   m.Set(1,2,0);   m.Set(0,4,0);
    m.Set(4,4,0);
    m.Print();

    return 0;
}
/*FIN MATRIZ DISPERSA 3 - STL */
/*
HEAP TERNARIO: Considere la siguiente secuencia de números: {30,35,40,50,43,36,60,51,70,90,66,77,23,21,49,88,73}.
Si insertamos esta secuencia en un MaxHeap basado en la topología de un árbol binario (2 hijos), quedaría como en la imagen 1.
Por otro lado, si insertamos esta misma secuencia en un MaxHeap basado en la topología de un árbol ternario (3 hijos), quedaría
como en la imagen 2. En esta pregunta se pide que a partir del siguiente código inicial
(preg_heap.cpp), se implemente una clase en C++ para representar un MaxHeap basado en un árbol ternario.
*/
/*
En el caso de nuestro MaxHeap ternario, usamos el deque porque:
Necesitamos acceso aleatorio eficiente para comparar padres e hijos
La estructura del heap crece y se reduce dinámicamente
Podemos acceder a cualquier elemento en O(1);
std::deque<int> heap;
heap.push_back(90);  // Raíz
heap.push_back(88);  // Hijo izquierdo
heap.push_back(77);  // Hijo medio
heap.push_back(73);  // Hijo derecho

// Acceder al padre y sus hijos
int padre = heap[0];           // 90
int hijoIzquierdo = heap[1];   // 88
int hijoMedio = heap[2];       // 77
int hijoDerecho = heap[3];     // 73
*/
#include <iostream>
#include <deque>
#include <vector>

template <class T>
class CMaxHeap3 {
public:
    void push(int n);
    int top();
    void pop();
    void print();
private:
    std::deque<T> heap;

    // Helper methods for heap operations
    int parent(int i) { return (i - 1) / 3; }  // Get parent index
    int leftChild(int i) { return 3 * i + 1; } // Get left child index
    int middleChild(int i) { return 3 * i + 2; } // Get middle child index
    int rightChild(int i) { return 3 * i + 3; } // Get right child index
    void heapifyUp(int i);   // Restore heap property upwards
    void heapifyDown(int i); // Restore heap property downwards
};

template <class T>
int CMaxHeap3<T>::top() {
    if (heap.empty()) return 0;
    return heap.front();
}

template <class T>
void CMaxHeap3<T>::push(int x) {
    // Add the new element at the end
    heap.push_back(x);
    // Restore heap property by moving it up if needed
    heapifyUp(heap.size() - 1);
}

template <class T>
void CMaxHeap3<T>::heapifyUp(int i) {
    // While we're not at the root and parent is smaller
    while (i > 0 && heap[parent(i)] < heap[i]) {
        // Swap with parent
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

template <class T>
void CMaxHeap3<T>::heapifyDown(int i) {
    int largest = i;
    int left = leftChild(i);
    int middle = middleChild(i);
    int right = rightChild(i);
    int size = heap.size();

    // Compare with left child
    if (left < size && heap[left] > heap[largest])
        largest = left;

    // Compare with middle child
    if (middle < size && heap[middle] > heap[largest])
        largest = middle;

    // Compare with right child
    if (right < size && heap[right] > heap[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        // Recursively heapify the affected sub-tree
        heapifyDown(largest);
    }
}

template <class T>
void CMaxHeap3<T>::pop() {
    if (heap.empty()) return;

    // Replace root with last element
    heap[0] = heap.back();
    heap.pop_back();

    // Restore heap property if heap is not empty
    if (!heap.empty()) {
        heapifyDown(0);
    }
}
template <class T>
void CMaxHeap3<T>::print() {
    for (auto i = heap.begin(); i != heap.end(); ++i)
        std::cout << *i << " ";
    std::cout << "\n";
}

int main() {
    CMaxHeap3<int> h;
    std::vector<int> vpush = {30,35,40,50,43,36,60,51,70,90,66,77,23,21,49,88,73};
    for (auto i : vpush)
        h.push(i);
    h.print();
    for (int j = 0; j < 5; j++)
        h.pop();
    h.print();
}
/*FIN HEAP TERNARIO */
/*
THREADS SUMA 20 - ARRAY 1
Considere el siguiente programa (preg_threads.cpp). En la función main, se tiene un
arreglo "v" de 1000 elementos enteros y se tiene un arreglo "sums" de 5 elementos.
Se pide sumar todos los elementos de "v" de la siguiente manera, los elementos que terminan en:
0 o 9 se sumen en sums[0]
1 o 8 se sumen en sums[1]
2 o 7 se sumen en sums[2]
3 o 6 se sumen en sums[3]
4 o 5 se sumen en sums[4]
- El proceso debe ser realizado con 20 threads.
- Todas las sumas deben ser hechas directamente en el array sums.
- No se debe utilizar la idea de que cada thread tenga su propia suma.
- Sólo se debe modificar la función ThreadingSum
- Se puede agregar otras funciones y variables
- La función main no debe ser modificada
*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>


// Necesitamos mutexes para proteger las sumas concurrentes
std::mutex sumMutexes[5];

// Función que ejecutará cada thread
void sumDigits(int* arr, int start, int count, unsigned long* sums) {
    // Cada thread procesará una porción del arreglo
    for (int i = start; i < start + count; i++) {
        // Obtenemos el último dígito del número
        int lastDigit = arr[i] % 10;

        // Determinamos en qué posición de sums debemos sumar
        int sumIndex;
        if (lastDigit == 0 || lastDigit == 9) sumIndex = 0;
        else if (lastDigit == 1 || lastDigit == 8) sumIndex = 1;
        else if (lastDigit == 2 || lastDigit == 7) sumIndex = 2;
        else if (lastDigit == 3 || lastDigit == 6) sumIndex = 3;
        else sumIndex = 4; // Para 4 y 5

        // Protegemos la suma con un mutex para evitar condiciones de carrera
        {
            std::lock_guard<std::mutex> lock(sumMutexes[sumIndex]);
            sums[sumIndex] += arr[i];
        }
    }
}

void ThreadingSum(int* pv, int sizev, unsigned long* sums, int sizes) {
    const int NUM_THREADS = 20;
    std::vector<std::thread> threads;

    // Calculamos cuántos elementos procesará cada thread
    int elementsPerThread = sizev / NUM_THREADS;
    int remainingElements = sizev % NUM_THREADS;

    // Creamos los threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Calculamos el punto de inicio para este thread
        int start = i * elementsPerThread;

        // Calculamos cuántos elementos procesará este thread
        int count = elementsPerThread;
        if (i == NUM_THREADS - 1) {
            // El último thread se encarga de los elementos restantes
            count += remainingElements;
        }

        // Creamos el thread y lo añadimos al vector
        threads.push_back(std::thread(sumDigits, pv, start, count, sums));
    }

    // Esperamos a que todos los threads terminen
    for (auto& thread : threads) {
        thread.join();
    }
}


int main()
{
    unsigned long sums[5] = {0,0,0,0,0};
    int v[1000] = {11,58,12,98,68,55,98,65,16,44,14,22,31,9,66,25,7,69,66,45,88,14,99,94,2,91,2,10,64,17,80,22,22,97,92,49,4,39,41,16,98,67,72,94,49,93,56,78,54,57,22,34,25,18,17,9,89,78,75,42,64,0,46,86,30,37,22,63,58,91,77,49,32,94,68,41,10,56,21,56,44,25,44,16,50,79,65,82,79,3,73,35,15,28,3,79,34,44,58,44,23,76,91,32,73,78,36,62,76,91,51,53,55,29,7,52,80,63,2,15,65,31,46,44,77,39,67,28,0,5,44,64,7,66,86,81,99,79,50,88,54,73,59,24,20,17,92,18,47,41,62,59,21,96,20,41,25,33,33,58,79,52,81,39,67,8,19,38,57,74,25,43,67,7,31,45,16,17,13,47,96,8,38,44,12,72,53,46,74,86,1,11,45,10,6,39,64,12,51,62,38,81,32,29,40,96,17,83,59,46,61,4,1,43,99,42,28,64,13,74,35,78,23,85,67,73,10,18,46,66,21,57,73,21,42,43,10,39,37,8,40,49,86,73,13,80,34,50,48,27,91,14,86,55,71,0,96,2,74,74,59,78,56,19,59,94,93,16,72,50,14,17,78,57,90,82,27,14,13,3,22,6,24,26,76,12,34,94,86,47,31,25,75,35,92,4,3,83,87,69,37,4,36,88,96,80,57,46,81,24,79,5,85,8,54,69,51,99,44,31,33,1,50,23,50,99,33,29,1,89,4,10,23,11,39,59,30,9,99,32,74,30,63,92,90,89,13,49,5,57,18,49,44,66,56,78,10,15,24,94,29,82,49,39,68,7,14,33,56,60,32,61,9,66,24,13,71,78,21,97,55,73,31,22,28,62,58,21,55,56,54,28,73,82,21,92,69,78,44,4,44,34,78,19,66,83,17,45,26,15,25,69,45,68,13,54,11,41,19,84,95,86,89,62,72,67,0,0,48,5,62,14,39,1,86,7,97,80,78,24,29,20,50,70,69,1,70,92,82,43,37,3,1,47,17,27,95,99,75,80,37,35,34,28,64,11,82,8,42,48,46,7,67,87,79,4,27,5,33,71,56,66,61,55,97,78,35,77,36,81,79,46,94,74,70,38,49,35,47,82,62,97,97,95,2,14,27,93,14,97,11,4,27,15,75,54,85,12,45,45,72,6,93,59,18,57,29,71,45,88,94,8,30,99,83,51,7,81,41,15,70,81,17,14,9,15,85,98,64,36,38,66,29,27,88,46,74,17,59,93,72,48,97,77,32,51,38,19,68,47,75,90,99,83,20,97,85,63,82,75,78,82,35,49,33,57,76,38,82,3,80,76,36,47,83,38,7,43,5,9,83,24,34,71,3,43,55,74,6,53,88,19,18,5,58,86,34,7,80,71,56,24,56,1,5,90,69,74,86,83,11,89,73,47,69,66,87,29,41,0,15,72,85,18,17,44,72,52,14,52,2,56,35,82,1,51,16,8,82,79,33,15,1,12,42,36,73,62,32,38,42,75,26,47,44,16,56,11,71,95,14,54,86,64,13,29,2,76,18,65,50,29,6,66,2,75,48,83,11,62,83,26,60,77,44,10,80,40,94,91,6,50,66,10,5,25,94,61,81,98,49,84,23,64,46,18,0,89,17,60,67,59,76,59,53,26,91,90,36,47,10,84,28,85,67,27,71,67,81,32,64,29,35,7,11,3,93,0,54,90,64,57,18,30,81,87,68,63,73,34,85,4,87,55,62,59,67,22,76,71,77,92,88,19,9,69,59,84,24,12,28,65,54,48,36,54,67,52,13,65,65,47,66,85,13,26,1,25,88,43,52,51,21,52,29,29,62,11,38,23,16,70,52,5,76,69,9,56,7,9,45,76,17,59,34,96,2,76,32,33,65,19,60,61,44,77,54,28,15,4,60,5,35,78,3,84,51,36,97,78,89,82,85,71,96,20,46,29,48,81,77,81,13,37,98,28,54,95,98,16,20,5,26,98,48,21,19,64,60,80,99,72,64,39,60,37,43,17,65,34,5,65,69,77,17,35,44,9,39,40,69,69,77,40,94,86,68,88,26,22,1,4,59,18,19,97,65,84,58,16,91,23,81,93,45,30,53,33,12,70,6,16,74,17,90,8,70,37,10,17,3,3,61,79,87,72,66,45,55,82,12,31,16,92,72,71,72,67,27,75,46,96,31,85,72,34,33,10,28,88,84,67,65,0,31,44,11,31,68,98,64,17,86,13,7,73,6,82,89,74};
    ThreadingSum(v, 1000, sums, 5);
    for (auto i : sums)
        std::cout<<i<<"\n";
}
//FIN THREADS SUMA 20 - ARRAY
/**
THREADS TREE ARBOL
Implemente el metodo insert y la funcion main; de tal forma que se pueda crear un arbol cuyas hojas son el array Leafs
y los nodos padres constituyen la suma del valor de sus hijos. Como por ejemplo, en la imagen se muestra un array y el
arbol correspondiente que se construiria con dichoi array. Debe realziar la construccion del arbol usando 4 threads, las
cuales deben estar ocupadas la mayor parte del tiempo del proceso en paralelo. Tambien se provee el metodo Print que
muestra el arbol por niveles
[3,25,30,28,10,11,15,14]
        136 |
    86   -    50 |
28  -  58   21 - 29 |
3-25 30-28 10-11 15-14
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
-Construcción Paralela:
Dividimos el array de hojas en 4 partes iguales
Cada thread construye un subárbol independiente
Finalmente, unimos los subárboles en un árbol completo
-buildSubTree:
Construye recursivamente un subárbol
Si es una hoja, crea un nodo con el valor del array
Si no, crea un nodo padre con la suma de sus hijos
-buildTreeParallel:
Crea 4 threads y asigna una sección del array a cada uno
Cada thread construye su parte independientemente
Al final, une los resultados en un árbol completo

*/struct CBinNode {
    CBinNode(int _v) {
        value = _v;
        nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

// Clase principal del árbol binario
class CBinTree {
public:
    CBinTree();
    bool Insert(int x);
    void Print();
    void buildTreeParallel(int* leafs, int size);

private:
    void printLevelOrder(CBinNode* root);
    void printCurrentLevel(CBinNode* root, int level);
    int height(CBinNode* node);
    CBinNode* buildSubTree(int* leafs, int start, int end, int level);
    void buildTreeSection(int* leafs, int start, int end, int level, CBinNode** result);

    CBinNode* m_root;
    mutex treeMutex;
};

// Constructor de la clase
CBinTree::CBinTree() {
    m_root = nullptr;
}

// Método para construir una sección del árbol (ejecutado por cada thread)
void CBinTree::buildTreeSection(int* leafs, int start, int end, int level, CBinNode** result) {
    *result = buildSubTree(leafs, start, end, level);
}

// Construye recursivamente un subárbol
CBinNode* CBinTree::buildSubTree(int* leafs, int start, int end, int level) {
    // Si solo hay un elemento, creamos un nodo hoja
    if (start == end) {
        return new CBinNode(leafs[start]);
    }
    // Calculamos el punto medio
    int mid = start + (end - start) / 2;
    // Creamos los subárboles izquierdo y derecho
    CBinNode* leftChild = buildSubTree(leafs, start, mid, level + 1);
    CBinNode* rightChild = buildSubTree(leafs, mid + 1, end, level + 1);

    // Creamos el nodo padre con la suma de los hijos
    CBinNode* parent = new CBinNode(leftChild->value + rightChild->value);
    parent->nodes[0] = leftChild;
    parent->nodes[1] = rightChild;

    return parent;
}

// Método principal para construir el árbol en paralelo
void CBinTree::buildTreeParallel(int* leafs, int size) {
    vector<thread> threads;
    vector<CBinNode*> subResults(4, nullptr);

    int sectionSize = size / 4;

    // Crear y ejecutar los 4 threads cada uno construyendo una parte del árbol
    for (int i = 0; i < 4; i++) {
        int start = i * sectionSize;
        int end = (i == 3) ? size - 1 : (i + 1) * sectionSize - 1;
        threads.push_back(thread(&CBinTree::buildTreeSection, this, leafs, start, end, 0, &subResults[i]));
    }

    // Esperar a que terminen todos los threads
    for (auto& t : threads) {
        t.join();
    }

    // Unir los resultados en pares
    CBinNode* leftPair = new CBinNode(subResults[0]->value + subResults[1]->value);
    leftPair->nodes[0] = subResults[0];
    leftPair->nodes[1] = subResults[1];

    CBinNode* rightPair = new CBinNode(subResults[2]->value + subResults[3]->value);
    rightPair->nodes[0] = subResults[2];
    rightPair->nodes[1] = subResults[3];

    // Crear el nodo raíz final
    m_root = new CBinNode(leftPair->value + rightPair->value);
    m_root->nodes[0] = leftPair;
    m_root->nodes[1] = rightPair;
}

// Métodos para imprimir el árbol
void CBinTree::Print() {
    printLevelOrder(m_root);
    cout << endl;
}

void CBinTree::printLevelOrder(CBinNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        cout << i << ": ";
        printCurrentLevel(root, i);
        cout << endl;
    }
}

void CBinTree::printCurrentLevel(CBinNode* root, int level) {
    if (root == nullptr)
        return;
    if (level == 1)
        cout << root->value << " ";
    else if (level > 1) {
        printCurrentLevel(root->nodes[0], level - 1);
        printCurrentLevel(root->nodes[1], level - 1);
    }
}

int CBinTree::height(CBinNode* node) {
    if (node == nullptr)
        return 0;
    else {
        int lheight = height(node->nodes[0]);
        int rheight = height(node->nodes[1]);
        return (lheight > rheight) ? (lheight + 1) : (rheight + 1);
    }
}

// Función principal
int main() {
    CBinTree t;
    int Leafs[128] = { 94,38,69,61,46,31,85,23,34,17,54,22,75,100,97,62,58,47,34,3,98,57,66,67,
                       99,17,69,46,14,36,96,83,8,97,53,58,33,94,79,67,4,3,21,63,7,15,89,14,63,80,
                       94,17,62,18,32,71,15,22,75,47,21,24,86,27,39,59,7,62,84,93,93,62,55,27,50,
                       34,94,93,14,20,6,82,49,58,2,98,74,36,71,60,63,46,71,89,56,66,37,18,37,99,
                       79,26,93,68,67,96,48,80,51,8,27,51,53,54,12,22,98,26,60,92,25,81,24,67,74,
                       21,30,55 };

    t.buildTreeParallel(Leafs, 128);
    t.Print();

    return 0;
}
//FIN THREADS TREE ARBOL
/*TAREA AVL TREE */
#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

template <class T>
struct Node {
    T data;
    Node<T> *nodes[2];
    int height = 0;
    Node(T v){
        data = v;
        nodes[0] = nodes[1] = 0;
        height = 1;
    }
};

template <class T>
class CBinTree {
private:
    bool brep = 0;

    Node<T>** rep(Node<T>**p) {
        Node<T>** q = &((*p)->nodes[!brep]);
        while((*q)->nodes[brep]){
            q = &(*q)->nodes[brep];
        }
        brep = !brep;
        return q;
    }
    bool find(T v,Node<T>**&p) {
        for(p = &root;
           *p && (*p)->data != v;
           p = &((*p)->nodes[(*p)->data < v])
        );
        return *p != 0;
    }
    bool findParent(T v,Node<T>**&p) {
        if (root == nullptr || root->data == v) return false;
        for (p = &root; *p; p = &((*p)->nodes[(*p)->data < v])) {
            if ((*p)->nodes[0] && (*p)->nodes[0]->data == v) return true;
            if ((*p)->nodes[1] && (*p)->nodes[1]->data == v) return true;
        }
        return false;
    }
    stack<Node<T> *> saveData(T v,Node<T>**&p) {
        stack<Node<T>*> stack;
        for (p = &root; *p && (*p)->data != v; p = &((*p)->nodes[(*p)->data < v])) {
            stack.push(*p);
        }
        return stack;
    }
    int getHeight(Node<T>* n) {
        if (n == nullptr) return 0;
        return n->height;
    }
    void setHeight(Node<T>**p) {
        (*p)->height = 1 + max(getHeight((*p)->nodes[0]), getHeight((*p)->nodes[1]));
    }
    int getBalance(Node<T>* n) {
        if (n == nullptr) return 0;
        return getHeight(n->nodes[0]) - getHeight(n->nodes[1]);
    }
    void balance(T v) {
        Node<T> **p;
        stack<Node<T>*> path = saveData(v, p);
        while (!path.empty()) {
            Node<T>* node = path.top();
            path.pop();

            int balance = getBalance(node);
            if (balance == -2) {
                rotateLeft(node);
            }
            if (balance == 2) {
                rotateRight(node);
            }
            // Añadir otros casos de balance...
        }
    }

public:
    Node<T> * root;
    CBinTree(){
        root = 0;
    }

    bool ins(T v){
        Node<T> ** p;
        if(find(v,p))return 0;
        *p = new Node<T>(v);
        stack<Node<T>*> stack = saveData(v, p);
        stack.push(*p);
        while (!stack.empty()) {
            Node<T> * node = stack.top();
            Node<T> * temp;
            stack.pop();

            setHeight(&node);
            int balance = getBalance(node);
            //izq - der = -2
            // Caso Left-Left: El desbalance está en el hijo izquierdo y el nuevo valor es menor
            if(balance == 2 && getBalance(node->nodes[0]) >= 0) {
                cout<<"lef lef"<<"\n";
                // Rotación simple a la derecha
                T temp = node->data;
                node->data = node->nodes[0]->data;
                node->nodes[0]->data = temp;
                //apuntar nodo
                Node<T>* rn = node->nodes[0];    // rn es hijo izquierdo de node
                Node<T>* A = node->nodes[1];    // ln es hijo derecho de node
                Node<T>* B = rn->nodes[1];   //l_rn es hijo derecho de rn

                node->nodes[0] = rn->nodes[0];
                setHeight(&node);
                node->nodes[1] = rn;
                rn->nodes[1] = A;
                rn->nodes[0] = B;
                setHeight(&rn);
                return true;
            }
            // Caso Right-Right: El desbalance está en el hijo derecho y el nuevo valor es mayor
            else if(balance == -2 && getBalance(node->nodes[1]) <= 0) {
                cout<<"right right"<<"\n";
                T temp = node->data;
                node->data = node->nodes[1]->data;
                node->nodes[1]->data = temp;
                //apuntar nodo
                Node<T>* rn = node->nodes[1];    // rn es hijo derecho de node
                Node<T>* A = node->nodes[0];    // ln es hijo izquierdo de node
                Node<T>* B = rn->nodes[0];   //l_rn es hijo izquierdo de rn

                node->nodes[1] = rn->nodes[1];
                setHeight(&node);
                node->nodes[0] = rn;
                rn->nodes[0] = A;
                rn->nodes[1] = B;
                setHeight(&rn);
                return true;
            }
            // Caso Left-Right: El desbalance está en el hijo izquierdo y el nuevo valor está en el medio
            else if(balance == 2 && getBalance(node->nodes[0]) < 0) {
                cout<<"lef right"<<"\n";
                //  A
                //B
                //  C
                Node<T>* A = node;             // Nodo actual (el desbalanceado)
                Node<T>* B = node->nodes[0];   // Hijo izquierdo
                Node<T>* C = B->nodes[1];      // Hijo derecho del hijo izquierdo

                // Intercambio de valores para mantener la estructura deseada
                T temp = A->data;
                A->data = C->data;
                C->data = temp;

                // Guardamos temporalmente los subárboles que se moverán
                Node<T>* T1 = B->nodes[0];    // Subárbol izquierdo de B
                Node<T>* T2 = C->nodes[0];    // Subárbol izquierdo de C
                Node<T>* T3 = C->nodes[1];    // Subárbol derecho de C
                Node<T>* T4 = A->nodes[1];    // Subárbol derecho de A

                // Reorganización de los punteros
                A->nodes[0] = C;              // C se convierte en hijo izquierdo de A
                A->nodes[1] = T4;             // Mantenemos el subárbol derecho de A
                C->nodes[0] = B;              // B se convierte en hijo izquierdo de C
                C->nodes[1] = T3;             // Mantenemos el subárbol derecho de C
                B->nodes[0] = T1;             // Mantenemos el subárbol izquierdo de B
                B->nodes[1] = T2;             // T2 se convierte en hijo derecho de B

                // Actualizamos las alturas de abajo hacia arriba
                setHeight(&B);
                setHeight(&C);
                setHeight(&A);
                return true;
            }
            // Caso Right-Left: El desbalance está en el hijo derecho y el nuevo valor está en el medio
            else if(balance == -2 && getBalance(node->nodes[1]) > 0) {
                //A
                //  B
                //C
                cout<<"right left"<<"\n";
                Node<T>* A = node;             // Nodo actual (el desbalanceado)
                Node<T>* B = node->nodes[1];   // Hijo derecho
                Node<T>* C = B->nodes[0];      // Hijo izquierdo del hijo derecho

                // Intercambio de valores para mantener la estructura deseada
                T temp = A->data;
                A->data = C->data;
                C->data = temp;

                // Guardamos temporalmente los subárboles que se moverán
                Node<T>* T1 = A->nodes[0];    // Subárbol izquierdo de A
                Node<T>* T2 = C->nodes[0];    // Subárbol izquierdo de C
                Node<T>* T3 = C->nodes[1];    // Subárbol derecho de C
                Node<T>* T4 = B->nodes[1];    // Subárbol derecho de B

                // Reorganización de los punteros
                A->nodes[0] = T1;             // Mantenemos el subárbol izquierdo de A
                A->nodes[1] = C;              // C se convierte en hijo derecho de A
                C->nodes[0] = T2;             // Mantenemos el subárbol izquierdo de C
                C->nodes[1] = B;              // B se convierte en hijo derecho de C
                B->nodes[0] = T3;             // T3 se convierte en hijo izquierdo de B
                B->nodes[1] = T4;             // Mantenemos el subárbol derecho de B

                // Actualizamos las alturas de abajo hacia arriba
                setHeight(&B);
                setHeight(&C);
                setHeight(&A);
                return true;
            }
        }


        return 0;
    }


    bool rem(T v){
        Node<T> **p;
        if(!find(v, p)) return 0;
        if((*p)->nodes[0] && (*p)->nodes[1]){
            Node<T> ** q = rep(p);
            (*p)->data = (*q)->data;
            p = q;
        }
        Node<T> * temp = *p;
        (*p) = (*p)->nodes[(*p)->nodes[1] != 0];
        delete temp;
        return 1;
    }
    void levelOrderTraversalWithHeight() {
        if (root == nullptr) return;
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node<T>* current = q.front();
                q.pop();
                // Mostramos el valor y la altura del nodo
                cout << current->data << "(h:" << current->height
                    << ",b:" << getBalance(current) << ") ";
                if (current->nodes[0])
                    q.push(current->nodes[0]);
                if (current->nodes[1])
                    q.push(current->nodes[1]);
            }
            cout << "| \n"; // Separador de niveles
    }
    cout << "\n";
}
    void levelOrderTraversal() {
        if (root == nullptr) return;

        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                Node<T>* current = q.front();
                q.pop();
                cout << current->data << " ";

                if (current->nodes[0])
                    q.push(current->nodes[0]);
                if (current->nodes[1])
                    q.push(current->nodes[1]);
            }
            cout << "| "; // Separador de niveles
        }
        cout << "\n";
    }
};

int main() {
    CBinTree<int> tree;
    /* Caso Left-Right
    tree.ins(20);
    tree.ins(10);
    tree.ins(15);
    Caso Right-Left
    tree.ins(20);
    tree.ins(30);
    tree.ins(25); */
    tree.ins(20);
    tree.ins(30);
    tree.ins(25);
    // tree.ins(15);
    // tree.ins(5);
    // tree.ins(55);
    cout << "Recorrido por niveles: \n";
    tree.levelOrderTraversalWithHeight();
    return 0;
}
/*FIN TAREA AVL TREE */
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
/*TAREA HEAP TREE */
#include <iostream>
#include <queue>

using namespace std;

template<class T>
class Max {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

template<class T>
class Min {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};


template <class T>
struct Node {
    T value;
    Node* nodes[2]; // Arreglo de punteros a Nodes
    Node* padre;

    Node(T valor, Node* pa = nullptr) {
        value = valor;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
        padre = pa;
    }
};

template <class T, class O>
class CHeapTree {
    Node<T>* root;
    Node<T>* last;
    O order;
public:
    CHeapTree() {
        root = nullptr;
        last = nullptr;
    }

    Node<T>* findEmptyParent(){
        if(root == nullptr) return root;
        queue<Node<T>*> cola;
        cola.push(root);

        while(!cola.empty()){
            int level = cola.size();
            for(int i = 0; i < level; i++){
                Node<T>* current = cola.front();
                cola.pop();
                if(current->nodes[0] == nullptr || current->nodes[1] == nullptr ) return current;
                if(current->nodes[0] != nullptr) cola.push(current->nodes[0]);
                if(current->nodes[1] != nullptr) cola.push(current->nodes[1]);
            }
        }
        return nullptr;
    }

    void ins(T v) {
        if(root == nullptr) {
            root = new Node<T>(v);
            last = root;
            return;
        }

        Node<T>* empty = findEmptyParent();

        if(empty->nodes[0] == nullptr) {
            empty->nodes[0] = new Node<T>(v, empty);
            last = empty->nodes[0];
        } else {
            empty->nodes[1] = new Node<T>(v, empty);
            last = empty->nodes[1];
        }

        Node<T>* current = last;
        while(current->padre != nullptr) {
            if(order(current->value, current->padre->value)) {
                swap(current->value, current->padre->value);
                current = current->padre;
            } else {
                break;
            }
        }
    }

    Node<T> * getMinMaxChild(Node<T>* p){
        Node<T> *q = order(p->nodes[0]->value,p->nodes[1]->value) ? p->nodes[0] : p->nodes[1];
        return q;
    }

    T pop() {
        if(root == nullptr) return 0;
        T valor_retorno = root->value;
        swap(last->value, root->value);

        Node<T> *p = root;
        Node<T> *q = nullptr;

        while((p->nodes[0] != nullptr || p->nodes[1] != nullptr)){
            q = getMinMaxChild(p);
            if(order(q->value, p->value)){
                swap(q->value, p->value);
            }
            p = q;
        }

        if (last->padre->nodes[0] == last) {
            last->padre->nodes[0] = nullptr;
        }
        if (last->padre->nodes[1] == last) {
            last->padre->nodes[1] = nullptr;
        }

        delete last;
        last = p;
        return valor_retorno;
    }

    void print() {
        if (root == nullptr) return;

        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node<T>* current = q.front();
                q.pop();
                cout << current->value << " ";
                if (current->nodes[0])
                    q.push(current->nodes[0]);
                if (current->nodes[1])
                    q.push(current->nodes[1]);
            }
            cout << "| \n"; // Separador de niveles
        }
        cout << "\n";
    }
};


int main() {
    CHeapTree<int, Max<int>> t;
    t.ins(10);
    t.ins(11);
    t.ins(16);
    t.ins(71);
    t.ins(78);
    t.ins(15);
    t.ins(118);
    t.print();

    return 0;
}
/*FIN TAREA HEAP TREE */
/*TAREA HEAP VECTOR */
/*
[80,72,30,62,55,10,20,47,73]
73: i = 8;
padre: (i-1)/2 = x=> (3): 62
padre del padre: (x-1)/2 = 1 (72) , el 3 es una variable j
padre del padre: (3-1)/2 = 1 (72) , el 3 es una variable j
hijos:
(j+1) * 2
(j+1) * 2 - 1

*/
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class great {
public:
    bool operator()(T A, T B) {
        return A > B;
    }
};

template <class T>
class lessi {
public:
    bool operator()(T A, T B) {
        return A < B;
    }
};

template <class T, class U>
struct CHeap {
    vector<T> heap;
    T max();
    void push(T x);
    T pop();
    U orden;
    void print();
};

template<class T, class U>
void CHeap<T, U>::push(T x) {
    if (heap.empty()) {
        heap.push_back(x);
    }
    else {
        heap.push_back(x);
        int i = heap.size() - 1;
        while (true) {
            int comp = (i - 1) / 2;
            if (orden(heap[i], heap[comp])) {
                swap(heap[i], heap[comp]);
                i = comp;
            }
            else { break; }
            if (i == 0) { break; }
        }
    }
}

template<class T, class U>
T CHeap<T, U>::max() {
    return heap.front();
}

template<class T, class U>
T CHeap<T, U>::pop() {
    int j = 0;
    int last = heap.size() - 1;
    swap(heap[last], heap[j]);
    heap.resize(last);

    while (true) {

        int h1 = j * 2 + 1;
        int h2 = j * 2 + 2;
        int next = j;

        if (h1 < heap.size() && orden(heap[h1], heap[j])) {
            next = h1;
        }
        if (h2 < heap.size() && orden(heap[h2], heap[next])) {
            next = h2;
        }
        if (next == j) break;
        swap(heap[j], heap[next]);
        j = next;
    }
    return heap.front();
}

template<class T, class U>
void CHeap<T, U>::print() {
    for (auto& value : heap) {
        cout << value << " ";
    }
    cout << endl;
}
int main() {
    CHeap<int, lessi<int>> max_heap;
    max_heap.push(80);
    max_heap.push(72);
    max_heap.push(30);
    max_heap.push(55);
    max_heap.push(10);
    max_heap.push(20);
    max_heap.push(47);
    max_heap.push(62);
    max_heap.push(73);
    max_heap.print();
    max_heap.pop();
    max_heap.print();
    return 0;
}
/*FIN TAREA HEAP VECTOR */
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
/*TAREA THREADS SUMA */
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void F1(int* ar, int n, int *s) {
    for ( int i = 0; i < n; i++) {
        *s += ar[i];
    }
}

int main() {

    int ar[16] = {2,6,3,1,7,8,9,6,4,3,2,8,9,11,13,1};
    int xsum[4] = {0,0,0,0};
    int sum = 0;

    int i = 0, nt = 4;

    vector<thread> ths(nt);

    for(i = 0; i < nt; i++)
        ths[i] = thread(F1, &ar[i * nt], nt, &xsum[i]);

    for(i = 0; i < nt; i++)
        ths[i].join();

    for(i = 0; i < nt; i++){
        sum += xsum[i];
    }
    cout<<"\n suma:"<<sum<<"\n";
   return 0;
}
/*FIN TAREA THREADS SUMA */
/*TAREA TREE AVL SFML */
#include <iostream>
#include <queue>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T> *nodes[2];
    int height = 0;
    Node(T v){
        data = v;
        nodes[0] = nodes[1] = 0;
        height = 1;
    }
};

template <class T>
class CBinTree {
private:
    bool brep = 0;

    Node<T>** rep(Node<T>**p) {
        Node<T>** q = &((*p)->nodes[!brep]);
        while((*q)->nodes[brep]){
            q = &(*q)->nodes[brep];
        }
        brep = !brep;
        return q;
    }

    bool find(T v,Node<T>**&p) {
        for(p = &root;
           *p && (*p)->data != v;
           p = &((*p)->nodes[(*p)->data < v])
        );
        return *p != 0;
    }
    int getHeight(Node<T>* n) {
        if (n == nullptr) return 0;
        return n->height;
    }
    void setHeight(Node<T>* n) {
        if (n == nullptr) return;
        // La altura es 1 + el máximo de las alturas de sus hijos
        n->height = 1 + max(getHeight(n->nodes[0]), getHeight(n->nodes[1]));
    }
   Node<T>* insertRec(Node<T>* node, T v) {
        // 1. Inserción normal BST
        if (node == nullptr) {
            return new Node<T>(v);
        }

        if (v < node->data) {
            node->nodes[0] = insertRec(node->nodes[0], v);
        }
        else if (v > node->data) {
            node->nodes[1] = insertRec(node->nodes[1], v);
        }
        else {
            return node; // Valor duplicado
        }

        // 2. Actualizar altura
        setHeight(node);

         // 3. Obtener factor de balance
        int balance = getBalance(node);

        // 4. Casos de rotación

        // Caso Izquierda-Izquierda
        if (balance > 1 && v < node->nodes[0]->data) {
            return rotateRight(node);
        }

        // Caso Derecha-Derecha
        if (balance < -1 && v > node->nodes[1]->data) {
            return rotateLeft(node);
        }

        // Caso Izquierda-Derecha
        if (balance > 1 && v > node->nodes[0]->data) {
            return rotateLeftRight(node);
        }

        // Caso Derecha-Izquierda
        if (balance < -1 && v < node->nodes[1]->data) {
            return rotateRightLeft(node);
        }

        return node;
    }

    int getBalance(Node<T>* n) {
        if (n == nullptr) return 0;
        return getHeight(n->nodes[0]) - getHeight(n->nodes[1]);
    }
     Node<T>* rotateRight(Node<T>* y) {
        if (y == nullptr || y->nodes[0] == nullptr) return y;

        Node<T>* x = y->nodes[0];    // x es hijo izquierdo de y
        Node<T>* T2 = x->nodes[1];   // T2 es hijo derecho de x

        // Realizar rotación
        x->nodes[1] = y;             // y se vuelve hijo derecho de x
        y->nodes[0] = T2;            // T2 se vuelve hijo izquierdo de y

        // Actualizar alturas
        setHeight(y);                // Primero actualizar y porque ahora es hijo
        setHeight(x);                // Después x porque ahora es padre

        return x;                    // Nueva raíz del subárbol
    }

    Node<T>* rotateLeft(Node<T>* x) {
        if (x == nullptr || x->nodes[1] == nullptr) return x;

        Node<T>* y = x->nodes[1];    // y es hijo derecho de x
        Node<T>* T2 = y->nodes[0];   // T2 es hijo izquierdo de y

        // Realizar rotación
        y->nodes[0] = x;             // x se vuelve hijo izquierdo de y
        x->nodes[1] = T2;            // T2 se vuelve hijo derecho de x

        // Actualizar alturas
        setHeight(x);                // Primero actualizar x porque ahora es hijo
        setHeight(y);                // Después y porque ahora es padre

        return y;                    // Nueva raíz del subárbol
    }
    Node<T>* rotateLeftRight(Node<T>* node) {
        if (node == nullptr) return node;

        // Primero rotación izquierda en el hijo izquierdo
        node->nodes[0] = rotateLeft(node->nodes[0]);

        // Luego rotación derecha en el nodo actual
        return rotateRight(node);
    }

    Node<T>* rotateRightLeft(Node<T>* node) {
        if (node == nullptr) return node;

        // Primero rotación derecha en el hijo derecho
        node->nodes[1] = rotateRight(node->nodes[1]);

        // Luego rotación izquierda en el nodo actual
        return rotateLeft(node);
    }


public:
    Node<T> * root;
    CBinTree(){
        root = 0;
    }

    bool ins(T v){
        Node<T> ** p;
        if(find(v,p))return 0;
        *p = new Node<T>(v);
        Node<T>* before = root;
        root = insertRec(root, v);
        return root != before;
    }


    bool rem(T v){
        Node<T> **p;
        if(!find(v, p)) return 0;
        if((*p)->nodes[0] && (*p)->nodes[1]){
            Node<T> ** q = rep(p);
            (*p)->data = (*q)->data;
            p = q;
        }
        Node<T> * temp = *p;
        (*p) = (*p)->nodes[(*p)->nodes[1] != 0];
        delete temp;
        return 1;
    }
    void levelOrderTraversalWithHeight() {
    if (root == nullptr) return;
    queue<Node<T>*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            Node<T>* current = q.front();
            q.pop();
            // Mostramos el valor y la altura del nodo
            cout << current->data << "(h:" << current->height
                 << ",b:" << getBalance(current) << ") ";
            if (current->nodes[0])
                q.push(current->nodes[0]);
            if (current->nodes[1])
                q.push(current->nodes[1]);
        }
        cout << "| "; // Separador de niveles
    }
    cout << "\n";
}
    void levelOrderTraversal() {
        if (root == nullptr) return;

        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node<T>* current = q.front();
                q.pop();
                cout << current->data << " ";

                if (current->nodes[0])
                    q.push(current->nodes[0]);
                if (current->nodes[1])
                    q.push(current->nodes[1]);
            }
            cout << "| "; // Separador de niveles
        }
        cout << "\n";
    }
};

int main() {
    CBinTree<int> tree;
    tree.ins(20);
    tree.ins(10);
    tree.ins(30);
    cout << "Recorrido por niveles: ";
    tree.levelOrderTraversalWithHeight();
    return 0;
}
/*FIN TAREA TREE AVL SFML */
/*FUNCIONES AUXILIARES */
//si un nodo es una hoja
bool isLeaf(Node<T>* node) {
    return node && !node->nodes[0] && !node->nodes[1];
}
//si un nodo esta en el contorno izquierdo del arbol
bool isLeft(Node<T>* node) {
    Node<T>** q = &(root->nodes[0]);
    while((*q)->nodes[0]){
        if(node->data == (*q)->data) {
            return true;
        }
        q = &(*q)->nodes[0];
    }
    return false;
}
//si un nodo esta en el contorno derecho del arbol
bool isRight(Node<T>* node) {
    Node<T>** q = &(root->nodes[1]);
    while((*q)->nodes[1]){
        if(node->data == (*q)->data) {
            return true;
        }
