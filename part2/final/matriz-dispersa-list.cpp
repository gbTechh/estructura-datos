/*
MATRIZ DISPERSA 2 - LIST: Considere el siguiente programa preg_sparse_matrix.cpp. En la clase SparseMatrix implemente el método set
que permita ingresar y actualizar elementos dentro de la Matriz Dispersa, la que debe ser implementada en
una lista enlazada de elementos Nodo. En método print, imprime los elementos dentro de la lista enlazada
que representa la matriz dispersa. En Main se proporciona una prueba en donde se llenará los elementos y
sus respectivas llamadas a la función print para comprobar el correcto funcionamiento de la matriz Dispersa.
En la clase SparseMatrix puede adicionar los métodos que considere pertinentes, sin embargo no debe
modificarse el método print.
*/
#include <iostream>

using namespace std;

class Nodo
{
public:
    int fil;
    int col;
    int dato;
    Nodo* next;
};

class SparseMatrix
{
public:
    Nodo* Mat = NULL;
    void set(int fil, int col, int dato);
    void print();
};

void SparseMatrix::set(int fil, int col, int dato) {
    // Si el dato es cero, debemos eliminar el nodo si existe
    if (dato == 0) {
        // Caso especial: lista vacía
        if (!Mat) return;

        // Caso especial: primer nodo debe ser eliminado
        if (Mat->fil == fil && Mat->col == col) {
            Nodo* temp = Mat;
            Mat = Mat->next;
            delete temp;
            return;
        }

        // Buscar y eliminar el nodo si existe
        for (Nodo* p = Mat; p->next != NULL; p = p->next) {
            if (p->next->fil == fil && p->next->col == col) {
                Nodo* temp = p->next;
                p->next = p->next->next;
                delete temp;
                return;
            }
        }
        return;
    }

    // Si la lista está vacía, crear el primer nodo
    if (!Mat) {
        Mat = new Nodo();
        Mat->fil = fil;
        Mat->col = col;
        Mat->dato = dato;
        Mat->next = NULL;
        return;
    }

    // Buscar si ya existe un nodo en esa posición
    for (Nodo* p = Mat; p != NULL; p = p->next) {
        if (p->fil == fil && p->col == col) {
            // Actualizar el dato existente
            p->dato = dato;
            return;
        }
    }

    // Si no existe, crear nuevo nodo al inicio de la lista
    Nodo* nuevo = new Nodo();
    nuevo->fil = fil;
    nuevo->col = col;
    nuevo->dato = dato;
    nuevo->next = Mat;
    Mat = nuevo;
}

void SparseMatrix::print()
{
    cout << "------Mat-----"<<endl;
    for (Nodo* p = Mat; p; p = p->next)
        cout << "[" << p->fil << "][" << p->col << "] = " << p->dato << endl;
    cout << "------FIN Mat-----"<<endl;
}

int main()
{
    SparseMatrix SM;

    int a[10][10] = { {0,10,20,30,40,50,60,70,80,90},
{10,20,30,40,50,60,70,0,80,90},
{10,20,30,0,50,60,70,80,90,0},
{20,10,90,0,10,20,60,70,80,0},
{30,20,90,10,20,30,70,0,80,10},
{30,20,0,10,20,30,70,80,90,10},
{80,20,20,20,0,60,0,90,90,0},
{70,10,30,30,0,70,70,80,80,0},
{0,20,30,20,10,70,0,80,80,10},
{80,20,90,30,10,0,80,90,90,10},
    };

    int b[10][10] = { {10,0,0,0,0,0,0,0,0,0},
{0,20,0,0,0,0,0,0,0,0},
{0,0,30,0,0,0,0,0,0,0},
{0,0,0,40,0,0,0,0,0,0},
{0,0,0,0,50,0,0,0,0,0},
{0,0,0,0,0,60,0,0,0,0},
{0,0,0,0,0,0,70,0,0,0},
{0,0,0,0,0,0,0,80,0,0},
{0,0,0,0,0,0,0,0,90,0},
{0,0,0,0,0,0,0,0,0,100},
    };

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, a[i][j]);

    SM.print();

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, b[i][j]);

    SM.print();

}

/*FIN MATRIZ DISPERSA 2 - LIST */
