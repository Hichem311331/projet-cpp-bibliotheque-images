#include "Detection_contour.hpp"
#include <algorithm>
#include <cmath>


//chargement image
Image::Image(int h, int l) : hauteur(h), largeur(l) {
    pixels.resize(hauteur, std::vector<int>(largeur, 0));
}

Image::Image(const std::vector<std::vector<int>>& data) {
    pixels = data;
    hauteur = data.size();
    largeur = data.empty() ? 0 : data[0].size();
}

int Image::getLargeur() const { return largeur; }
int Image::getHauteur() const { return hauteur; }

int Image::getPixel(int y, int x) const {
    if (y >= 0 && y < hauteur && x >= 0 && x < largeur) {
        return pixels[y][x];
    }
    return 0;
}

void Image::setPixel(int y, int x, int valeur) {
    if (y >= 0 && y < hauteur && x >= 0 && x < largeur) {
        pixels[y][x] = valeur;
    }
}

std::vector<std::vector<int>> Image::getData() const {
    return pixels;
}
//class detection de contour (conversion au niveau de gris , clamp pour qu'il n y'a pas de débordement et convolution)
DetectionContour::DetectionContour() {}

int DetectionContour::clamp(int valeur, int min, int max) {
    if (valeur < min) return min;
    if (valeur > max) return max;
    return valeur;
}

Image DetectionContour::convertirGris(const Image& img) {

    return img;
}

int DetectionContour::convolutionPoint(const Image& img, int y, int x) {
    int somme = 0;
    
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int py = y + dy;
            int px = x + dx;
            
            py = clamp(py, 0, img.getHauteur() - 1);
            px = clamp(px, 0, img.getLargeur() - 1);
            
            int pixelVal = img.getPixel(py, px);
            int noyauVal = noyau[dy + 1][dx + 1];
            
            somme += pixelVal * noyauVal;
        }
    }
    
    return somme;
}

Image DetectionContour::appliquerLaplacien(const Image& img) {
    int h = img.getHauteur();
    int l = img.getLargeur();
    Image resultat(h, l);
    
    // Appliquer la convolution à chaque pixel
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < l; x++) {
            int valeur = convolutionPoint(img, y, x);
            
            // Prendre la valeur absolue pour détecter les contours
            valeur = std::abs(valeur);
            
            // Normaliser entre 0 et 255
            valeur = clamp(valeur, 0, 255);
            
            resultat.setPixel(y, x, valeur);
        }
    }
    
    return resultat;
}

Image DetectionContour::seuillage(const Image& img, int seuil) {
    int h = img.getHauteur();
    int l = img.getLargeur();
    Image resultat(h, l);
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < l; x++) {
            int valeur = img.getPixel(y, x);
            // Binarisation : blanc (255) si > seuil, noir (0) sinon
            resultat.setPixel(y, x, valeur > seuil ? 255 : 0);
        }
    }
    
    return resultat;
}