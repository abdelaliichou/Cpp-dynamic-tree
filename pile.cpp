#include "pile.h"

// Constructeur
template<typename T>
Pile<T>::Pile(){
    top = nullptr;
} 

// Destructeur pour libérer la mémoire
template<typename T>
Pile<T>::~Pile() {
    while (!vide()) {
        dépiler();
    }
}

// Fonction pour vérifier si la pile est vide
template<typename T>
bool Pile<T>::vide() const {
     return top == nullptr;
}

// Fonction pour empiler un élément
template<typename T>
void Pile<T>::empiler(T data) {
    Node<T>* newNode = new Node<T>(data);
    newNode->next = top;
    top = newNode;
}

// Fonction pour dépiler un élément
template<typename T>
T Pile<T>::dépiler() {
    if (vide()) {
        throw std::underflow_error("La pile est vide");
    }
    Node<T>* temp = top;
    T data = top->data;
    top = top->next;
    delete temp;
    return data;
}

// Fonction pour obtenir l'élément au sommet sans le dépiler
template<typename T>
T Pile<T>::sommet() const {
    if (vide()) {
        throw std::underflow_error("La pile est vide");
    }
    return top->data;
}

