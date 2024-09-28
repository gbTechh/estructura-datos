#include <iostream>
using namespace std;

template <class T, class D>
struct Bubble {
    void operator()(T* a, T* b) {
        D comparator;
        bool next = true;
        while (a < b && next) {
            next = false;
            for (T* p = a; p < b; p++) {
                if (comparator(*p, *(p + 1))) {
                    std::swap(*p, *(p + 1));
                    next = true;
                }
            }
        }
    }
};

template <class T>
class ASC {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

template <class T>
class DESC {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};




int main()
{

    int A[6] = { 5,4,6,1,3,8 };
    char B[6] = { 'c','e','a','f','b','d' };
    Bubble<int, ASC<int>> b;
    b(A, A + 5);

    cout << "BUBBLE SORT ASC: \n";
    for (int i = 0; i < 6; i++) {
        std::cout << A[i] << " ";
    }

    std::cout << "\nBUBBLE SORT DESC: \n";

    Bubble<char, DESC<char>> c;
    c(B, B + 5);

    for (int i = 0; i < 6; i++) {
        std::cout << B[i] << " ";
    }

    std::cout << "\n";





}
