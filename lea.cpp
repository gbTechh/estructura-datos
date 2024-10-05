#include <iostream>
using namespace std;

class nodo {
public:
    int array[5];
    nodo* next;
    nodo* prev;
    nodo(nodo* n = NULL, nodo* p = NULL) {
        next = n;
        prev = p;
    }
};
class LEA {
public:
    nodo* TAIL = NULL;
    nodo* HEAD = NULL;
    int* INI = NULL;
    int* FIN = NULL;
    void ADD(int digit) {
        if (HEAD == NULL) {
            HEAD = new nodo(HEAD, TAIL);
            TAIL = HEAD;
            INI = HEAD->array;
            FIN = INI;
            *FIN = digit;
        }
        else {
            int* pos_arr;
            nodo* ub_nodo;
            FIND(digit, pos_arr, ub_nodo);
            int* aux_arr = FIN;
            nodo* aux_nodo = TAIL;
            if(!FIND(digit, pos_arr,ub_nodo)){
              if (FIN == TAIL->array + 4) {
                  TAIL = new nodo(NULL, TAIL);
                  TAIL->prev->next = TAIL;
                  FIN = TAIL->array;
              }
              else {
                  FIN++;
              }
              if (aux_arr == pos_arr) {
                  *FIN = digit;
                  return;
              }
              if (!pos_arr && ub_nodo->prev) {
                  pos_arr = aux_nodo->prev->array + 4;
                  ub_nodo = ub_nodo->prev;
              }
              while (aux_arr > pos_arr) {
                  if (aux_arr == aux_nodo->array + 4) {
                      *(aux_nodo->next->array) = *aux_arr;
                      aux_arr--;
                  }
                  else if (aux_arr == INI) {
                      *(aux_arr + 1) = *aux_arr;
                      pos_arr = aux_arr;
                      *(aux_arr) = digit;
                      return;
                  }
                  else if (aux_arr == aux_nodo->array) {
                      *(aux_arr + 1) = *aux_arr;
                      aux_nodo = aux_nodo->prev;
                      aux_arr = aux_nodo->array + 4;
                  }
                  else {
                      *(aux_arr + 1) = *aux_arr;
                      aux_arr--;
                  }
              }
              if (aux_arr == aux_nodo->array + 4) {
                  *(aux_nodo->next->array) = digit;
              }
              else {
                  *(aux_arr + 1) = digit;
              }
          }
        }
    }
    void DEL(int digit) {
        if (!HEAD) {
            cout << "array no encontrado" << endl;
            return;
        }
        else {
            int* aux_arr;
            nodo* aux_nodo;
            if (FIND(digit, aux_arr, aux_nodo)) {
                if (aux_arr == aux_nodo->array + 4) {
                    aux_nodo = aux_nodo->next;
                    aux_arr = aux_nodo->array;
                }
                else if (!aux_arr && aux_nodo->prev) {
                    aux_arr = aux_nodo->array;
                }
                else if (!aux_arr) {
                    aux_arr = INI;
                }
                else {
                    aux_arr++;
                }
                while (aux_arr != FIN) {
                    if (aux_arr == aux_nodo->array + 4) {
                        aux_nodo = aux_nodo->next;
                        *aux_arr = *(aux_nodo->array);
                        aux_arr = aux_nodo->array;
                    }
                    else {
                        *aux_arr = *(aux_arr + 1);
                        aux_arr++;
                    }
                }
                if (FIN == INI) {
                    delete HEAD;
                    TAIL = NULL;
                    HEAD = NULL;
                    INI = NULL;
                    FIN = NULL;
                }
                else if (FIN == TAIL->array) {
                    FIN = TAIL->prev->array + 4;
                    TAIL = TAIL->prev;
                    delete TAIL->next;
                }
                else {
                    FIN--;
                }
            }
            else {
                cout << "array no encontrado" << endl;
                return;
            }
        }
    }
    void PRINT() {
        nodo* aux_nodo = HEAD;
        int* aux = INI;
        cout << "HEAD ";
        while (aux && aux <= FIN) {

            if (aux == aux_nodo->array) {
                cout << "->[" << *aux;
                if (aux == FIN) {
                    cout << "]";
                }
                else {
                    cout << ",";
                }
                aux++;
            }
            else if (aux == FIN) {
                cout << *aux << "]" << endl;
                return;
            }
            else if (aux == aux_nodo->array + 4) {
                cout << *aux << "]";
                aux_nodo = aux_nodo->next;
                aux = aux_nodo->array;
            }
            else {
                cout << *aux << ",";
                aux++;
            }
        }
        cout << endl;
    }
    bool FIND(int digit, int*& pos_arr, nodo*& ub_nodo) {
        ub_nodo = HEAD;
        pos_arr = NULL;
        for (; ub_nodo->next && *(ub_nodo->array + 4) < digit; ub_nodo = ub_nodo->next);
        int* ptr_arr = ub_nodo->array;
        for (; ptr_arr <= FIN && *ptr_arr < digit; pos_arr = ptr_arr, ptr_arr++);
        if (ptr_arr <= FIN && *ptr_arr == digit) {
            return true;
        }
        return false;
    }
    ~LEA() {
        nodo* aux;
        while (HEAD && TAIL) {
            aux = TAIL;
            TAIL = TAIL->prev;
            delete aux;
        }
    }
};
int main() {
    LEA a;
    a.PRINT();
    a.ADD(1);
    a.ADD(10);
    a.ADD(3);
    a.ADD(4);
    a.ADD(5);
    a.ADD(8);
    a.ADD(8);
    a.ADD(28);
    a.ADD(18);
    a.ADD(9);
    a.ADD(10);
    a.ADD(11);
    a.ADD(12);
    a.PRINT();
    return 0;
}
