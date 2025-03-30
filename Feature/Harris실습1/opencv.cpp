
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;

const char* source_window = "Source image";
const char* corners_window = "Corners detected";

void cornerHarris_demo(int, void*);

int main(int argc, char** argv)
{

    src = imread("../Detect Image/bigben_16.jpg");
    if (src.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow(source_window);
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src);

    //////////////////// Lena 이미지 최대 최소 ////////////////////

    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    Mat lena = imread("../lena.jpg", IMREAD_GRAYSCALE);
    Mat dst = Mat::zeros(src.size(), CV_32FC1);
    cornerHarris(lena, dst, blockSize, apertureSize, k);

    cout << "img size" << lena.size() << endl;
    cout << "dst size" << dst.size() << endl;

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc);
    cout << endl << "Lena" << endl;
    cout << "Min: " << minVal << "Max: " << maxVal << endl;

    cornerHarris_demo(0, 0);

    waitKey();
    return 0;
}



void cornerHarris_demo(int, void*)
{
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    Mat dst = Mat::zeros(src.size(), CV_32FC1);
    cornerHarris(src_gray, dst, blockSize, apertureSize, k);

    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc);
    cout << endl << "input" << endl;
    cout << "Min: " << minVal << "Max: " << maxVal << endl;

    //float minValue = dst.at<float>(0,0);
    //float maxValue=minValue;

    //for (int i = 0; i < dst.rows; i++) {
    //    for (int j = 0; j < dst.cols; j++) {
    //        float tmp = dst.at<float>(i, j);
    //        if (minValue > tmp) minValue = tmp;
    //        if (maxValue < tmp) maxValue = tmp;
    //    }
    //}

    // cout<<endl << "Min: " << minValue << "Max: " << maxValue << endl;

    
    Mat dst_norm, dst_norm_scaled;
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);



    for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {


            if ((int)dst_norm.at<float>(i, j) > thresh )
            {
                circle(dst_norm_scaled, Point(j, i), 5, Scalar(0), 2, 8, 0);

            }
        }
    }



    namedWindow(corners_window);
    imshow(corners_window, dst_norm_scaled);
}