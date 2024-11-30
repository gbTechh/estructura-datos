/*
MATRIZ DISPERSA 1: Considere el
siguiente programa representa una estructura "Sparse Matrix"
Implemente los metodos set, y get de la clase CSMatrix de tal manera
que el main funcione correctamente. Esta clase CSMatrix debe ser creada
sobre la base de la clase map STL
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class CSMatrix
{
public:
    CSMatrix(int dx, int dy);
    bool set(int x, int y, int value);
    int get(int x, int y);
    void print();

private:
    vector<map<int,int>> matrix; // declarando matrix
    int dimx, dimy;
};

CSMatrix::CSMatrix(int dx, int dy)
{
    dimx = dx; dimy = dy;
    matrix.resize(dimx);

}

bool CSMatrix::set(int x, int y, int value)
{
    // si value es 0 borrar, si no actualizar
    if(x >= dimx || y >= dimy || x < 0 || y < 0)
        return false;
    auto &map = matrix[x];

    if(value == 0) {
        map.erase(y);
        return true;
    }
    map[y] = value;

    return true;
}

int CSMatrix::get(int x, int y)
{
    if(x >= dimx || y >= dimy || x < 0 || y < 0)
        return 0;
    auto &map = matrix[x];
    int val = map[y];
    auto it = map.find(y);  // Busca sin insertar
    return (it != map.end()) ? it->second : 0;
}

void CSMatrix::print()
{
    std::cout << "\n";
    for (int x = 0; x < dimx; x++)
    {
        for (int y = 0; y < dimy; y++)
        {
            std::cout << get(x,y) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main()
{
    CSMatrix m(8,8);
    m.set(2, 1, 5);
    m.set(2, 3, 2);
    m.set(2, 5, 7);
    m.set(5, 3, 9);
    m.set(7, 3, 12);
    m.set(1, 4, 3);
    m.set(2, 4, 0);
    m.set(5, 5, 8);
    m.set(3, 6, 1);
    m.print();
    m.set(1, 4, 0);
    m.set(2, 3, 0);
    m.set(4, 3, 0);
    m.set(0, 1, 0);
    m.print();
    std::cout << "\n 0,0 => " << m.get(0, 0);
    std::cout<< "\n 3,5 => " << m.get(3, 5);
    std::cout<< "\n 7,3 => " << m.get(7, 3);

    cout<<"\n";
 }
/*FIN MATRIZ DISPERSA 1 - USO DE MAP */
