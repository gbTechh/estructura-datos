#include <iostream>
#include <vector>

using namespace std;

template<class T>
class CSparseMatrix {
private:
    struct Node {
        int x, y;
        T value;
        Node* right;
        Node* bottom;

        Node(int _x, int _y, T _value) :
            x(_x), y(_y), value(_value), right(nullptr), bottom(nullptr) {}
    };

    std::vector<Node*> rows;  // Vector de punteros a nodos para filas
    std::vector<Node*> cols;  // Vector de punteros a nodos para columnas
    int n_rows, n_cols;

    // Encuentra posición en la fila x
    Node** findX(int x, int y) {
        Node** p = &rows[x];
        while (*p && (*p)->y < y)
            p = &((*p)->right);
        return p;
    }

    // Encuentra posición en la columna y
    Node** findY(int x, int y) {
        Node** p = &cols[y];
        while (*p && (*p)->x < x)
            p = &((*p)->bottom);
        return p;
    }

public:
    CSparseMatrix(int rows, int cols) : n_rows(rows), n_cols(cols) {
        this->rows.resize(rows, nullptr);  // Inicializa vector de filas con nullptr
        this->cols.resize(cols, nullptr);  // Inicializa vector de columnas con nullptr
    }

    ~CSparseMatrix() {
        // Liberar memoria
        for(size_t i = 0; i < rows.size(); i++) {
            Node* current = rows[i];
            while(current) {
                Node* next = current->right;
                delete current;
                current = next;
            }
        }
    }

    void set(int x, int y, T value) {
        if(x < 0 || x >= n_rows || y < 0 || y >= n_cols) return;

        Node** px = findX(x, y);
        Node** py = findY(x, y);

        if(*px && (*px)->y == y) {
            if(value == T()) {
                // Eliminar nodo
                Node* temp = *px;
                *px = temp->right;
                *py = temp->bottom;
                delete temp;
            } else {
                // Actualizar valor
                (*px)->value = value;
            }
        }
        else if(value != T()) {
            // Crear nuevo nodo
            Node* newNode = new Node(x, y, value);
            // Insertar en lista horizontal
            newNode->right = *px;
            *px = newNode;
            // Insertar en lista vertical
            newNode->bottom = *py;
            *py = newNode;
        }
    }

    T get(int x, int y) const {
        if(x < 0 || x >= n_rows || y < 0 || y >= n_cols) return T();

        Node* p = rows[x];
        while(p && p->y < y)
            p = p->right;

        return (p && p->y == y) ? p->value : T();
    }

    T operator()(int x, int y) const {
        return get(x, y);
    }
};

int main() {
    CSparseMatrix<int> m(5, 5);  // Matriz 5x5

    // Insertar algunos valores
    m.set(0, 0, 2);
    m.set(0, 2, 3);
    m.set(1, 1, 4);
    m.set(2, 2, 5);
    m.set(3, 1, 6);

    // Imprimir la matriz
    cout << "Matriz inicial:\n";
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cout << m(i, j) << " ";  // Usando el operador()
        }
        cout << endl;
    }

    // Modificar valores existentes
    m.set(0, 0, 7);    // Actualizar
    m.set(1, 1, 0);    // Eliminar (poner 0)
    m.set(2, 3, 8);    // Insertar nuevo

    cout << "\nDespués de modificaciones:\n";
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cout << m(i, j) << " ";
        }
        cout << endl;
    }

    // Probar gets específicos
    cout << "\nValores específicos:\n";
    cout << "m(0,0): " << m.get(0, 0) << endl;  // Debe mostrar 7
    cout << "m(1,1): " << m.get(1, 1) << endl;  // Debe mostrar 0
    cout << "m(2,3): " << m.get(2, 3) << endl;  // Debe mostrar 8
    cout << "m(4,4): " << m.get(4, 4) << endl;  // Debe mostrar 0

    return 0;
}
