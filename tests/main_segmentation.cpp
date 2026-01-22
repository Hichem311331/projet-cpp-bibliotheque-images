#include <opencv2/opencv.hpp>
#include <iostream>
#include "segmentation.hpp"
using namespace std;
using namespace cv;
int main() {

Mat img =imread("image1.jpeg");
if (img.empty()) {
cout << "Erreur chargement image\n";
return -1;
}

  
if (img.channels()==3)
cvtColor(img,img,COLOR_BGR2GRAY);  // Conversion en niveaux de gris 

Segmentation seg;
seg.demanderparams();// demander à l'itisateur les nombre de k clusters et iterations 
seg.prepare(img);
seg.calcul();

Mat result = seg.resultat(img);
imshow("image originale", img);
imshow("image segmentee", result);
waitKey(0);

return 0;
}



