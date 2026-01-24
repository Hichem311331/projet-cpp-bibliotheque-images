#include <opencv2/opencv.hpp>
#include <iostream>
#include "Filtrage.hpp"

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("image.jpg", IMREAD_GRAYSCALE);

    if (img.empty())
    {
        cout << "Erreur : image non chargee" << endl;
        return -1;
    }

    Filtrage f(img);

    Mat moyenneur = f.filtreMoyenneur();
    Mat gaussien = f.filtreGaussien();
    Mat laplacien = f.filtreLaplacien();

    f.afficher(img, "Original");
    f.afficher(moyenneur, "Moyenne");
    f.afficher(gaussien, "Gaussien");
    f.afficher(laplacien, "Laplacien");

    waitKey(0);

    f.sauvegarder(moyenneur, "moyenne.png");
    f.sauvegarder(gaussien, "gaussien.png");
    f.sauvegarder(laplacien, "laplacien.png");

    return 0;
}

