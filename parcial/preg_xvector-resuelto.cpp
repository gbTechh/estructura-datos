#include <iostream>
#include <cstring> // Para memcpy

class XVector
{
public:
    XVector(int size_map, int size_vec);
    ~XVector();
    void push_back(int value);
    void push_front(int value);
    int& operator[](int index);

    int** map;
    int size_map, size_vec;
    int front_index, back_index;
    int size;

private:
    void resize_map();
};

XVector::XVector(int sm, int sv) : size_map(sm), size_vec(sv), front_index(sm/2), back_index(sm/2-1), size(0)
{
    map = new int*[size_map];
    for (int i = 0; i < size_map; ++i) {
        map[i] = new int[size_vec];
    }
}

XVector::~XVector()
{
    for (int i = 0; i < size_map; ++i) {
        delete[] map[i];
    }
    delete[] map;
}

void XVector::push_back(int value)
{
    if ((back_index + 1) % size_map == front_index) {
        resize_map();
    }
    back_index = (back_index + 1) % size_map;
    map[back_index][size % size_vec] = value;
    ++size;
}

void XVector::push_front(int value)
{
    if ((front_index - 1 + size_map) % size_map == back_index) {
        resize_map();
    }
    front_index = (front_index - 1 + size_map) % size_map;
    map[front_index][size % size_vec] = value;
    ++size;
}

int& XVector::operator[](int index)
{
    int map_index = (front_index + index / size_vec) % size_map;
    int vec_index = index % size_vec;
    return map[map_index][vec_index];
}

void XVector::resize_map()
{
    int new_size_map = size_map * 2;
    int** new_map = new int*[new_size_map];
    for (int i = 0; i < new_size_map; ++i) {
        new_map[i] = new int[size_vec];
    }

    int new_front_index = new_size_map / 2;
    for (int i = 0; i < size; ++i) {
        int old_map_index = (front_index + i / size_vec) % size_map;
        int old_vec_index = i % size_vec;
        int new_map_index = (new_front_index + i / size_vec) % new_size_map;
        int new_vec_index = i % size_vec;
        new_map[new_map_index][new_vec_index] = map[old_map_index][old_vec_index];
    }

    for (int i = 0; i < size_map; ++i) {
        delete[] map[i];
    }
    delete[] map;

    map = new_map;
    size_map = new_size_map;
    front_index = new_front_index;
    back_index = (new_front_index + size - 1) % new_size_map;
}

void print(XVector* p)
{ //no modificar esta función
    for ( int i = 0; i < p->size; i++ )
        std::cout<<(*p)[i]<<" ";
    std::cout<<"\n";
}

int main()
{
    //no modificar esta función main
    XVector v(4,3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5); v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); v.push_back(77);
    print(&v);
}
