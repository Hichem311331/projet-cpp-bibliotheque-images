#ifndef FILTRAGE_HPP
#define FILTRAGE_HPP

#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

class Filtrage
{
private:
    Mat image;

public:
    Filtrage(Mat img);

    Mat filtreMoyenne();
    Mat filtreGaussien();
    Mat filtreLaplacien();

    void afficher(const Mat& img, const string& titre);
    void sauvegarder(const Mat& img, const string& nom);
};

#endif
