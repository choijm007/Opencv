
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

    cornerHarris_demo(0, 0);

    waitKey();
    return 0;
}



void cornerHarris_demo(int, void*)
{
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;


    int dx = 100;
    int dy = 100;
    
    Mat dst_trans = Mat::zeros(src.rows+dy, src.cols+dx, CV_32FC1);
    Mat dst_rot = Mat::zeros(src.size(), CV_32FC1);
    Mat dst_scale = Mat::zeros(src.size(), CV_32FC1);
    Mat dst = Mat::zeros(src.size(), CV_32FC1);


    Mat src_rot, src_scale;
    Mat src_trans= Mat::zeros(src.rows + dy, src.cols + dx,src_gray.type());
    for (int i = 0; i < src_gray.rows; i++) for (int j = 0; j < src_gray.cols; j++) {
        src_trans.at<uchar>(i + dy, j + dx) = src_gray.at<uchar>(i, j);
    }

    rotate(src_gray, src_rot, ROTATE_90_CLOCKWISE);
    resize(src_gray, src_scale, Size(), 1.5, 1.5);


    cornerHarris(src_rot, dst_rot, blockSize, apertureSize, k);
    cornerHarris(src_scale, dst_scale, blockSize, apertureSize, k);
    cornerHarris(src_trans, dst_trans, blockSize, apertureSize, k);
    cornerHarris(src_gray, dst, blockSize, apertureSize, k);

    
    Mat dst_norm_rot;
    Mat dst_norm_scale, dst_norm_trans;
    Mat dst_norm;

    normalize(dst_rot, dst_norm_rot, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    normalize(dst_scale, dst_norm_scale, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    normalize(dst_trans, dst_norm_trans, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    

    Mat rot;
    Mat scale;
    Mat trans;
    Mat dst_norm_scaled;

    convertScaleAbs(dst_norm_rot, rot);
    convertScaleAbs(dst_norm_trans, trans);
    convertScaleAbs(dst_norm_scale, scale);
    convertScaleAbs(dst_norm, dst_norm_scaled);


    for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {
            //if ((int)dst_norm.at<float>(i, j) <= 62 + 1 && (int)dst_norm.at<float>(i, j) >= 62 - 1) continue;

            if ((int)dst_norm.at<float>(i, j) > thresh)
            {
                circle(dst_norm_scaled, Point(j, i), 5, Scalar(0), 2, 8, 0);

            }
        }
    }
    imshow("original", dst_norm_scaled);


    for (int i = 0; i < dst_norm_rot.rows; i++)
    {
        for (int j = 0; j < dst_norm_rot.cols; j++)
        {
            //if ((int)dst_norm.at<float>(i, j) <= 62 + 1 && (int)dst_norm.at<float>(i, j) >= 62 - 1) continue;

            if ((int)dst_norm_rot.at<float>(i, j) > thresh )
            {
                circle(rot, Point(j, i), 5, Scalar(0), 2, 8, 0);

            }
        }
    }
    imshow("rotation", rot);

    for (int i = 0; i < dst_norm_scale.rows; i++)
    {
        for (int j = 0; j < dst_norm_scale.cols; j++)
        {
            //if ((int)dst_norm.at<float>(i, j) <= 62 + 1 && (int)dst_norm.at<float>(i, j) >= 62 - 1) continue;

            if ((int)dst_norm_scale.at<float>(i, j) > thresh)
            {
                
                circle(scale, Point(j, i), 5, Scalar(0), 2, 8, 0);
                

            }
        }
    }
    imshow("scale", scale);


    for (int i = 0; i < dst_norm_trans.rows; i++)
    {
        for (int j = 0; j < dst_norm_trans.cols; j++)
        {
            //if ((int)dst_norm.at<float>(i, j) <= 62 + 1 && (int)dst_norm.at<float>(i, j) >= 62 - 1) continue;

            if ((int)dst_norm_trans.at<float>(i, j) > thresh)
            {

                circle(trans, Point(j, i), 5, Scalar(0), 2, 8, 0);

            }
        }
    }
    imshow("translation", trans);

    // namedWindow(corners_window);
    
    
    
}