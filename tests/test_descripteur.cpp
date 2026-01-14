#include "../include/Descripteur.hpp"
#include <iostream>
using namespace std;

int main() {
    cout << "=== Test Descripteur ===" << endl << endl;
   
    Descripteur desc1;
    desc1.afficher();
    cout << endl;
   
    Descripteur desc2("mars.jpg", "Mars", 1, 0.0, 'L');
    desc2.afficher();
    cout << endl;
   
    Descripteur desc3("lune.png", "Lune", 2, 5.50, 'R');
    desc3.afficher();
    cout << endl;
   
    desc1.setSource("terre.jpg");
    desc1.setTitre("Terre");
    desc1.setNumero(4);
    desc1.setPrix(8.00);
    desc1.setAcces('R');
    desc1.afficher();
    cout << endl;
   
    cout << "Titre: " << desc2.getTitre() << endl;
    cout << "Prix: " << desc3.getPrix() << endl;
   
    cout << "Acces Mars pour L: " << (desc2.aAcces('L') ? "OK" : "NO") << endl;
    cout << "Acces Lune pour L: " << (desc3.aAcces('L') ? "OK" : "NO") << endl;
    cout << "Acces Lune pour R: " << (desc3.aAcces('R') ? "OK" : "NO") << endl;
   
    return 0;
}
