#ifndef SEGMENTATION_HPP
#define SEGMENTATION_HPP

#include <opencv2/opencv.hpp>
using namespace cv;
class Segmentation {
private:
    int K;
    int ITER;
    int N;
    unsigned char* pixels;
    int* labels;
    float* centers;

public:
    Segmentation(int k = 2, int iter=100);// 2 et 100 par defaut : le min a faire
    ~Segmentation();// un desctructeur pour libérer la memoire
    void demanderparams();            
    void prepare(const Mat& img);
    void calcul();
    Mat resultat(const Mat& img) const;
};

#endif


