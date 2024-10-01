#include <iostream>

// Definición de la clase Node
template<typename T>
class Node {
public:
    // Constructor
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}

    // Getter y Setter
    T getData() const { return data; }
    void setData(T newData) { data = newData; }

    Node<T>* getNext() const { return next; }
    void setNext(Node<T>* newNext) { next = newNext; }

    Node<T>* getPrev() const { return prev; }
    void setPrev(Node<T>* newPrev) { prev = newPrev; }

private:
    T data;
    Node<T>* next;
    Node<T>* prev;
};

template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Constructor
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor
    ~DoubleLinkedList() {
        Node<T>* current = head;
        Node<T>* nextNode;

        while (current != nullptr) {
            nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
    }

    // Método para imprimir la lista
    void print_list() const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->getData() << " <-> ";
            temp = temp->getNext();
        }
        std::cout << "nullptr" << std::endl;
    }

    // Método para insertar al frente
    void push_front(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        head->setPrev(newNode);
        newNode->setNext(head);
        head = newNode;
    }
    // Método para insertar al frente
    void push_back(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    void pop_front() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->getNext();
            head->setPrev(nullptr);
            delete temp;
        }
    }
    void pop_back() {
        if (head != nullptr) {
            if (head->getNext() == nullptr) { //si solo tiene un elemento
                delete head;
                head = nullptr;
            }
            else { //si tiene mas de 1
                Node<T>* temp = tail->getPrev();   // temp apunta al penultimo           
                delete temp->getNext(); //se elimina el ultimo
                temp->setNext(nullptr); 
                tail = temp;
                temp->setPrev(temp->getPrev());
            }
        }
    }
    // Método para buscar un nodo
    Node<T>* search(T data) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->getData() == data) {
                return temp;
            }
            temp = temp->getNext();
        }
        return nullptr;
    }
    
    void print_reverse() {
        Node<T>* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->getData() << " <-> ";
            temp = temp->getPrev();
        }
        std::cout << "nullptr" << std::endl;
    }

    bool empty() {
        return head == nullptr;
    }
    
    T front() {
      try {
        if(head == nullptr){
          throw std::runtime_error("Intento de acceder a un nodo nulo");
        }

        return head->getData(); 
      } catch(const std::exception& e) {
        std::cerr << "Excepción en getData(): "<<e.what() << std::endl;
        return T();
      }
    }

    T back() {
      try {
        if(head == nullptr){
          throw std::runtime_error("Intento de acceder a un nodo nulo");
        }

        return tail->getData(); 
      } catch(const std::exception& e) {
        std::cerr << "Excepción en getData(): "<<e.what() << std::endl;
        return T();
      }
    }

    void clear() {
        if (head != nullptr) {
            Node<T>* temp = head;
            while (temp != nullptr) {
                temp = temp->getPrev();
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
        }       
    }   
    void insert(Node<T>* p, T data) {   
      if (p != nullptr) {        
        Node<T>* newNode = new Node<T>(data); 
        if(p == tail){
          newNode->setNext(nullptr);   
          tail = newNode;       
        }else{
          newNode->setNext(p->getNext());
          p->getNext()->setPrev(newNode);
        }
        p->setNext(newNode);
        newNode->setPrev(p);         
      }
      else {
          std::cout << "Nodo no encontrado." << std::endl;
      }
    }
    void remove(Node<T>* node) { 
      if (node == nullptr) return;
      if (node == head) {
        head = head->getNext();
        if (head != nullptr) {
            head->setPrev(nullptr);
        } else {
            tail = nullptr;
        }
        delete node;
        return;
      }

      if (node == tail) {
        tail = tail->getPrev();
        if (tail != nullptr) {
            tail->setNext(nullptr);
        } else {
            head = nullptr;
        }
        delete node;
        return;
      }

      Node<T>* prev = node->getPrev();
      Node<T>* next = node->getNext();

      if (prev != nullptr) {
          prev->setNext(next);
      }

      if (next != nullptr) {
          next->setPrev(prev);
      }

      delete node;
    }
};


