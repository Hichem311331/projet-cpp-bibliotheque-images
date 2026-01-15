#include "Filtrage.hpp"
//constructeur
// si l'image est en couleur (RGB), elle est convertie en niveau de gris 
Filtrage::Filtrage(Mat img)
{
   if (img.channels() == 3)
        cvtColor(img, image, COLOR_BGR2GRAY);
    else
        image = img.clone();
}

void Filtrage::afficher(const Mat& img, const string& titre)
{
    imshow(titre, img);
}

void Filtrage::sauvegarder(const Mat& img, const string& nom)
{
    imwrite(nom, img);
}

// filtre moyenneur 3x3
Mat Filtrage::filtreMoyenne()
{
    Mat out = image.clone();

    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
            int somme = 0;

            for (int j = -1; j <= 1; j++)
                for (int i = -1; i <= 1; i++)
                    somme += image.at<uchar>(y+j, x+i);

            out.at<uchar>(y,x) = somme / 9;
        }
    }
    return out;
}
// filtre gaussien 3x3
Mat Filtrage::filtreGaussien()
{
    Mat out = image.clone();

    int K[3][3] = {
        {1,2,1},
        {2,4,2},
        {1,2,1}
    };

    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
            int somme = 0;

            for (int j = -1; j <= 1; j++)
                for (int i = -1; i <= 1; i++)
                    somme += image.at<uchar>(y+j, x+i) * K[j+1][i+1];

            out.at<uchar>(y,x) = somme / 16;
        }
    }
    return out;
}

// filtre laplacien 
Mat Filtrage::filtreLaplacien()
{
    Mat out = image.clone();

    int K[3][3] = {
        {0,-1,0},
        {-1,4,-1},
        {0,-1,0}
    };

    for (int y = 1; y < image.rows - 1; y++)
    {
        for (int x = 1; x < image.cols - 1; x++)
        {
            int somme = 0;

            for (int j = -1; j <= 1; j++)
                for (int i = -1; i <= 1; i++)
                    somme += image.at<uchar>(y+j, x+i) * K[j+1][i+1];

            if (somme < 0) somme = 0;
            if (somme > 255) somme = 255;

            out.at<uchar>(y,x) = somme;
        }
    }
    return out;
}
