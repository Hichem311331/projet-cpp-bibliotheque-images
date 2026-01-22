#include <iostream>
#include <vector>
#include "Descripteur.hpp"
#include "Filtragetri.hpp"

using namespace std;

int main() {

    vector<Descripteur> liste;

    // creation de quelques descripteurs (test)
    liste.push_back(Descripteur("NASA", "Mars", 1, 5.99, 'R'));
    liste.push_back(Descripteur("ESA", "Lune", 2, 0.0, 'L'));
    liste.push_back(Descripteur("INSERM", "IRM", 3, 12.5, 'R'));

    FiltrageTri ft(liste);

    cout << "=== Recherche par numero ===" << endl;
    Descripteur d;
    if (ft.rechercherParNumero(2, d)) {
        d.afficher();
    } else {
        cout << "Image pas trouvee" << endl;
    }

    cout << "\n=== Tri par prix Decroissant ===" << endl;
    ft.afficher(ft.trierParPrixDecroissant());

    cout << "\n=== Filtrage entre 1 et 10 ===" << endl;
    ft.afficher(ft.filtrerParPlage(1, 10));
    
     cout << "=== Filtrage optionnel par titre : Mars ===" << endl;
     ft.afficher(ft.filtrerParTitre("Mars"));

    return 0;
}

