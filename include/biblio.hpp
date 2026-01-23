#ifndef BIBLIOTHEQUE_IMAGES_HPP
#define BIBLIOTHEQUE_IMAGES_HPP

#include<vector>
#include<string>
#include"Descripteur.hpp"

class BibliothequeImages {
private:
    std::vector<Descripteur> images;
    int indexNumero(int numero) const;

public:
    BibliothequeImages();
    bool ajouter(const Descripteur& d);//ajout descp(false si numero deja utilise)
    bool supprimer(int numero);
    // Modifier un descripteur par numero
    bool modifier(int numero, const Descripteur& nouveau);
    const Descripteur* trouver(int numero) const;
    
    void afficherTout() const;
    void afficherAccessibles(char droitUtilisateur) const;
    int taille() const;
    bool aAcces(int numero, char droitUtilisateur) const;// verfication de l'acces
    const std::vector<Descripteur>& getImages() const;

};
#endif
