#include <opencv2/opencv.hpp>
#include "histogramme.hpp"

using namespace std;
using namespace cv;

// =============================================
// Programme principal
// =============================================
int main()
{
    string cheminImage;
    int choix;

    cout << "Chemin de l'image à analyser : ";
    cin >> cheminImage;

    Mat image = imread(cheminImage);
    if (image.empty()) {
        cout << "Erreur : impossible de charger l'image !" << endl;
        return -1;
    }

    imshow("Image Originale", image);

    cout << "\n=== Choix de l'histogramme ===" << endl;
    cout << "1 - Niveaux de gris" << endl;
    cout << "2 - Histogrammes couleur (BGR)" << endl;
    cout << "Votre choix : ";
    cin >> choix;

    if (choix == 1) {
        Mat imageGris;
        if (image.channels() == 3)
            cvtColor(image, imageGris, COLOR_BGR2GRAY);
        else
            imageGris = image;

        int hist[256];
        calculerHistogrammeGris(imageGris, hist);

        Mat imgHist = dessinerHistogrammeGris(hist);
        imshow("Histogramme Gris", imgHist);
    }
    else if (choix == 2) {
        if (image.channels() != 3) {
            cout << "L'image doit être en couleur." << endl;
            return -1;
        }

        int histB[256], histG[256], histR[256];
        calculerHistogrammeCouleur(image, histB, histG, histR);

        Mat hB = dessinerHistogrammeCanal(histB, Scalar(255, 0, 0), "Histogramme Bleu");
        Mat hG = dessinerHistogrammeCanal(histG, Scalar(0, 255, 0), "Histogramme Vert");
        Mat hR = dessinerHistogrammeCanal(histR, Scalar(0, 0, 255), "Histogramme Rouge");

        imshow("Histogramme Bleu", hB);
        imshow("Histogramme Vert", hG);
        imshow("Histogramme Rouge", hR);
    }
    else {
        cout << "Choix invalide." << endl;
    }

    waitKey(0); // Attendre la touche
    return 0;
}

