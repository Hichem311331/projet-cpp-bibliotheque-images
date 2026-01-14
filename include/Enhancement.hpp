#ifndef ENHANCEMENT_HPP
#define ENHANCEMENT_HPP

#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

class Enhancement {
private:
    Mat image;
   
public:
    Enhancement(Mat img);
    Mat calculerLaplacien(Mat img);
    Mat appliquerRehaussement();
    void afficher(Mat img, const string& titre);
    void sauvegarder(Mat img, const string& nomFichier);
};

#endif
