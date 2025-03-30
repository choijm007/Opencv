
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;
using namespace std;



int main()
{
    Mat black(256, 256, CV_8UC1);
    Mat white(256, 256, CV_8UC1);
    Mat rec(256, 256, CV_8UC1);
    Mat circle(256, 256, CV_8UC1);

    int height = rec.rows;
    int width = rec.cols;

    memset(black.data, 0, 256 * 256);
    memset(white.data, 255, 256 * 256);


    memset(rec.data, 0, 256 * 256);
    memset(circle.data, 0, 256 * 256);

    int recsize = 100;

    int num = int((height - recsize) / 2);

    for (int j = num; j < height - num; j++) for (int i = num; i < width - num; i++) {
        rec.data[width * j + i] = 255;
    }

    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        if (sqrt(pow(abs(i - 128), 2) + pow(abs(j - 128), 2)) < recsize)
            circle.data[width * j + i] = 255;
    }


    imshow("black", black);
    imshow("white", white);
    imshow("rec", rec);
    imshow("circle", circle);


    waitKey();

    return 0;
}
