#include "histogramme.hpp"
#include <algorithm> // pour std::fill et std::max_element

using namespace cv;

// =============================================
// Fonction : calculerHistogrammeGris
// But : remplit le tableau hist avec les fréquences
//       des intensités de 0 à 255 (image en niveaux de gris)
// =============================================
void calculerHistogrammeGris(const Mat& image, int hist[256]) {
    std::fill(hist, hist + 256, 0); // Initialiser à 0

    for (int y = 0; y < image.rows; ++y)
        for (int x = 0; x < image.cols; ++x)
            hist[image.at<uchar>(y, x)]++;
}

// =============================================
// Fonction : calculerHistogrammeCouleur
// But : remplit 3 tableaux pour les canaux B, G, R
// =============================================
void calculerHistogrammeCouleur(const Mat& image, int histB[256], int histG[256], int histR[256]) {
    std::fill(histB, histB + 256, 0);
    std::fill(histG, histG + 256, 0);
    std::fill(histR, histR + 256, 0);

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            Vec3b pixel = image.at<Vec3b>(y, x);
            histB[pixel[0]]++;
            histG[pixel[1]]++;
            histR[pixel[2]]++;
        }
    }
}

// =============================================
// Fonction : dessinerHistogrammeGris
// But : wrapper qui appelle dessinerHistogrammeCanal
// avec une couleur noire pour gris
// =============================================
Mat dessinerHistogrammeGris(const int hist[256]) {
    return dessinerHistogrammeCanal(hist, Scalar(0, 0, 0), "Histogramme Gris");
}

// =============================================
// Fonction : dessinerHistogrammeCanal
// But : créer une image affichant l’histogramme
// avec axes, valeurs et titre
// =============================================
Mat dessinerHistogrammeCanal(const int hist[256], const Scalar& couleur, const std::string& titre)
{
    int largeur = 600, hauteur = 400;
    int margeG = 60, margeD = 20, margeT = 30, margeB = 50;

    Mat img(hauteur, largeur, CV_8UC3, Scalar(255, 255, 255)); // Fond blanc

    // Titre de l’image
    putText(img, titre, Point(20, 25), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1);

    // Axes X (intensité) et Y (fréquence)
    line(img, Point(margeG, hauteur - margeB), Point(largeur - margeD, hauteur - margeB), Scalar(0, 0, 0), 1); // X
    line(img, Point(margeG, hauteur - margeB), Point(margeG, margeT), Scalar(0, 0, 0), 1); // Y

    // Max de l'histogramme (pour normaliser l'affichage)
    int maxVal = *std::max_element(hist, hist + 256);
    if (maxVal == 0) return img; // éviter division par 0

    // Ticks de l'axe X (intensité : 0 → 255)
    for (int v = 0; v <= 255; v += 64) {
        int x = margeG + (v * (largeur - margeG - margeD)) / 255;
        line(img, Point(x, hauteur - margeB), Point(x, hauteur - margeB + 5), Scalar(0, 0, 0), 1);
        putText(img, std::to_string(v), Point(x - 10, hauteur - margeB + 20), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 1);
    }

    // Ticks de l'axe Y (fréquences)
    for (int i = 0; i <= 4; i++) {
        int val = i * maxVal / 4;
        int y = hauteur - margeB - (val * (hauteur - margeB - margeT)) / maxVal;
        line(img, Point(margeG - 5, y), Point(margeG, y), Scalar(0, 0, 0), 1);
        putText(img, std::to_string(val), Point(5, y + 5), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 1);
    }

    // Tracer l’histogramme (courbe lissée)
    for (int i = 1; i < 256; i++) {
        int xPrev = margeG + ((i - 1) * (largeur - margeG - margeD)) / 255;
        int xCurr = margeG + (i * (largeur - margeG - margeD)) / 255;

        int hPrev = (hist[i - 1] * (hauteur - margeB - margeT)) / maxVal;
        int hCurr = (hist[i] * (hauteur - margeB - margeT)) / maxVal;

        Point p1(xPrev, hauteur - margeB - hPrev);
        Point p2(xCurr, hauteur - margeB - hCurr);

        line(img, p1, p2, couleur, 2, LINE_AA);
    }

    // Légendes axes
    putText(img, "Intensite (0-255)", Point(largeur / 2 - 70, hauteur - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1);
    putText(img, "Frequence", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1);

    return img;
}

