#include "../include/Enhancement.h"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    cout << " Test Algorithme Rehaussement " << endl;
   
    Mat testImage = Mat::zeros(300, 300, CV_8UC1);
    circle(testImage, Point(150, 150), 80, Scalar(255), -1);
   
    Enhancement enh(testImage);
    Mat result = enh.appliquerRehaussement();
   
    enh.afficher(testImage, "Original");
    enh.afficher(result, "Rehausse");
   
    cout << "Appuyez sur une touche..." << endl;
    waitKey(0);
   
    enh.sauvegarder(result, "image_rehaussee.jpg");
   
    return 0;
}
