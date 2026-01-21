

#include "Transfhough.hpp"

#include <cmath>

#include <iostream>


using namespace std;

using namespace cv;


Transfhough::Transfhough(Mat contours) {

    imageContours = contours;  // Stocker l'image des contours

    

    // Créer une image noire de la même taille (3 canaux pour dessiner en couleur)

    imageResultat = Mat::zeros(contours.rows, contours.cols, CV_8UC3);

}

void Transfhough::calculerVotes() {

    int largeur = imageContours.cols;

    int hauteur = imageContours.rows;


    // Calculer la distance maximale possible (diagonale de l'image)

    distanceMax = sqrt(largeur * largeur + hauteur * hauteur);


    // Créer la table d'accumulation (2D)

    votes = vector<vector<int>>(2 * distanceMax + 1, vector<int>(180, 0));


    // Parcourir tous les pixels de l'image des contours

    for (int y = 0; y < hauteur; y++) {

        for (int x = 0; x < largeur; x++) {

            if (imageContours.at<uchar>(y, x) > 0) {  // Si le pixel est blanc

                for (int angle = 0; angle < 180; angle++) {

                    double theta = angle * CV_PI / 180.0;  // Convertir l'angle en radians

                    int rho = cvRound(x * cos(theta) + y * sin(theta));  // Calculer rho

                    int indexRho = rho + distanceMax;  // Décaler rho pour avoir un index positif


                    if (indexRho >= 0 && indexRho < 2 * distanceMax + 1) {

                        votes[indexRho][angle]++;  // Ajouter un vote

                    }

                }

            }

        }

    }

}
void Transfhough::chercherMaximaLocaux(int seuil) {
    vector<int> maximaRho;    // Stocke les indices rho
    vector<int> maximaAngle;  // Stocke les indices angle

    // Chercher les maxima locaux
    for (size_t rhoIdx = 1; rhoIdx < votes.size() - 1; rhoIdx++) {
        for (int angle = 1; angle < 179; angle++) {
          
            int centre = votes[rhoIdx][angle];
            int haut = votes[rhoIdx - 1][angle];
            int bas = votes[rhoIdx + 1][angle];
            int gauche = votes[rhoIdx][angle - 1];
            int droite = votes[rhoIdx][angle + 1];

            if (centre > seuil && centre > haut && centre > bas && centre > gauche && centre > droite) {
                maximaRho.push_back(rhoIdx);    // Ajouter rhoIdx
                maximaAngle.push_back(angle);  // Ajouter angle
            }
        }
    }

    cout << "Nombre de maxima locaux detectes : " << maximaRho.size() << endl;

    // Calculer une distance dynamique basée sur la taille de l'image
    int tailleMax = max(imageResultat.rows, imageResultat.cols);  // Taille maximale de l'image
    int distanceArbitraire = tailleMax * 2;  // Distance dynamique (2 fois la taille maximale)

    // Dessiner les lignes pour les maxima locaux
    for (size_t i = 0; i < maximaRho.size(); i++) {
        int rhoIdx = maximaRho[i];
        int angle = maximaAngle[i];

        float rho = rhoIdx - distanceMax;
        float theta = angle * CV_PI / 180.0;

        float a = cos(theta);
        float b = sin(theta);
        float x0 = a * rho;
        float y0 = b * rho;

        for (int t = -distanceArbitraire; t <= distanceArbitraire; t++) {
            int x = cvRound(x0 + t * (-b));
            int y = cvRound(y0 + t * a);

            if (x >= 0 && x < imageResultat.cols && y >= 0 && y < imageResultat.rows) {
                imageResultat.at<Vec3b>(y, x) = Vec3b(0, 0, 255);  // Rouge
            }
        }
    }
}
void Transfhough::afficher() {
    imshow("Contours", imageContours);
    imshow("Lignes detectees", imageResultat);
    waitKey(0);
}
void Transfhough::sauvegarder(string nom) {
    imwrite(nom, imageResultat);
    cout << "Image sauvegardee : " << nom << endl;
}

