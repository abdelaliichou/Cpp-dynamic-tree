#ifndef PILE_H
#define PILE_H

#include "noeud.h"
#include <stdexcept>

// Définition de la classe Node pour les éléments de la liste chaînée
template<typename T>
class Node {
public:
    T data;
    Node* next;
    
    Node(T data) : data(data), next(nullptr) {}
};

// Définition de la classe Pile utilisant une liste chaînée
template<typename T>
class Pile {
private:
    Node<T>* top;

public:
    // Constructeur
    Pile();

    // Destructeur pour libérer la mémoire
    ~Pile();

    // Fonction pour vérifier si la pile est vide
    bool vide() const;

    // Fonction pour empiler un élément
    void empiler(T data);

    // Fonction pour dépiler un élément
    T dépiler();

    // Fonction pour obtenir l'élément au sommet sans le dépiler
    T sommet() const;
};

#include "pile.cpp"  // Inclure les implémentations du fichier pile.cpp

#endif

