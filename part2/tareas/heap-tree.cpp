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
