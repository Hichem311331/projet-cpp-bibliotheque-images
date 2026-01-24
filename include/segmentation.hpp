#ifndef SEGMENTATION_HPP
#define SEGMENTATION_HPP
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
class Segmentation {
private:
    int K;
    int ITER;

    int N;
    unsigned char* pixels; // img.data (image d'entrée)

    int* labels;
    float* centers;

public:
    Segmentation(int k = 3, int iter = 10);
    ~Segmentation();// destructeur :pour libertaion de la memoire

    void prepare(const Mat& img);
    // calcul du kmeans
    void run();
    // image resultante
    Mat getResult(const Mat& img) const;
};

#endif
