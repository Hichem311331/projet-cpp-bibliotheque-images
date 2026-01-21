#include "Transfhough.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    // Charger l'image des contours directement
    Mat contours = imread("contours.jpg", IMREAD_GRAYSCALE);  // Image des contours
    if (contours.empty()) {
        cout << "Erreur : image des contours introuvable" << endl;
        return -1;
    }
    
    // Appliquer la transformée de Hough
    Transfhough hough(contours);
    hough.calculerVotes();
    hough.chercherMaximaLocaux(165);  
    hough.afficher();
    hough.sauvegarder("resultat.png");
    
    return 0;
}
