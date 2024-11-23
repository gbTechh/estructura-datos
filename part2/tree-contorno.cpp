#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

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

    // Nueva función auxiliar para determinar si un nodo es hoja
    bool isLeaf(Node<T>* node) {
        return node && !node->nodes[0] && !node->nodes[1];
    }
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
    bool isRight(Node<T>* node) {
        Node<T>** q = &(root->nodes[1]);
        while((*q)->nodes[1]){
            if(node->data == (*q)->data) {
                return true;
            }
            q = &(*q)->nodes[1];
        }
        return false;
    }
public:
    Node<T> * root;
    CBinTree(){
        root = 0;
    }

    bool ins(T v){
        Node<T> ** p;
        if(find(v,p)) return 0;
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

    void drawTree(sf::RenderWindow &window, Node<T> *node, int x, int y, int offsetX, int level) {
        if (!node) return;

        int radius = 20; // Radio del círculo que representa el nodo

        // Dibujar conexión con el hijo izquierdo
        if (node->nodes[0]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x - offsetX, y + 100))
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->nodes[0], x - offsetX, y + 100, offsetX / 2, level + 1);
        }

        // Dibujar conexión con el hijo derecho
        if (node->nodes[1]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x + offsetX, y + 100))
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->nodes[1], x + offsetX, y + 100, offsetX / 2, level + 1);
        }

        // Dibujar el nodo como un círculo
        sf::CircleShape circle(radius);

        // Determinar el color del nodo
        if (node == root || isLeaf(node) || isLeft(node) || isRight(node)) {

            circle.setFillColor(sf::Color::Red); // Color rojo para raíz y hojas
        } else {
            circle.setFillColor(sf::Color::Blue); // Color azul para nodos internos
        }

        circle.setPosition(x - radius, y - radius);

        // Dibujar el valor dentro del nodo
        sf::Font font;
        if (!font.loadFromFile("./part2/arial.ttf")) {
            cout << "Error cargando la fuente" << endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(to_string(node->data));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);

        // Centrar el texto en el círculo
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        text.setPosition(x, y);

        window.draw(circle);
        window.draw(text);;
    }

    void draw(sf::RenderWindow &window) {
        drawTree(window, root, 400, 50, 200, 0);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 800), "Arbol Binario - SFML");

    CBinTree<int> tree;
    tree.ins(10);
    tree.ins(5);
    tree.ins(15);
    tree.ins(1);
    tree.ins(3);
    tree.ins(1);
    tree.ins(7);
    tree.ins(6);
    tree.ins(8);
    tree.ins(5);
    tree.ins(3);
    tree.ins(14);
    tree.ins(19);
    tree.ins(15);
    tree.ins(12);
    tree.ins(17);
    tree.ins(16);
    tree.ins(20);
    tree.ins(28);
    tree.ins(14);
    tree.ins(11);
    tree.ins(0);
    tree.ins(13);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        tree.draw(window);
        window.display();
    }

    return 0;
}
