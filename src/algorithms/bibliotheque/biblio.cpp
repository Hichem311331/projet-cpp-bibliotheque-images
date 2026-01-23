#include"biblio.hpp"
#include<iostream>

BibliothequeImages::BibliothequeImages() {}

int BibliothequeImages::indexNumero(int numero) const {
    for (int i = 0; i < (int)images.size(); i++) {
        if (images[i].getNumero() == numero) return i;
    }// transforme le numero de limge en un indice   
    return -1;
}

bool BibliothequeImages::ajouter(const Descripteur& d) {//copie par ref et on cherhce le num du descpteur
    if (indexNumero(d.getNumero()) !=-1) return false;//si ne le trouve pas false donc on l'ajoute pas 
    images.push_back(d);//else on ajoute la copie au vecteur 
    return true;
}

bool BibliothequeImages::supprimer(int numero) {
    int idx = indexNumero(numero);//idx position de limage dans vecteur images
    if(idx== -1) 
    return false;// si pas d'indice return false : pas de supp

    images.erase(images.begin()+idx);//parcourt le vect imge jusquà idx et le supprime 
    return true;
}

bool BibliothequeImages::modifier(int numero, const Descripteur& nouveau) {
    int idx = indexNumero(numero);
    if (idx == -1) 
    return false;// on modifie une image qui existe

    // On garde le numero identique pour eviter incoherences
    Descripteur copie=nouveau; // creation dun nv descpiteur
    copie.setNumero(numero);// garde le meme num mais un nv descp
    images[idx]=copie;// ecaser limage
    return true;
}

const Descripteur* BibliothequeImages::trouver(int numero) const {
    int idx = indexNumero(numero);
    if (idx == -1) 
    return nullptr;
    return &images[idx]; // on return un pointeur vers l'ojbet -> @
}

void BibliothequeImages::afficherTout() const {
    std::cout << "Bibliotheque images (total des images: " << images.size() << ") \n";
    for (int i(0);i<images.size();i++) {
        images[i].afficher();// affichage de toute les images(descpiteur)
    }
}

void BibliothequeImages::afficherAccessibles(char droitUtilisateur) const {
    std::cout << "Images accessibles pour '" << droitUtilisateur << "' ===\n";
    for (int i(0);i<images.size();i++) {
        if (images[i].aAcces(droitUtilisateur)) {
            images[i].afficher();// affichage selon les droits
        }
    }
}

int BibliothequeImages::taille() const {
    return (int)images.size();
}

bool BibliothequeImages::aAcces(int numero, char droitUtilisateur) const {
    const Descripteur* d = trouver(numero);
    if (!d) return false;
    return d->aAcces(droitUtilisateur);// acceder au membre d : 
}



const std::vector<Descripteur>& BibliothequeImages::getImages() const {
    return images;
}




