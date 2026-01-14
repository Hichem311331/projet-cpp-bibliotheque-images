#include "../../../include/Enhancement.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Enhancement::Enhancement(Mat img){
    image = img.clone();
}

Mat Enhancement::calculerLaplacien(Mat img){
    Mat gray, laplacian;
    if(img.channels() == 3){
        cvtColor(img, gray, COLOR_BGR2GRAY);
    } else{
        gray = img.clone();
    }
   
    laplacian = Mat::zeros(gray.size(), CV_8U);
    for(int i=1; i<gray.rows - 1; i++) {
        for(int j=1; j<gray.cols - 1; j++){
            int center = gray.at<uchar>(i,j);
            int top = gray.at<uchar>(i-1,j);
            int bottom = gray.at<uchar>(i+1,j);
            int left = gray.at<uchar>(i,j-1);
            int right = gray.at<uchar>(i,j+1);
            int result = -4 * center + top + bottom + left + right;
            result = abs(result);
            if (result > 255) result = 255;
            laplacian.at<uchar>(i,j) = (uchar)result;
        }
    }
    return laplacian;
}

Mat Enhancement::appliquerRehaussement() {
    Mat gray, laplacian, enhanced;
   
    if (image.channels() == 3) {
        cvtColor(image, gray, COLOR_BGR2GRAY);
    } else {
        gray = image.clone();
    }
   
    laplacian = calculerLaplacien(image);
    enhanced = Mat::zeros(gray.size(), CV_8U);
   
    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            int original = gray.at<uchar>(i, j);
            int lap = laplacian.at<uchar>(i, j);
            int result = original + (lap / 2);
           
            if (result > 255) result = 255;
            if (result < 0) result = 0;
           
            enhanced.at<uchar>(i, j) = (uchar)result;
        }
    }
   
    return enhanced;
}

void Enhancement::afficher(Mat img, const string& titre) {
    imshow(titre, img);
}

void Enhancement::sauvegarder(Mat img, const string& nomFichier) {
    imwrite(nomFichier, img);
    cout << "Image sauvegardee dans " << nomFichier << endl;
}
