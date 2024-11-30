/**
MATRIZ DISPERSA 3 - STL : Se pide implementar los metodos SET y GET
de la matriz, apra que las instrucicones del main funcionen correcamente
*/
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <class T, T NE>
class CSparseMatrix
{
    typedef unsigned int uint;
    typedef T value_type;
public:
    CSparseMatrix(uint xdim, uint ydim);
    void Set(uint x, uint y, T value);
    T    Get(uint x, uint y);
    void Print();

private:
    vector< list<T> > matrix;
    uint m_XDim, m_YDim;
};

template <class T, T NE>
CSparseMatrix<T,NE>::CSparseMatrix(uint xdim, uint ydim)
{
    m_XDim = xdim; m_YDim = ydim;
    matrix.resize(m_XDim);
}

template <class T, T NE>
void CSparseMatrix<T,NE>::Set(uint x, uint y, T value)
{
    // Verificar límites de la matriz
    if (x >= m_XDim || y >= m_YDim) return;

    // Obtener referencia a la lista en la fila x
    list<T>& row = matrix[x];

    // Si el valor es NE (elemento nulo), debemos eliminar el par si existe
    if (value == NE) {
        // Recorrer la lista de dos en dos buscando la coordenada y
        for (auto it = row.begin(); it != row.end(); ) {
            auto coord = it;  // Primer elemento del par (coordenada y)
            auto val = ++it;  // Segundo elemento del par (valor)

            if (coord != row.end() && val != row.end() && *coord == y) {
                // Eliminar tanto la coordenada como el valor
                it = row.erase(coord, ++val);
                return;
            }
        }
        return;
    }

    // Para insertar o actualizar un valor no nulo
    for (auto it = row.begin(); it != row.end(); ) {
        auto coord = it;      // Coordenada y actual
        auto val = ++it;      // Valor actual

        if (coord != row.end() && val != row.end()) {
            if (*coord == y) {
                // Actualizar valor existente
                *val = value;
                return;
            }
            ++it;  // Avanzar al siguiente par
        }
    }

    // Si llegamos aquí, debemos insertar un nuevo par
    row.push_back(y);    // Insertar coordenada y
    row.push_back(value); // Insertar valor
}

template <class T, T NE>
typename CSparseMatrix<T,NE>::value_type CSparseMatrix<T,NE>::Get(uint x, uint y)
{
    // Verificar límites de la matriz
    if (x >= m_XDim || y >= m_YDim) return NE;

    // Obtener referencia a la lista en la fila x
    const list<T>& row = matrix[x];

    // Recorrer la lista de dos en dos buscando la coordenada y
    auto it = row.begin();
    while (it != row.end()) {
        T coord = *it;    // Coordenada y
        ++it;
        if (it == row.end()) break;  // Verificación de seguridad
        T val = *it;      // Valor
        ++it;

        if (coord == y) return val;
    }

    // Si no encontramos la coordenada, retornar el elemento nulo
    return NE;
}

template <class T, T NE>
void CSparseMatrix<T,NE>::Print()
{
    int xi, yi;
    for (yi = 0; yi < m_YDim; yi++)
    {
        for (xi = 0; xi < m_XDim; xi++)
        {
            T value = Get(yi,xi);
            cout<< value<<" ";
        }
        cout<<endl;
    }
    cout<<"---"<<endl;
}


int main(int argc, const char * argv[])
{
    CSparseMatrix<int,0> m(5,5);

    m.Set(0,0,2);   m.Set(2,0,0);   m.Set(3,1,5);
    m.Set(1,2,6);   m.Set(2,2,7);   m.Set(3,2,0);
    m.Set(4,2,9);   m.Set(1,3,1);   m.Set(0,4,0);
    m.Set(3,4,8);
    m.Print();

    m.Set(3,1,0);   m.Set(1,2,0);   m.Set(0,4,0);
    m.Set(4,4,0);
    m.Print();

    return 0;
}
/*FIN MATRIZ DISPERSA 3 - STL */
