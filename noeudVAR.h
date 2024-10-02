#ifndef NOEUD_VH
#define NOEUD_VH

#include <string>

class noeudVAR {
public:
    char type; // 'o' pour opérateur et 'f' pour valeur
    char ope;  // Opérateur si type est 'o'
    double val; // Valeur si type est 'f'
    std::string var; // Variable si type est 'v'
    noeudVAR* fg;
    noeudVAR* fd;

    // Constructeurs
    noeudVAR(char operateur, noeudVAR* gauche, noeudVAR* droit);
    noeudVAR(double valeur);
    noeudVAR(char operateur, noeudVAR* unique);
    noeudVAR(const std::string& variable);

    // Destructeur
    ~noeudVAR();

    // Copier un nœud
    noeudVAR* copier() const;
};

#endif

