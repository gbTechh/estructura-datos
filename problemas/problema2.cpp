/*
Los nodos de la lista circular estan modificados para tener un puntero extra llamado jump.
Este puntero debe apuntar al nodo en la k posicion siguiente
Aunq el valor de k sea mayor al numero de elementos de la lista,
el valor de jump puede dar la vuelta a la lista y seguir apuntando al k-esimo siguiente nodo.

Implementar el metodo updateJumps de la lista circular para los punteros jumps
sean actualizados despues de cada push y pop.

No modifiques el main. Codea dentro del metodo updateJumps.
Puedes crear nuevas funciones o metodos

Desafio adicional:
Crear un metodo que revierta los nodos jump y que apunten al k-esimo nodo anterior
Para comprobar este desafio adicional puedes modificar el main.

*/

#include <iostream>
using namespace std;


template <class T>
class Node {
public:
   T value;
   Node* next;
   Node* jump;

   Node(T value, Node* next = nullptr, Node* jump = nullptr) {
      this->value = value;
      this->next = next;
      this->jump = jump;
   }
};

template <class T>
class CircularList {
private:

   Node<T>* head = nullptr;
   Node<T>* tail = nullptr;

public:

   int size = 0;
   int k = 1;

   CircularList(int k){
      this->k = k;
   }

   void updateJumps(){

      // Codea aqui :D



   }

   void push(T val) {

      ++ size;

      if (!head){
         head = new Node<T>(val);
         head->next = head;
         head->jump = head;

         tail = head;
      }
      else{
         tail->next = new Node<T>(val, head);
         tail = tail->next;

         updateJumps();

      }

   }

   void pop() {

      if (!head) return;

      -- size;

      if (head == tail){
         delete head;
         head = tail = nullptr;
      }
      else{
         tail->next = head->next;
         delete head;
         head = tail->next;

         updateJumps();

      }

   }


   void print() {

      cout << "Circular List (" << size << "):";
      if (!head) {
         cout << "NULL\n" << endl;
         return;
      }

      cout << endl << "\tNode value " << head->value << " -> Jump value ";
      if (head->jump) cout << head->jump->value;
      else cout << "NULL";

      for (Node<T>* p = head->next; p != head; p = p->next){
         cout << endl << "\tNode value " << p->value << " -> Jump value ";
         if (p->jump) cout << p->jump->value;
         else cout << "NULL";
      }

      cout << endl << endl;

   }


};

int main() {

   cout << "\n----- Test 1 -----\n";
   CircularList<int> circularList(4);

   // Test Case 1: Basic Push and Jump Updates
   cout << "Test Case 1: Basic Push\n";
   for (int i = 0; i < 5; ++i){
      circularList.push(i);
      circularList.print();
   }

   // Test Case 2: Remove nodes and recheck jumps
   cout << "Test Case 2: Pop and Push\n";
   circularList.pop();  // Remove one node
   circularList.print();

   circularList.push(5);  // Add a new node
   circularList.print();

   // Test Case 3: More pushes and pops to check the integrity
   cout << "Test Case 3: Push More\n";
   circularList.push(6);
   circularList.push(7);
   circularList.push(8);
   circularList.print();

   cout << "Pop some elements and update\n";
   circularList.pop();
   circularList.pop();
   circularList.print();

   // Test Case 4: Full circularity after multiple operations
   cout << "Test Case 4: Circularity Check after multiple operations\n";
   for (int i = 9; i < 12; ++i) {
      circularList.push(i);
   }
   circularList.print();

   // Test Case 5: Empty list handling
   cout << "Test Case 5: Empty List\n";
   while (circularList.size > 0) {
      circularList.pop();
      circularList.print();
   }


   cout << "\n\n----- Test 2 -----\n";
   CircularList<int> circularList2(5);

   // Test Case 1: Basic Push and Jump Updates
   cout << "Test Case 1: Basic Push\n";
   for (int i = 0; i < 5; ++i){
      circularList2.push(i);
      circularList2.print();
   }

   // Test Case 2: Remove nodes and recheck jumps
   cout << "Test Case 2: Pop and Push\n";
   circularList2.pop();  // Remove one node
   circularList2.print();

   circularList2.push(5);  // Add a new node
   circularList2.print();

   // Test Case 3: More pushes and pops to check the integrity
   cout << "Test Case 3: Push More\n";
   circularList2.push(6);
   circularList2.push(7);
   circularList2.push(8);
   circularList2.print();

   cout << "Pop some elements and update\n";
   circularList2.pop();
   circularList2.pop();
   circularList2.print();

   // Test Case 4: Full circularity after multiple operations
   cout << "Test Case 4: Circularity Check after multiple operations\n";
   for (int i = 9; i < 12; ++i) {
      circularList2.push(i);
   }
   circularList2.print();

   // Test Case 5: Empty list handling
   cout << "Test Case 5: Empty List\n";
   while (circularList2.size > 0) {
      circularList2.pop();
      circularList2.print();
   }

   return 0;
}
