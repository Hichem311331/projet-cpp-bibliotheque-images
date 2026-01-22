#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include <opencv2/opencv.hpp>

// Histogramme pour image en niveaux de gris
void calculerHistogrammeGris(const cv::Mat& image, int hist[256]);

// Histogramme pour chaque canal (Bleu, Vert, Rouge)
void calculerHistogrammeCouleur(const cv::Mat& image, int histB[256], int histG[256], int histR[256]);

// Affichage d’un histogramme en niveaux de gris
cv::Mat dessinerHistogrammeGris(const int hist[256]);

// Affichage d’un histogramme pour un seul canal (R, G ou B)
cv::Mat dessinerHistogrammeCanal(const int hist[256], const cv::Scalar& couleur, const std::string& titre);

#endif

