
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
