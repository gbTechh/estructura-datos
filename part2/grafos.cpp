#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <class G>
struct CEdge {
    typedef typename G::Node Node;
    typedef typename G::E E;
    E value;
    Node nodes[2];
    bool dir; // 0: bidireccional  , 1: [0]->[1]
};

template <class G>
struct CNode {
    typedef typename G::Edge Edge;

    list<Edge *> edges;
};

template <class N, class E>
class CGraph {
    typedef CGraph<N,E> G;
    typedef CNode<G> Node;
    typedef CEdge<G> Edge;

    bool InsNode(N n);
    bool InsEdge(Node* a, Node* b, E e, bool dir);
    vector<Node*> nodes;

};

bool CGraph::InsNode(N n){

}


int main(){

    CGraph<char,int> g;

    return 0;
}
