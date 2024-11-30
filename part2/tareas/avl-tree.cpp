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
