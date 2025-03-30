
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
void change_ld(unsigned char* src, unsigned char* dst, int width, int height);
void change_ud(unsigned char* src, unsigned char* dst, int width, int height);
void add_value(unsigned char* src, unsigned char* dst, int width, int height, int val);
void change_ld_color(unsigned char* src, unsigned char* dst, int width, int height);
void avg_value(unsigned char* src1, unsigned char* src2, unsigned char* dst, int width, int height);
void sub_img(unsigned char* src1, unsigned char* src2, unsigned char* dst, int width, int height);
int Clib(int n);

int main()
{

    // 상하 좌우 반전
    Mat src = imread("Lenna.png", IMREAD_GRAYSCALE);

    imshow("src", src);

    Mat ud, ld;
    Mat add, avg, sub;

    ud = src.clone();
    ld = src.clone();

    change_ld(src.data, ld.data, src.cols, src.rows);
    change_ud(src.data, ud.data, src.cols, src.rows);

    imshow("ud", ud);
    imshow("ld", ld);


    // 이미지 연산을 수행

    src = imread("Lenna.png");

    Mat ld_color = src.clone();
    add = src.clone();
    avg = src.clone();
    sub = src.clone();

    change_ld_color(src.data, ld_color.data, src.cols, src.rows);
    imshow("ldcolor", ld_color);
    add_value(src.data, add.data, src.cols, src.rows, 70);
    avg_value(src.data, ld_color.data, avg.data, src.cols, src.rows);
    sub_img(src.data, ld_color.data, sub.data, src.cols, src.rows);


    imshow("add", add);
    imshow("avg", avg);
    imshow("sub", sub);

    waitKey();

    return 0;
}


void change_ld(unsigned char* src, unsigned char* dst, int width, int height)
{
    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        dst[width * j + width - 1 - i] = src[width * j + i];
    }


}

void change_ud(unsigned char* src, unsigned char* dst, int width, int height)
{
    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        dst[width * (height - 1 - j) + i] = src[width * j + i];
    }
}

void add_value(unsigned char* src, unsigned char* dst, int width, int height, int val) {
    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        dst[3 * (width * j + i)] = Clib(src[3 * (width * j + i)] + val);
        dst[3 * (width * j + i) + 1] = Clib(src[3 * (width * j + i) + 1] + val);
        dst[3 * (width * j + i) + 2] = Clib(src[3 * (width * j + i) + 2] + val);
    }
}

void avg_value(unsigned char* src1, unsigned char* src2, unsigned char* dst, int width, int height) {
    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        dst[3 * (width * j + i)] = int((src1[3 * (width * j + i)] + src2[3 * (width * j + i)]) / 2);
        dst[3 * (width * j + i) + 1] = int((src1[3 * (width * j + i) + 1] + src2[3 * (width * j + i) + 1]) / 2);
        dst[3 * (width * j + i) + 2] = int((src1[3 * (width * j + i) + 2] + src2[3 * (width * j + i) + 2]) / 2);
    }
}

void sub_img(unsigned char* src1, unsigned char* src2, unsigned char* dst, int width, int height) {
    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        dst[3 * (width * j + i)] = Clib(src1[3 * (width * j + i)] - src2[3 * (width * j + i)]);
        dst[3 * (width * j + i) + 1] = Clib(src1[3 * (width * j + i) + 1] - src2[3 * (width * j + i) + 1]);
        dst[3 * (width * j + i) + 2] = Clib(src1[3 * (width * j + i) + 2] - src2[3 * (width * j + i) + 2]);
    }
}

void change_ld_color(unsigned char* src, unsigned char* dst, int width, int height)
{
    for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
        dst[3 * (width * j + width - 1 - i)] = src[3 * (width * j + i)];
        dst[3 * (width * j + width - 1 - i) + 1] = src[3 * (width * j + i) + 1];
        dst[3 * (width * j + width - 1 - i) + 2] = src[3 * (width * j + i) + 2];

    }


}

int Clib(int n) {
    if (n < 0) return 0;
    if (n > 255) return 255;
    return n;
}