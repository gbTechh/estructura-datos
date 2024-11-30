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
