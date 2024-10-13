#include <iostream>

template <class T>
struct CForwardNode
{
    CForwardNode(T x)
    {   value = x;  next = 0;   }
    T value;
    CForwardNode<T>* next;
};

template <class T>
class CForwardList
{
public:
    CForwardList();
    ~CForwardList();
    bool Find(T x, CForwardNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    void Print();
private:
    CForwardNode<T>* head;
};

template <class T>
CForwardList<T>::CForwardList()
{
    head = 0;
}

template <class T>
CForwardList<T>::~CForwardList()
{
    //...
}

template <class T>
bool CForwardList<T>::Find(T x, CForwardNode<T>**& p)
{
    for ( p = &head; *p && (*p)->value < x; p = &(*p)->next );
    return *p && (*p)->value == x;
}

template <class T>
bool CForwardList<T>::Ins(T x)
{
    CForwardNode<T>** p;
    if ( Find(x,p) ) return 0;
    CForwardNode<T>* t = new CForwardNode<T>(x);
    t->next = *p;
    *p = t;
    return 1;
}

template <class T>
bool CForwardList<T>::Rem(T x)
{
    CForwardNode<T>** p;
    if ( !Find(x,p) ) return 0;
    CForwardNode<T>* t = *p;
    *p = t->next;
    delete t;
    return 1;
}

template <class T>
void CForwardList<T>::Print()
{
    for ( CForwardNode<T>* t = head; t ; t = t->next )
        std::cout<<t->value<<" ";
    std::cout<<"\n";
}

void proc1(CForwardList<int>* l)
{//function objects
    
}

void proc2(CForwardList<int>* l)
{//polimorfismo
    
}

int main()
{
    CForwardList<int> l;
    l.Ins(6);   l.Ins(18);  l.Ins(26);  l.Ins(17);
    l.Ins(3);   l.Ins(4);   l.Ins(27);  l.Ins(30);
    l.Ins(7);   l.Ins(11);  l.Ins(24);  l.Ins(25);
    l.Ins(1);   l.Ins(2);   l.Print();
    proc1(&l);  l.Print();
    proc2(&l);  l.Print();
}
