// AVL MAXHEIGHT - THREADS
//IMPLEMENTAR el metodo MaxNodeHeight para calcular la altura de un nodo cualquiera
//Luego utilizar el metodo MaxNodeHeight en el metodo MaxHeight para calcular la altura
//maxma de todo el arbol, este metodo debe ser implementaod utilizando 4 threads
#include <iostream>
#include <queue>
#include <thread>

#include <chrono>
#include <random>
#include <iomanip>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CAVLNode
{
    CAVLNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0;  }
    int value;
    CAVLNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CAVLTree
{
public:
    CAVLTree();
    ~CAVLTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    int MaxNodeHeight(CAVLNode* n);
    int MaxHeight();

private:
    bool Find(int x, CAVLNode**& p);
    CAVLNode** Rep(CAVLNode** p);
    void InOrder(CAVLNode* n);
    CAVLNode* m_root;
};

CAVLTree::CAVLTree()
{   m_root = 0; }

CAVLTree::~CAVLTree()
{}

bool CAVLTree::Find(int x, CAVLNode**& p)
{
    for ( p = &m_root ; *p && (*p)->value != x ; p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CAVLTree::Insert(int x)
{
    CAVLNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CAVLNode(x);
    return 0;
}
bool CAVLTree::Remove(int x)
{
    CAVLNode** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CAVLNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CAVLNode* t = *p;
    *p = (*p)->nodes[ !(*p)->nodes[0] ];
    delete t;
    return 1;
}

CAVLNode** CAVLTree::Rep(CAVLNode** p)
{
    bool b = rand()%2;
    for( p = &( (*p)->nodes[b] ); (*p)->nodes[!b]; p = &( (*p)->nodes[!b] ) );
    return p;
}

void CAVLTree::InOrder(CAVLNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CAVLTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}

//======================================================
void MaxNodeHeightThread(CAVLNode* n, int& height) {
    if (!n) {
        height = 0;
        return;
    }
    queue<CAVLNode*> cola;
    cola.push(n);
    height = 0;

    while(!cola.empty()) {
        int level = cola.size();
        for(int i = 0; i < level; i++){
            CAVLNode* current = cola.front();
            cola.pop();
            if(current->nodes[0]){
                cola.push(current->nodes[0]);
            }
            if(current->nodes[1]){
                cola.push(current->nodes[1]);
            }
        }
        height++;
    }
}

//======================================================

int CAVLTree::MaxNodeHeight(CAVLNode* n) {
    int h;
    MaxNodeHeightThread(n, h);
    return h;
}

int CAVLTree::MaxHeight()
{
    if(m_root == nullptr) return 0;

    /*trhead */
    int nt = 4;
    int xheight[4] = {0,0,0,0};
    vector<thread> ths(nt);

    /*cola */
    queue<CAVLNode*> cola;
    cola.push(m_root);
    int h = 1;
    int hroot = 0;
    while(!cola.empty()) {
        int level = cola.size();
        if(h<3){
            for(int i = 0; i < level; i++){
                CAVLNode* current = cola.front();
                cola.pop();
                if(current->nodes[0]){
                    cola.push(current->nodes[0]);
                }
                if(current->nodes[1]){
                    cola.push(current->nodes[1]);
                }
            }
            hroot = h;

        }else{
            int height;
            //puede ser level: for(int i = 0; i < level; i++)
            for(int i = 0; i < 4; i++){
                CAVLNode* current = cola.front();
                cola.pop();
                ths[i] = thread(MaxNodeHeightThread, current, ref(xheight[i]));
            }
            //puede ser level: for(int i = 0; i < level; i++)
            for(int i = 0; i < 4; i++)
                ths[i].join();

        }

        h+=1;

    }

    int maxHeight = 0;
    for(int i = 0; i < nt; i++) {
        if(xheight[i] > maxHeight)
            maxHeight = xheight[i];
    }

    return maxHeight  + hroot;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    // int v[150] = {239, 389, 128, 46, 235, 65, 423, 417, 121, 451, 396, 331, 158, 100, 95, 353, 470, 207, 453, 156, 98, 160, 373, 44, 313, 284, 152, 131, 236, 340, 369, 408, 411, 174, 141, 69, 96, 451, 259, 28, 234, 158, 168, 100, 379, 1, 487, 307, 182, 486, 385, 221, 30, 305, 41, 115, 415, 227, 166, 85, 220, 446, 127, 66, 316, 298, 144, 446, 65, 425, 241, 160, 215, 346, 212, 341, 44, 452, 226, 168, 132, 230, 448, 173, 174, 483, 59, 237, 436, 28, 472, 2, 142, 194, 203, 355, 410, 78, 418, 489, 220, 258, 19, 411, 373, 216, 311, 31, 411, 357, 334, 205, 118, 471, 252, 291, 389, 40, 389, 437, 36, 134, 475, 401, 448, 133, 30, 251, 456, 220, 417, 302, 256, 34, 120, 115, 318, 459, 110, 251, 392, 360, 261, 389, 450, 122, 308, 188, 212, 37};
    // CAVLTree t;
    // for ( int i = 0; i < 150; i++ )
    //     t.Insert(v[i]);
    // t.Print();

    // cout<<"Max Height is: "<<t.MaxHeight()<<endl;
    //

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000000); // Rango de números entre 1 y 100000

    CAVLTree t;

    // Medir tiempo de inserción
    auto start_insert = chrono::high_resolution_clock::now();

    // Insertar 10000 números aleatorios
    for(int i = 0; i < 10000000; i++) {
        t.Insert(dis(gen));
    }

    auto end_insert = chrono::high_resolution_clock::now();
    chrono::duration<double> insert_time = end_insert - start_insert;

    cout << "Tiempo de inserción: " << fixed << setprecision(4)
            << insert_time.count() << " segundos" << endl;

    // Medir tiempo de cálculo de altura
    auto start_height = chrono::high_resolution_clock::now();

    int height = t.MaxHeight();

    auto end_height = chrono::high_resolution_clock::now();
    chrono::duration<double> height_time = end_height - start_height;

    cout << "Altura máxima: " << height << endl;
    cout << "Tiempo de cálculo de altura: " << fixed << setprecision(4)
            << height_time.count() << " segundos" << endl;

    //t.Print();

    return 0;
}
// FIN AVL MAXHEIGHT - THREADS
