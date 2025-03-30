#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;


int main()
{

    Mat img = imread("9.jpg");
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    Mat img_canny;
    Canny(gray, img_canny, 100, 200);
    
    std::vector<Vec4i> linesP;
    // threshold, minLineLength, maxLineGap
    // 약한 line
    // 10, 0, 20
    // 강한 line
    // 50, 10, 0
    HoughLinesP(img_canny, linesP, 1, (CV_PI / 180), 10, 0, 20);

    Mat img_houghP;
    img.copyTo(img_houghP);

    for (int i = 0; i < linesP.size(); i++) {
        Vec4i l = linesP[i];
        line(img_houghP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1);
    }
    imshow("img", img);
    imshow("edge", img_canny);
    imshow("houghP", img_houghP);

    

    waitKey(0);
    return 0;
}

