#include "Filtragetri.hpp"
#include <iostream>

using namespace std;

// constructeur
FiltrageTri::FiltrageTri(vector<Descripteur> l) {
    liste = l;
}



// recherche par numero
bool FiltrageTri::rechercherParNumero(int numero, Descripteur& resultat) {
    for (int i = 0; i < (int)liste.size(); i++) {
        if (liste[i].getNumero() == numero) {
            resultat = liste[i];
            return true;
        }
    }
    return false;
}

// on filtre par titre 
vector<Descripteur> FiltrageTri::filtrerParTitre(string titreRecherche) {
    vector<Descripteur> resultat;

    for (int i = 0; i < (int)liste.size(); i++) {
        if (liste[i].getTitre() == titreRecherche) {
            resultat.push_back(liste[i]);
        }
    }

    return resultat;
}
// on filtre par prix decroissant 
vector<Descripteur> FiltrageTri::trierParPrixDecroissant() {
    vector<Descripteur> resultat = liste;

    for (int i = 0; i < resultat.size() - 1; i++) {
        for (int j = i + 1; j < resultat.size(); j++) {
            if (resultat[i].getPrix() < resultat[j].getPrix()) {
                Descripteur tmp = resultat[i];
                resultat[i] = resultat[j];
                resultat[j] = tmp;
            }
        }
    }
    return resultat;
}
// on filtre par plage de prix 
vector<Descripteur> FiltrageTri::filtrerParPlage(float min, float max) {
    vector<Descripteur> resultat;

    for (int i = 0; i < liste.size(); i++) {
        if (liste[i].getPrix() >= min && liste[i].getPrix() <= max) {
            resultat.push_back(liste[i]);
        }
    }

    return resultat;
}
//affichage 
void FiltrageTri::afficher(vector<Descripteur> l) {
    for (int i = 0; i < l.size(); i++) {
        l[i].afficher();
    }
}


