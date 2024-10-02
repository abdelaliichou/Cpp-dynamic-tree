#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cmath>
#include "pile.h"
#include "arbre.h"
#include "arbreVAR.h"
#include "shunting_yard.h"

// Fonction pour évaluer une expression suffixée
double évaluer(const std::string& expression) {
    Pile<double> pile;
    std::istringstream iss(expression);
    std::string element;

    while (iss >> element) {
        if (std::isdigit(element[0]) || (element[0] == '-' && std::isdigit(element[1]))) {
            pile.empiler(std::stod(element));
        } else if (element.size() == 1 && std::string("+-*/^").find(element) != std::string::npos) {
            double operand2 = pile.dépiler();
            double operand1 = pile.dépiler();
            double result;

            switch (element[0]) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': 
                    if (operand2 == 0) {
                        throw std::runtime_error("Division par zéro");
                    }
                    result = operand1 / operand2; 
                    break;
                case '^': result = pow(operand1, operand2); break;
                default:
                    throw std::runtime_error("Opérateur inconnu");
            }
            pile.empiler(result);
        } else {
            throw std::runtime_error("Élément invalide");
        }
    }

    if (pile.vide()) {
        throw std::runtime_error("Expression invalide");
    }

    double result = pile.dépiler();
    if (!pile.vide()) {
        throw std::runtime_error("Expression invalide");
    }
    return result;
}

// void testPile(){
//    try {
//           Pile<int> pile;

//           pile.empiler(10);
//           pile.empiler(20);
//           pile.empiler(30);

//           std::cout << "Sommet: " << pile.sommet() << std::endl;  // Affiche 30

//           std::cout << "Dépile: " << pile.dépiler() << std::endl;  // Affiche 30
//           std::cout << "Dépile: " << pile.dépiler() << std::endl;  // Affiche 20
//           std::cout << "Dépile: " << pile.dépiler() << std::endl;  // Affiche 10

//           std::cout << "La pile est vide: " << (pile.vide() ? "Oui" : "Non") << std::endl;  // Affiche Oui
//       } catch (const std::exception& e) {
//           std::cerr << "Erreur: " << e.what() << std::endl;
//       }
// }

void QUESTION1(){
    try {
          std::string expression = "3 4 + 2 * 7 /";       
          double result = évaluer(expression);
          std::cout << "Résultat: " << result << std::endl;  // Affiche 2

          expression = "5 1 2 + 4 * + 3 -";
          result = évaluer(expression);
          std::cout << "Résultat: " << result << std::endl;  // Affiche 14
        } catch (const std::exception& e) {
          std::cerr << "Erreur: " << e.what() << std::endl;
    }
}

void QUESTION2(){
   try {
        std::string expression = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
        std::string postfixExpression = infixToPostfix(expression);
        double result = évaluer(postfixExpression);
        std::cout << "Expression: " << expression << std::endl;
        std::cout << "Postfix: " << postfixExpression << std::endl;
        std::cout << "Résultat: " << result << std::endl;

        expression = "5 + ( 1 + 2 ) * 4 - 3";
        postfixExpression = infixToPostfix(expression);
        result = évaluer(postfixExpression);
        std::cout << "Expression: " << expression << std::endl;
        std::cout << "Postfix: " << postfixExpression << std::endl;
        std::cout << "Résultat: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
    }
}

void QUESTION3(){
      try {
        std::string expression1 = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
        std::string expression11 = "3 - 2 * 4";
        std::string expression2 = "5 + ( 1 + 2 ) * 4 - 3";

        std::cout << "Expression: " << expression1 << std::endl;
        arbre arbre1(expression1);
        std::cout << "Expression suffixe noeud: ";
        arbre1.afficherInfixe();
        std::cout << std::endl;
        std::cout << "Résultat: " << arbre1.evaluation() << std::endl;

        std::cout << "Expression: " << expression2 << std::endl;
        arbre arbre2(expression2);
        std::cout << "Expression suffixe noeud: ";
        arbre2.afficherInfixe();
        std::cout << std::endl;
        std::cout << "Résultat: " << arbre2.evaluation() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
  } 
}

void QUESTION4(){
    try {  
    
        std::cout << "Expression: 4 * X^2 - 2 * Y + (-Z)" << std::endl;;
        
        // Exemple : 4 * X^2 - 2 * Y + (-Z)
        noeudVAR* exp = new noeudVAR('+',
            new noeudVAR('-',
                new noeudVAR('*',
                    new noeudVAR(4.0),
                    new noeudVAR('^', new noeudVAR("X"), new noeudVAR(2.0))
                ),
                new noeudVAR('*', new noeudVAR(2.0), new noeudVAR("Y"))
            ),
            new noeudVAR('-', nullptr, new noeudVAR("Z"))  // Represents -Z
        );
        
        arbreVAR a(exp);
        

        arbreVAR dérivéeA = a.dérivée("X");
        arbreVAR dérivéeB = a.dérivée("Y");
        arbreVAR dérivéeC = a.dérivée("Z");
        
        std::cout << "Expression inffixe: ";
        dérivéeA.afficherInfixe();
        std::cout << std::endl;

        std::unordered_map<std::string, double> variables = {{"X", 1.0}, {"Y", 2.0}, {"Z", 3.0}};
        
        double resultA = dérivéeA.évaluation(variables);
        double resultB = dérivéeB.évaluation(variables);
        double resultC = dérivéeC.évaluation(variables);
        
        std::cerr << "Result de la dérivée par rapport a (X): " << resultA << std::endl;
        std::cerr << "Result de la dérivée par rapport a (Y): " << resultB << std::endl;
        std::cerr << "Result de la dérivée par rapport a (Z): " << resultC << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
  }
}

int main() {

   //  Projet de Meriem Ammour, Universite d'avignon
   //  Manuelle de l'execution : 
   //     - installation de C++ dans la machine ( g++ )
   //     - se localiser dans le dossier qui contient le projet ( cd ../dossier )
   //     - lancer la command : g++ -o main main.cpp arbre.cpp arbreVAR.cpp noeudVAR.cpp noeud.cpp shunting_yard.cpp
   //     - lancer la command : ./main
   
   
   
   // testPile();
   // QUESTION1();
   // QUESTION2();
   // QUESTION3();
   // QUESTION4();

   return 0;
}
