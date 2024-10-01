#include <iostream>
using namespace std;


template<class T>
struct Node {
    T data;
    Node<T> *right;
    Node<T> *left;
    // 1 derecha - 0 izquierda
    Node(T v, Node<T>* n = nullptr, bool d = false){
        data = v;
        if(d) {
            right = n;
        } else {
            left = n;
        }
    }
};

template<class T>
class Tree {
    private:
        Node<T>* root = nullptr;
    public:

    void add(T v, Node<T> * node) {
        Node<T>* p = root;
        if(!p) {
            root = new Node<T>(v, root);
        } else {
            if(p->data > v) {
                p->right = new Node<T>(v,p->right,1);
            } else {
                p->left = new Node<T>(v,p->left,0);
            }


        }
    }

    void print() {
        Node<T>* current = root;
        cout << current->data << "\n";
        // while (current != nullptr) {
        //     cout << current->left->data << "\n";
        //     cout << current->right->data << "\n";
        //     current = current->right;
        // }
        cout << "nullptr" << endl;
    }

};


int main() {

    Tree<int> tree;
    tree.add(50);
    tree.add(51);
    tree.print();
    return 0;
}
