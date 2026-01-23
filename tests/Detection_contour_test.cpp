#include <opencv2/opencv.hpp>
#include <iostream>
#include "Detection_contour.hpp"

using namespace std;
using namespace cv;

Image matToImage(const Mat& mat) {
    vector<vector<int>> data(mat.rows, vector<int>(mat.cols));
    
    for (int y = 0; y < mat.rows; y++) {
        for (int x = 0; x < mat.cols; x++) {
            data[y][x] = mat.at<uchar>(y, x);
        }
    }
    
    return Image(data);
}

Mat imageToMat(const Image& img) {
    Mat mat(img.getHauteur(), img.getLargeur(), CV_8UC1);
    auto data = img.getData();
    
    for (int y = 0; y < img.getHauteur(); y++) {
        for (int x = 0; x < img.getLargeur(); x++) {
            mat.at<uchar>(y, x) = static_cast<uchar>(data[y][x]);
        }
    }
    
    return mat;
}

int main() {
    // Charger une image (OpenCV est utilisé uniquement pour entrées et sorties)
    Mat imgOriginal = imread("papillon.jpg", IMREAD_GRAYSCALE);
    
    if (imgOriginal.empty()) {
        cout << "Erreur: Impossible de charger l'image 'test.jpg'" << endl;
    }
    
    cout << "Détection de contours par filtre Laplacien" << endl;
    
    // Convertir en notre format
    Image img = matToImage(imgOriginal);
    
    // Créer le détecteur
    DetectionContour detecteur;
    
    // Appliquer le filtre Laplacien
    cout << "Application du filtre Laplacien..." << endl;
    Image imgLaplacien = detecteur.appliquerLaplacien(img);
    
    // Appliquer un seuillage pour binariser
    cout << "Application du seuillage (seuil = 30)..." << endl;
    Image imgContours = detecteur.seuillage(imgLaplacien, 30);
    
    // Convertir pour affichage
    Mat matLaplacien = imageToMat(imgLaplacien);
    Mat matContours = imageToMat(imgContours);
    
    //afficher les résultats
    namedWindow("Image Originale", WINDOW_NORMAL);
    namedWindow("Laplacien", WINDOW_NORMAL);
    namedWindow("Contours (Seuillage)", WINDOW_NORMAL);
    
    imshow("Image Originale", imgOriginal);
    imshow("Laplacien", matLaplacien);
    imshow("Contours (Seuillage)", matContours);

    cout <<"appuyer sur une toucher pour quitter"<<endl;

    waitKey(0);

    return 0;
}