#ifndef DESCRIPTEUR_HPP
#define DESCRIPTEUR_HPP

#include <string>
using namespace std;

class Descripteur {
protected:
    string source;
    string titre;
    int numero;
    float prix;
    char acces;

public:
    Descripteur(string src, string ttr, int num, float pr, char acc);
    Descripteur();
   
    string getSource() const;
    string getTitre() const;
    int getNumero() const;
    float getPrix() const;
    char getAcces() const;
   
    void setSource(string src);
    void setTitre(string ttr);
    void setNumero(int num);
    void setPrix(float pr);
    void setAcces(char acc);
   
    void afficher() const;
    bool aAcces(char droitUtilisateur) const;
};

#endif
