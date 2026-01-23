#ifndef DETECTION_CONTOUR_HPP
#define DETECTION_CONTOUR_HPP

#include <vector>

class Image {
private:
    std::vector<std::vector<int>> pixels;
    int largeur;
    int hauteur;

public:
    Image(int h, int l);
    Image(const std::vector<std::vector<int>>& data);
    
    int getLargeur() const;
    int getHauteur() const;
    int getPixel(int y, int x) const;
    void setPixel(int y, int x, int valeur);
    
    std::vector<std::vector<int>> getData() const;
};

class DetectionContour {
private:
    // Noyau Laplacien
    int noyau[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };
    
    int convolutionPoint(const Image& img, int y, int x);
    int clamp(int valeur, int min, int max);

public:
    DetectionContour();
    
    Image convertirGris(const Image& img);
    Image appliquerLaplacien(const Image& img);
    Image seuillage(const Image& img, int seuil);
};

#endif