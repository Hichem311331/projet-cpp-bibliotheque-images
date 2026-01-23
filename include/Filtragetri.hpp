#ifndef FILTRAGETRI_HPP
#define FILTRAGETRI_HPP

#include <vector>
#include "Descripteur.hpp"

using namespace std;

class FiltrageTri {
private:
    // on a la liste des descripteurs
    vector<Descripteur> liste;  

public:
    // constructeur
    FiltrageTri(vector<Descripteur> l);
    
    // recherche par numero
    bool rechercherParNumero(int numero, Descripteur& resultat);
  
   // filtrage optionnel par titre 
   vector<Descripteur> filtrerParTitre(string titreRecherche);

    // on trie par prix (ordre décroissant)
    vector<Descripteur> trierParPrixDecroissant();

    // on filtre par plage de prix
    vector<Descripteur> filtrerParPlage(float min, float max);

    // afficher une liste de descripteurs
    void afficher(vector<Descripteur> l);
};

#endif

