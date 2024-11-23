
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <class T>
struct Node {
    T data;
    Node<T>* nodes[2];
    Node(T v) {
        data = v;
        nodes[0] = nodes[1] = 0;
    }
};

template <class T>
class CBinTree {
private:
    bool brep = 0;
    T targetValue; // Valor para el cual queremos encontrar tíos y primos

    Node<T>** rep(Node<T>** p) {
        Node<T>** q = &((*p)->nodes[!brep]);
        while ((*q)->nodes[brep]) {
            q = &(*q)->nodes[brep];
        }
        brep = !brep;
        return q;
    }

    bool find(T v, Node<T>**& p) {
        for (p = &root;
            *p && (*p)->data != v;
            p = &((*p)->nodes[(*p)->data < v])
            );
        return *p != 0;
    }

    // Encuentra el padre de un nodo con valor dado
    Node<T>* findParent(Node<T>* current, T value) {
        if (!current) return nullptr;

        // Si alguno de los hijos es el valor que buscamos
        if ((current->nodes[0] && current->nodes[0]->data == value) ||
            (current->nodes[1] && current->nodes[1]->data == value)) {
            return current;
        }

        // Buscar recursivamente
        Node<T>* leftResult = findParent(current->nodes[0], value);
        if (leftResult) return leftResult;

        return findParent(current->nodes[1], value);
    }

    vector<T> findUncles(T value) {
        vector<T> uncles;
        Node<T>* parent = findParent(root, value);
        if (!parent) return uncles;

        // Encontrar el nivel del padre
        int parentLevel = getNodeLevel(root, parent->data, 0);

        // Encontrar todos los nodos en el mismo nivel que el padre
        getAllNodesAtLevel(root, parentLevel, uncles);

        // Remover al padre de la lista de tíos
        uncles.erase(remove(uncles.begin(), uncles.end(), parent->data), uncles.end());

        return uncles;
    }

    // Encuentra el nivel de un nodo en el árbol
    int getNodeLevel(Node<T>* node, T value, int level) {
        if (!node) return -1;

        if (node->data == value)
            return level;

        int leftLevel = getNodeLevel(node->nodes[0], value, level + 1);
        if (leftLevel != -1)
            return leftLevel;

        return getNodeLevel(node->nodes[1], value, level + 1);
    }

    // Obtiene todos los nodos en un nivel específico
    void getAllNodesAtLevel(Node<T>* node, int targetLevel, vector<T>& nodes, int currentLevel = 0) {
        if (!node) return;

        if (currentLevel == targetLevel) {
            nodes.push_back(node->data);
            return;
        }

        getAllNodesAtLevel(node->nodes[0], targetLevel, nodes, currentLevel + 1);
        getAllNodesAtLevel(node->nodes[1], targetLevel, nodes, currentLevel + 1);
    }

    // Encuentra todos los hijos de los tíos (primos)
    vector<T> findCousins(T value) {
        vector<T> cousins;
        vector<T> uncles = findUncles(value);

        for (T uncleValue : uncles) {
            Node<T>* uncle = nullptr;
            Node<T>** p;
            if (find(uncleValue, p)) {
                uncle = *p;
                // Agregar todos los hijos del tío
                if (uncle->nodes[0])
                    cousins.push_back(uncle->nodes[0]->data);
                if (uncle->nodes[1])
                    cousins.push_back(uncle->nodes[1]->data);
            }
        }

        return cousins;
    }



public:
    Node<T>* root;
    CBinTree() {
        root = 0;
        targetValue = T();
    }

    // Función para establecer el valor objetivo
    void setTargetValue(T value) {
        targetValue = value;
    }

    bool ins(T v) {
        Node<T>** p;
        if (find(v, p)) return 0;
        *p = new Node<T>(v);
        return 1;
    }

    bool rem(T v) {
        Node<T>** p;
        if (!find(v, p)) return 0;
        if ((*p)->nodes[0] && (*p)->nodes[1]) {
            Node<T>** q = rep(p);
            (*p)->data = (*q)->data;
            p = q;
        }
        Node<T>* temp = *p;
        (*p) = (*p)->nodes[(*p)->nodes[1] != 0];
        delete temp;
        return 1;
    }

    void drawTree(sf::RenderWindow& window, Node<T>* node, int x, int y, int offsetX, int level) {
        if (!node) return;

        int radius = 20;

        // Dibujar conexiones
        if (node->nodes[0]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x - offsetX, y + 100))
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->nodes[0], x - offsetX, y + 100, offsetX / 2, level + 1);
        }

        if (node->nodes[1]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x + offsetX, y + 100))
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, node->nodes[1], x + offsetX, y + 100, offsetX / 2, level + 1);
        }

        // Obtener tíos y primos del valor objetivo
        vector<T> uncles = findUncles(targetValue);
        vector<T> cousins = findCousins(targetValue);

        // Dibujar el nodo
        sf::CircleShape circle(radius);

        // Determinar el color del nodo
        sf::Color nodeColor = sf::Color::Blue; // Color por defecto

        // Si es un tío, pintar de verde
        for (T uncle : uncles) {
            if (node->data == uncle) {
                nodeColor = sf::Color::Green;
                break;
            }
        }

        // Si es un primo, pintar de amarillo
        for (T cousin : cousins) {
            if (node->data == cousin) {
                nodeColor = sf::Color::Cyan;
                break;
            }
        }

        // Si es el nodo objetivo, pintar de rojo
        if (node->data == targetValue) {
            nodeColor = sf::Color::Red;
        }

        circle.setFillColor(nodeColor);
        circle.setPosition(x - radius, y - radius);

        // Dibujar el texto
        sf::Font font;
        if (!font.loadFromFile("./part2/arial.ttf")) {
            cout << "Error cargando la fuente" << endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(to_string(node->data));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(x, y);

        window.draw(circle);
        window.draw(text);
    }

    void draw(sf::RenderWindow& window) {
        drawTree(window, root, 400, 50, 200, 0);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arbol Binario - SFML");

    CBinTree<int> tree;
    tree.ins(10);
    tree.ins(3);
    tree.ins(16);
    tree.ins(1);
    tree.ins(6);
    tree.ins(13);
    tree.ins(4);
    tree.ins(7);
    tree.ins(5);
    tree.ins(1);
    tree.ins(3);
    tree.ins(4);
    tree.ins(2);
    tree.ins(7);
    tree.ins(8);
    tree.ins(13);
    tree.ins(12);
    tree.ins(11);
    tree.ins(14);
    tree.ins(18);
    tree.ins(17);
    tree.ins(19);

    // Establecer el valor para el cual queremos ver tíos y primos
    tree.setTargetValue(7);  // Puedes cambiar este valor según quieras

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
