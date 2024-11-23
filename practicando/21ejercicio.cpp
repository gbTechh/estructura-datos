#include <iostream>
#include <stack>
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

    void inOrderStack() {
        stack<Node<T>*> s;
        Node<T>* current = root;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->nodes[0];
            }

            current = s.top();
            s.pop();

            cout << current->data << " ";

            current = current->nodes[1];
        }
        cout << "\n";
    }

    void preOrderStack() {
        if (root == nullptr) return;

        stack<Node<T>*> s;
        s.push(root);

        while (!s.empty()) {
            Node<T>* current = s.top();
            s.pop();

            cout << current->data << " ";

            if (current->nodes[1])
                s.push(current->nodes[1]);
            if (current->nodes[0])
                s.push(current->nodes[0]);
        }
        cout << "\n";
    }

    void postOrderStack() {
        if (root == nullptr) return;

        stack<Node<T>*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node<T>* current = s1.top();
            s1.pop();
            s2.push(current);

            if (current->nodes[0])
                s1.push(current->nodes[0]);
            if (current->nodes[1])
                s1.push(current->nodes[1]);
        }

        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << "\n";
    }

    // Las funciones originales se mantienen por compatibilidad
    void inOrder(Node<T> * n) {
        if(!n) return;
        inOrder(n->nodes[0]);
        cout<<n->data<<" ";
        inOrder(n->nodes[1]);
    }
    void preOrden(Node<T> * n) {
        if(!n) return;
        cout<<n->data<<" ";
        preOrden(n->nodes[0]);
        preOrden(n->nodes[1]);
    }
    void postOrden(Node<T> * n) {
        if(!n) return;
        postOrden(n->nodes[0]);
        postOrden(n->nodes[1]);
        cout<<n->data<<" ";
    }
    void reverse(Node<T> * n) {
        if(!n) return;
        reverse(n->nodes[1]);
        cout<<n->data<<" ";
        reverse(n->nodes[0]);
    }
    void print() {
        inOrder(root);
        cout<<"\n";
    }
    void printPre() {
        preOrden(root);
        cout<<"\n";
    }
    void printPost() {
        postOrden(root);
        cout<<"\n";
    }
    void printReverse() {
        reverse(root);
        cout<<"\n";
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

    cout << "Inorder (recursivo): ";
    tree.print();
    cout << "Inorder (con stack): ";
    tree.inOrderStack();

    cout << "Preorder (recursivo): ";
    tree.printPre();
    cout << "Preorder (con stack): ";
    tree.preOrderStack();

    cout << "Postorder (recursivo): ";
    tree.printPost();
    cout << "Postorder (con stack): ";
    tree.postOrderStack();

    cout << "Reverse: ";
    tree.printReverse();

    return 0;
}
