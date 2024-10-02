#ifndef NOEUD_H
#define NOEUD_H

class noeud {
public:
    char type; // 'o' pour opérateur et 'f' pour valeur
    char ope;
    double val;
    noeud* fg;
    noeud* fd;

    // Constructeur pour un opérateur
    noeud(char operateur);

    // Constructeur pour une valeur
    noeud(double valeur);

    // Destructeur pour libérer la mémoire
    ~noeud();
};

#endif

