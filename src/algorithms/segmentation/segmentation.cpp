#include "segmentation.hpp"
#include <iostream>

using namespace cv;

Segmentation::Segmentation(int k, int iter)//constructeur
    : K(k), ITER(iter), N(0), pixels(nullptr), labels(nullptr), centers(nullptr) {}

Segmentation::~Segmentation() {//destructeur
    delete[] labels;
    delete[] centers;
}

void Segmentation::prepare(const Mat& img) {
    
    N = img.rows * img.cols;
    pixels = img.data;

    delete[] labels;
    delete[] centers;

    labels = new int[N];
    centers = new float[K];

    // init centres déterministe
        for (int k = 0; k < K; k++) {
        int idx = (k * N) / K;
        centers[k] = pixels[idx];
    }
}

void Segmentation::run() {
    for (int it = 0; it < ITER; it++) {

        // assignation
        for (int i = 0; i < N; i++) {
            float minDist = 1e9f;
            int best = 0;

            for (int k = 0; k < K; k++) {
                float d = (float)pixels[i] - centers[k];
                float dist = d * d;
                if (dist < minDist) {
                    minDist = dist;
                    best=k;
                }
            }
            labels[i] = best;
        }

        // MAJ des centres
        float* sum = new float[K];
        int* count = new int[K];
        for (int k = 0; k < K; k++) { sum[k] = 0.0f; count[k] = 0; }

        for (int i = 0; i < N; i++) {
            int k = labels[i];
            sum[k] += pixels[i];
            count[k]++;
        }

        for (int k = 0; k < K; k++) {
            if (count[k] > 0) centers[k] = sum[k] / count[k];
        }

        delete[] sum;
        delete[] count;
    }
}

Mat Segmentation::getResult(const Mat& img) const {
    Mat result = img.clone();   // creation de la nouvelle image ne modifie pas l'original
    unsigned char* out = result.data;

    for (int i = 0; i < N; i++) {
        float v = centers[labels[i]];
        if (v < 0) v = 0;
        if (v > 255) v = 255;
        out[i] = (unsigned char)v;
    }

    return result;
}
