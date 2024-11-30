#include <iostream>
#include <queue>
using namespace std;

template<class T>
class great {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

template<class T>
class lessi {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};

template<class T>
struct Nodo {
    T v;
    Nodo* node[2]; // Arreglo de punteros a Nodos
    Nodo* padre;

    Nodo(T valor, Nodo* pa) {
        v = valor;
        node[0] = nullptr;
        node[1] = nullptr;
        padre = pa;
    }
};

template<class T, class U>
class CBinTree {
public:
    Nodo<T>* root;
    Nodo<T>* last;
    U orden;
    CBinTree() {
        root = nullptr;
        last = nullptr;
    }

    void push(T v);
    T max();
    T pop();
    void print(Nodo<T>* r);
    Nodo<T>* Root();
};

template<class T, class U>
Nodo<T>* CBinTree<T, U>::Root() {
    return root;
}

template<class T, class U>
void CBinTree<T, U>::push(T v) {
    if (!root) {
        root = new Nodo<T>(v, nullptr);
        last = root;
    }
    else {
        Nodo<T>* newNode = nullptr;

        if (last->padre && last->padre->node[0] == last) {
            newNode = new Nodo<T>(v, last->padre);
            last->padre->node[1] = newNode;
        }
        else { // Necesitamos movernos más arriba para encontrar la posición más a la izquierda
            Nodo<T>* q = last;

            while (q->padre && q == q->padre->node[1]) {
                q = q->padre;
            }

            if (q->padre) {
                q = q->padre->node[1];
            }

            while (q != nullptr && q->node[0] != nullptr) {
                q = q->node[0];
            }

            newNode = new Nodo<T>(v, q);
            if (q) {
                q->node[0] = newNode; // Asegúrate de que q no sea nullptr antes de acceder a sus miembros
            }
        }
        last = newNode;
    }

    // HEAPIFY
    Nodo<T>* heapi = last;
    while (true) {
        if (heapi->padre && orden(heapi->v, heapi->padre->v)) {
            swap(heapi->v, heapi->padre->v);
            heapi = heapi->padre;
        }
        else { break; }
    }

}
template<class T, class U>
T CBinTree<T, U>::max() {
    return root->v;
}

template<class T, class U>
T CBinTree<T, U>::pop() {
    swap(root->v, last->v);

    Nodo<T>* del = last;

    //AQUI ACTUALIZAMOS EL NUEVO NODO LAST
    if (last == last->padre->node[1]) {
        last = last->padre->node[0];
        last->padre->node[1] = nullptr;
    }
    else {
        Nodo<T>* q = last;
        last->padre->node[0] = nullptr;

        while (q->padre && q == q->padre->node[0]) {
            q = q->padre;
        }

        if (q->padre) {
            q = q->padre->node[0];
        }

        while (q != nullptr && q->node[1] != nullptr) {
            q = q->node[1];
        }
        last = q;
    }
    //BORRAMOS EL NODO QUE TOMO EL VALOR DEL NODO MIN O MAX
    delete del;

    Nodo<T>* comp = root;
    Nodo<T>* nuevo = comp;
    while (true) {
        if (comp->node[0] && orden(comp->node[0]->v, comp->v)) {
            nuevo = comp->node[0];
        }
        if (comp->node[1] && orden(comp->node[1]->v, nuevo->v)) {
            nuevo = comp->node[1];
        }

        if (nuevo != comp) {
            swap(comp->v, nuevo->v);
            comp = nuevo;
        }
        else { break; }
    }
    return root->v;
}

template<class T, class U>
void CBinTree<T, U>::print(Nodo<T>* p) {
    if (root == nullptr) return;

    queue<Nodo<T>*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            Nodo<T>* current = q.front();
            q.pop();
            cout << current->v << " ";

            if (current->node[0])
                q.push(current->node[0]);
            if (current->node[1])
                q.push(current->node[1]);
        }
        cout << "| \n"; // Separador de niveles
    }
    cout << "\n";
}

int main() {
    CBinTree<int, great<int>> t;
    // t.push(10);
    // t.push(18);
    // t.push(2);
    // t.push(21);
    // t.push(20);
    // t.push(14);
    // t.push(12);
    // t.push(23);
    // t.push(31);
    t.push(10);
    t.push(20);
    t.push(30);
    t.push(5);
    t.push(15);
    t.push(17);
    t.push(22);
    t.push(7);
    t.print(t.Root());

    t.pop();
    t.print(t.Root());

    // t.push(1);
    // t.print(t.Root());
    return 0;
}
