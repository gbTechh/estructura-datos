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
