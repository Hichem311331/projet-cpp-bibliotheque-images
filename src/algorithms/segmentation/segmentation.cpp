#include "segmentation.hpp"
#include <iostream>
using namespace std; 
using namespace cv;
Segmentation::Segmentation(int k, int iter)// constructeur 
    : K(k), ITER(iter), N(0),
      pixels(nullptr), labels(nullptr), centers(nullptr) {}

Segmentation::~Segmentation() {
    delete[] labels; // destru : libierer la memoire
    delete[] centers;
}

void Segmentation::demanderparams() {
cout << "Entrer le nombre de clusters (K) : ";
cin >> K;

cout << "Entrer le nombre d'iterations : ";
cin >> ITER;

if (K <= 0) {
	cout << "K invalide, K = 2 par defaut\n";
        K = 2;
    }

if (ITER <= 0) {
	cout << "ITER invalide, ITER = 100 par defaut\n";
        ITER = 100;
    }
}

void Segmentation::prepare(const cv::Mat& img) {
    N = img.rows * img.cols;// taillde de l'image
    pixels = img.data;

    delete[] labels;
    delete[] centers;
    labels = new int[N];
    centers = new float[K];

    // Initialisation des centroides
    for (int k = 0; k < K; k++) {
        int idx = (k * N) / K;
        centers[k] = pixels[idx];
    }
}


void Segmentation::calcul() {// calucl du Kmeans
    for (int it = 0; it < ITER; it++) {

        for (int i = 0; i < N; i++) {// attribution des labels
            float minDist = 1e9f;
            int best = 0;

            for (int k = 0; k < K; k++) {
                float d = (float)pixels[i] - centers[k];
                float dist = d * d;
                if (dist < minDist) {
                    minDist = dist;
                    best = k;
                }
            }
            labels[i] = best;
        }

        // MàJ des centres
        float* sum = new float[K];
        int* count = new int[K];

        for (int k = 0; k < K; k++) {
            sum[k] = 0.0f;
            count[k] = 0;
        }

        for (int i = 0; i < N; i++) {
            int k = labels[i];
            sum[k] += pixels[i];
            count[k]++;
        }

        for (int k = 0; k < K; k++) {
            if (count[k] > 0)
                centers[k] = sum[k] / count[k];
        }
        delete[] sum;
        delete[] count;//liberation
    }
}

Mat Segmentation::resultat(const Mat& img) const { //image segmentée
    Mat result = img.clone(); // creation dune copie de limage
    unsigned char* out = result.data;

    for (int i = 0; i < N; i++) {
        float v = centers[labels[i]];
        if (v < 0) v = 0;
        if (v > 255) v = 255;
        out[i] = static_cast<unsigned char>(v);
    }

    return result;
}