template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    // Constructor
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor
    ~DoubleLinkedList() {
        Node<T>* current = head;
        Node<T>* nextNode;

        while (current != nullptr) {
            nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
    }

    // Método para imprimir la lista
    void print_list() const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->getData() << " <-> ";
            temp = temp->getNext();
        }
        std::cout << "nullptr" << std::endl;
    }

    // Método para insertar al frente
    void push_front(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        head->setPrev(newNode);
        newNode->setNext(head);
        head = newNode;
    }
    // Método para insertar al frente
    void push_back(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    void pop_front() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->getNext();
            head->setPrev(nullptr);
            delete temp;
        }
    }
    void pop_back() {
        if (head != nullptr) {
            if (head->getNext() == nullptr) { //si solo tiene un elemento
                delete head;
                head = nullptr;
            }
            else { //si tiene mas de 1
                Node<T>* temp = tail->getPrev();   // temp apunta al penultimo           
                delete temp->getNext(); //se elimina el ultimo
                temp->setNext(nullptr); 
                tail = temp;
                temp->setPrev(temp->getPrev());
            }
        }
    }
    // Método para buscar un nodo
    Node<T>* search(T data) const {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->getData() == data) {
                return temp;
            }
            temp = temp->getNext();
        }
        return nullptr;
    }
    
    void print_reverse() {
        Node<T>* temp = tail;
        while (temp != nullptr) {
            std::cout << temp->getData() << " <-> ";
            temp = temp->getPrev();
        }
        std::cout << "nullptr" << std::endl;
    }

    bool empty() {
        return head == nullptr;
    }
    
    T front() {
      try {
        if(head == nullptr){
          throw std::runtime_error("Intento de acceder a un nodo nulo");
        }

        return head->getData(); 
      } catch(const std::exception& e) {
        std::cerr << "Excepción en getData(): "<<e.what() << std::endl;
        return T();
      }
    }

    T back() {
      try {
        if(head == nullptr){
          throw std::runtime_error("Intento de acceder a un nodo nulo");
        }

        return tail->getData(); 
      } catch(const std::exception& e) {
        std::cerr << "Excepción en getData(): "<<e.what() << std::endl;
        return T();
      }
    }

    void clear() {
        if (head != nullptr) {
            Node<T>* temp = head;
            while (temp != nullptr) {
                temp = temp->getPrev();
                delete temp;
            }
            head = nullptr;
            tail = nullptr;
        }       
    }   
    void insert(Node<T>* p, T data) {   
      if (p != nullptr) {        
        Node<T>* newNode = new Node<T>(data); 
        if(p == tail){
          newNode->setNext(nullptr);   
          tail = newNode;       
        }else{
          newNode->setNext(p->getNext());
          p->getNext()->setPrev(newNode);
        }
        p->setNext(newNode);
        newNode->setPrev(p);         
      }
      else {
          std::cout << "Nodo no encontrado." << std::endl;
      }
    }
    void remove(Node<T>* node) { 
      if (node == nullptr) return;
      if (node == head) {
        head = head->getNext();
        if (head != nullptr) {
            head->setPrev(nullptr);
        } else {
            tail = nullptr;
        }
        delete node;
        return;
      }

      if (node == tail) {
        tail = tail->getPrev();
        if (tail != nullptr) {
            tail->setNext(nullptr);
        } else {
            head = nullptr;
        }
        delete node;
        return;
      }

      Node<T>* prev = node->getPrev();
      Node<T>* next = node->getNext();

      if (prev != nullptr) {
          prev->setNext(next);
      }

      if (next != nullptr) {
          next->setPrev(prev);
      }

      delete node;
    }
};

int main() {

    DoubleLinkedList<int>* lista2 = new DoubleLinkedList<int>;

    lista2->push_front(1);
    lista2->push_front(2);
    lista2->push_front(5);
    lista2->push_front(7);
    lista2->push_front(3);
    lista2->push_back(3);
    lista2->pop_back();
    lista2->print_list();
    lista2->print_reverse();
    lista2->clear();
    std::cout << "\nLimpiando...\n\n";
    lista2->print_list();
    std::cout<<"es empty: " <<lista2->empty() << "\n";
    std::cout<<"get_front: " <<lista2->front() << "\n";
    lista2->push_front(1);
    lista2->push_front(2);
    lista2->push_front(3);
    std::cout<<"get_front: " <<lista2->front() << "\n";
    lista2->print_list();


    Node<int>* searchptr = lista2->search(1);
  
    if (searchptr != nullptr) {
        std::cout << "Encontrado: " << searchptr->getData() << std::endl;
    }
    else {
        std::cout << "No encontrado" << std::endl;
    }

    lista2->remove(searchptr);
    lista2->print_list();
   
    Node<int>* insertAfter = lista2->search(2);
    lista2->insert(insertAfter, 6);
    lista2->print_list();
    delete lista2;

    return 0;
}