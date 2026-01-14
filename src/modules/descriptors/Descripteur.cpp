#include "../../../include/Descripteur.hpp"
#include <iostream>
using namespace std;

Descripteur::Descripteur(string src, string ttr, int num, float pr, char acc) {
    source = src;
    titre = ttr;
    numero = num;
    prix = pr;
    acces = acc;
}

Descripteur::Descripteur() {
    source = "";
    titre = "";
    numero = 0;
    prix = 0.0;
    acces = 'L';
}

string Descripteur::getSource() const {
    return source;
}

string Descripteur::getTitre() const {
    return titre;
}

int Descripteur::getNumero() const {
    return numero;
}

float Descripteur::getPrix() const {
    return prix;
}

char Descripteur::getAcces() const {
    return acces;
}

void Descripteur::setSource(string src) {
    source = src;
}

void Descripteur::setTitre(string ttr) {
    titre = ttr;
}

void Descripteur::setNumero(int num) {
    numero = num;
}

void Descripteur::setPrix(float pr) {
    prix = pr;
}

void Descripteur::setAcces(char acc) {
    acces = acc;
}

void Descripteur::afficher() const {
    cout << "=== Descripteur Image ===" << endl;
    cout << "Source : " << source << endl;
    cout << "Titre : " << titre << endl;
    cout << "Numero : " << numero << endl;
    cout << "Prix : " << prix << " euros" << endl;
    cout << "Acces : " << acces << endl;
    cout << "========================" << endl;
}

bool Descripteur::aAcces(char droitUtilisateur) const {
    if (acces == 'L') {
        return true;
    }
    if (acces == 'R') {
        if (droitUtilisateur == 'R' || droitUtilisateur == 'W') {
            return true;
        }
        return false;
    }
    return false;
}
