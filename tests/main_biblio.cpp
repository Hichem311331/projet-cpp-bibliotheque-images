#include"Descripteur.hpp"
#include"biblio.hpp"
#include<iostream>
using namespace std;
int main() {


BibliothequeImages bib;

bib.ajouter(Descripteur("mars.jpg", "Mars", 1, 0.0f, 'L'));
bib.ajouter(Descripteur("lune.png", "Lune", 2, 5.5f, 'R'));
bib.ajouter(Descripteur("terre.jpg", "Terre", 3, 2.0f, 'R'));

bib.afficherTout();

cout << "----------- Acces pour L -------"<<endl;
bib.afficherAccessibles('L');

cout << "----------- Acces pour R -------"<<endl;
bib.afficherAccessibles('R');


cout<<"test d'acces :"<<endl;
cout << "Acces image #2 pour L : " << (bib.aAcces(2, 'L') ? "Oui" : "NON") <<endl;
cout << "Acces image #2 pour R : " << (bib.aAcces(2, 'R') ? "Oui" : "NON") <<endl;

//cout << "Suppression #1 : " << (bib.supprimer(1) ? "OK" : "NON") <<endl;
//cout << "Taille de la bibliothèque = " << bib.taille() <<endl;


cout<<"-----------modification de limgae 3 -------------"<<endl;
bib.modifier(2,Descripteur("terre.jpg", "Terre_v2", 3, 2.0f, 'R'));
bib.afficherTout();

cout<<"rechreche de image 3 : "<<bib.trouver(3)<<endl;
// elle me rrtourne l'adresse du descpteur de limage 3 // utilisationaussi dans les droit d'acces ou bien piour obtenir une imfo du le dscpteur

cout << "Suppression 5 : " << (bib.supprimer(5) ? "Oui" : "NON") <<endl; //non si pas de suppression -> nexiste pas 
return 0;
}

