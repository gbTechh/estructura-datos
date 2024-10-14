/*
Implementar, en un árbol binario de búsqueda,
el recorrido por niveles en un árbol binario de búsqueda utilizando std::queue.
*/

#include <iostream>
#include <queue>
using namespace std;

template <class T>
struct Node {
    T data;
    Node<T> *nodes[2];

    Node(T v){
        data = v;
        nodes[0] = nodes[1] = 0;
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


public:
    Node<T> * root;
    CBinTree(){
        root = 0;
    }

    bool ins(T v){
        Node<T> ** p;
        if(find(v,p))return 0;
        *p = new Node<T>(v);
        return 1;
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
    tree.ins(65);
    tree.ins(49);
    tree.ins(79);
    tree.ins(37);
    tree.ins(55);
    tree.ins(73);
    tree.ins(85);
    tree.ins(33);
    tree.ins(53);
    tree.ins(56);
    cout << "Recorrido por niveles: ";
    tree.levelOrderTraversal();
    return 0;
}
