
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    { value = _v; nodes[0] = nodes[1] = 0;  }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void sobrinos_de(int x);
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{   m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
    // ?
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for ( p = &m_root ;
         *p && (*p)->value != x ;
         p = &( (*p)->nodes[ (*p)->value < x ] ) );
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[0] == 0 ];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while( (*q)->nodes[m_b] )
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout<<endl;
}

void CBinTree::sobrinos_de(int x)
{
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    t.Insert(50); t.Insert(30); t.Insert(60);
    t.Insert(80); t.Insert(55); t.Insert(11);
    t.Insert(35); t.Insert(5);  t.Insert(14);
    t.Insert(32); t.Insert(48);
    t.Insert(51); t.Insert(56);
    t.Insert(70); t.Insert(85);
    t.Insert(1); t.Insert(6);
    t.Insert(12); t.Insert(16);
    t.Insert(31); t.Insert(33);
    t.Insert(42); t.Insert(49);
    
    t.Print();
    t.sobrinos_de(35);
    t.sobrinos_de(60);
    t.sobrinos_de(70);
    t.sobrinos_de(50);
    
    
}
