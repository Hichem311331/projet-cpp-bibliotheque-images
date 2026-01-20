#include <opencv2/opencv.hpp>
#include <iostream>
#include "segmentation.hpp"

using namespace cv;
using namespace std;
int main() {
    Mat img =imread("image1.jpeg");
    if (img.empty()) {
        cout << "Erreur image\n";
        return -1;
    }

    Segmentation seg(3, 10);

    seg.prepare(img);  
    seg.run();         
    Mat result =seg.getResult(img); 

    imshow("image Original", img);
    imshow("image Segmentée", result);
    waitKey(0);
    return 0;
}


