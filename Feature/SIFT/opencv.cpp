#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgproc.hpp"
//#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;
//using namespace cv::xfeatures2d;
using std::cout;
using std::endl;

const char* keys =
"{ help h |                  | Print help message. }"
"{ input1 | box.png          | Path to input image 1. }"
"{ input2 | box_in_scene.png | Path to input image 2. }";

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv, keys);
    Mat img1 = imread("../img1.png");
    Mat img2 = imread("../img2.png");
    //Mat img1 = imread("../Detect Image/image1.jpg");
    //Mat img2 = imread("../Detect Image/image2.jpg");

    resize(img1, img1, Size(), 1 / 5.0, 1 / 5.0);
    resize(img2, img2, Size(), 1 / 5.0, 1 / 5.0);

    Mat img1_gray;
    Mat img2_gray;
    cvtColor(img1, img1_gray, COLOR_BGR2GRAY);
    cvtColor(img2, img2_gray, COLOR_BGR2GRAY);


    if (img1.empty() || img2.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }
    cout << "img1 size : " << img1.size() << endl;
    cout << "img2 size : " << img2.size() << endl;
    

    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    int minHessian = 500;
    Ptr<SIFT> detector = SIFT::create(minHessian);

    int M = 50;
    int N = 50;
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;

    ///////////////////// M*N 블록으로 나누고 각 블록에서 독립적으로 특징점 추출
    for (int h = 0; h < img1.rows; h+=M)for (int w = 0; w < img1.cols; w+=N) {
        Rect window(w, h, M, N);
        if (h + M >= img1.rows || w + N >= img1.cols) {
            window = Rect(w, h, img1.cols - w, img1.rows - h);
        }
        Mat tmp = img1_gray(window);

        vector<KeyPoint> tmp_keyPoint;
        Mat tmp_descriptors;
        detector->detectAndCompute(tmp, noArray(), tmp_keyPoint, tmp_descriptors);

        for (int i = 0; i < tmp_keyPoint.size(); i++) {
            tmp_keyPoint[i].pt.x += w;
            tmp_keyPoint[i].pt.y += h;
        }
        keypoints1.insert(keypoints1.end(), tmp_keyPoint.begin(), tmp_keyPoint.end());
        if (!tmp_descriptors.empty()) {
            if (descriptors1.empty()) {
                descriptors1 = tmp_descriptors.clone();
            }
            else {
                // vertical 방향으로 이어붙이기
                vconcat(descriptors1, tmp_descriptors, descriptors1);
            }
        }

    }

    for (int h = 0; h < img2.rows; h += M)for (int w = 0; w < img2.cols; w += N) {
        Rect window(w, h, M, N);
        if (h + M >= img2.rows || w + N >= img2.cols) {
            window = Rect(w, h, img2.cols - w, img2.rows - h);
        }
        Mat tmp = img2_gray(window);

        vector<KeyPoint> tmp_keyPoint;
        Mat tmp_descriptors;
        detector->detectAndCompute(tmp, noArray(), tmp_keyPoint, tmp_descriptors);


        for (int i = 0; i < tmp_keyPoint.size(); i++) {
            tmp_keyPoint[i].pt.x += w;
            tmp_keyPoint[i].pt.y += h;
        }
        keypoints2.insert(keypoints2.end(), tmp_keyPoint.begin(), tmp_keyPoint.end());
        if (!tmp_descriptors.empty()) {
            if (descriptors2.empty()) {
                descriptors2 = tmp_descriptors.clone();
            }
            else {
                vconcat(descriptors2, tmp_descriptors, descriptors2);
            }
        }

    }


    //std::vector<KeyPoint> keypoints1, keypoints2;
    //Mat descriptors1, descriptors2;
    //detector->detectAndCompute(img1_gray, noArray(), keypoints1, descriptors1);
    //detector->detectAndCompute(img2_gray, noArray(), keypoints2, descriptors2);

    for (int i = 0; i < keypoints1.size(); i++) {
        circle(img1, Point(keypoints1[i].pt.x, keypoints1[i].pt.y),keypoints1[i].size / 2.0, Scalar(0, 255, 0), 1);
    }
    for (int i = 0; i < keypoints2.size(); i++) {
        circle(img2, Point(keypoints2[i].pt.x, keypoints2[i].pt.y), keypoints2[i].size / 2.0, Scalar(0, 255, 0), 1);
    }
    cout << endl << "minHessian : " << minHessian << endl;
    cout <<"feature Point size : " << keypoints1.size() << endl<<endl;
    imshow("img1", img1);
    imshow("img2", img2);
    waitKey(0);

    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // Since SURF is a floating-point descriptor NORM_L2 is used
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.7f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }

    //-- Draw matches
    Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, Scalar::all(-1),
        Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //-- Show detected matches
    imshow("Good Matches", img_matches);

    waitKey();
    return 0;
}
