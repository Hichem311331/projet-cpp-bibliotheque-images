#ifndef Transf_HOUGH_HPP

#define Transf_HOUGH_HPP


#include <opencv2/opencv.hpp>

#include <vector>


using namespace std;

using namespace cv;


class Transfhough {

private:

    Mat imageContours;           // L'image des contours

    Mat imageResultat;           // L'image finale avec les lignes

    vector<vector<int>> votes;   // La table des votes

    int distanceMax;             // Distance maximale possible


public:

    Transfhough(Mat contours);     // Créer l'objet

    void calculerVotes();             // Remplir la table des votes

    void chercherMaximaLocaux(int seuil); // Chercher les maxima locaux

    void afficher();                  // Afficher le résultat

    void sauvegarder(string nom);     // Sauvegarder l'image

};


#endif
