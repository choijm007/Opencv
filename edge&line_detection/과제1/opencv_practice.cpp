#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


void Filtering(Mat& scr, Mat& dst, Mat& filter, int v);
Mat Padding(Mat s, int width, int height, int FilterSize, int type);
void getMagPhase(const Mat& x, const Mat& y, Mat& mag);
unsigned char clamp(double v);

int main()
{

    /////////////////////// 문제 1 /////////////////////
    Mat gray = imread("lena.jpg");

    Mat scr(gray.size(), CV_8UC1);
    for (int h = 0; h < scr.rows; h++) for (int w = 0; w < scr.cols; w++) {
        uchar B = gray.data[3*(h * scr.rows + w)];
        uchar G = gray.data[3 * (h * scr.rows + w)+1];
        uchar R = gray.data[3 * (h * scr.rows + w)+2];

        scr.data[h * scr.rows + w] = R * 0.299 + G * 0.587 + B * 0.114;
    }


    Mat sobel_x = (Mat_<float>(3, 3) << -1, -2, -1,
        0, 0, 0,
        1, 2, 1);
    Mat sobel_y = (Mat_<float>(3, 3) << -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1);


    Mat x(scr.size(), CV_32F);
    Mat y(scr.size(), CV_32F);

    Filtering(scr, x, sobel_x, 1);
    Filtering(scr, y, sobel_y, 1);

    Mat mag(scr.size(), CV_8UC1);
    Mat rst = mag.clone();
    getMagPhase(x, y, mag);

    for (int i = 0; i < mag.rows * mag.cols; i++) {
        uchar d = 0;
        if (mag.data[i] > 255 * 0.4) {
            d = 255;
        }
        rst.data[i] = d;
    }


    imshow("image", mag);
    imshow("threshold", rst);


    waitKey(0);
    return 0;
}

void Filtering(Mat& scr, Mat& dst, Mat& filter, int v) {
    int height = scr.rows;
    int width = scr.cols;
    int n = 2 * v + 1;

    Mat pad = Padding(scr, width, height, n, dst.type());
    int PadSize = n / 2;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            double conv = 0.0;
            for (int j = 0; j < n; j++) {
                for (int i = 0; i < n; i++) {
                    conv += pad.at<float>(h + j, w + i) * filter.at<float>(j, i);
                }
            }
            dst.at<float>(h, w) = static_cast<float>(conv);
        }
    }
}

Mat Padding(Mat s, int width, int height, int FilterSize, int type) {
    int PadSize = FilterSize / 2;
    int nheight = height + 2 * PadSize;
    int nwidth = width + 2 * PadSize;

    Mat scr;
    s.convertTo(scr, CV_32F);
    Mat rtn(nheight, nwidth, CV_32F, Scalar(0));

    // 원본 이미지 가운데 넣기
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            rtn.at<float>(h + PadSize, w + PadSize) = scr.at<float>(h, w);
        }
    }

    // 위쪽과 아래쪽 패딩
    for (int w = 0; w < width; w++) {
        for (int h = 0; h < PadSize; h++) {
            rtn.at<float>(h, w + PadSize) = scr.at<float>(0, w);  // 위쪽
            rtn.at<float>(h + height + PadSize, w + PadSize) = scr.at<float>(height - 1, w);  // 아래쪽
        }
    }

    // 왼쪽과 오른쪽 패딩
    for (int h = 0; h < nheight; h++) {
        for (int w = 0; w < PadSize; w++) {
            rtn.at<float>(h, w) = rtn.at<float>(h, PadSize);  // 왼쪽
            rtn.at<float>(h, w + PadSize + width) = rtn.at<float>(h, PadSize + width - 1);  // 오른쪽
        }
    }

    return rtn;
}
void getMagPhase(const Mat& x, const Mat& y, Mat& mag) {
    for (int i = 0; i < x.rows; i++) {
        for (int j = 0; j < x.cols; j++) {
            float gx = x.at<float>(i, j);
            float gy = y.at<float>(i, j);

            
            mag.at<uchar>(i, j) = clamp(abs(gx/2)+abs(gy/2));

        }
    }
}


unsigned char clamp(double v) {
    if (v > 255)return 255;
    if (v < 0)return 0;
    return (unsigned char)v;
};