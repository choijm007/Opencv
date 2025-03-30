// PSNR.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


#define PI 3.141592


unsigned char interpolation(const unsigned char* scr, int width, int height, float x, float y);
void Resize_Pic(unsigned char* scr, unsigned char* dst, int height, int width, int nh, int nw);
void Rotate_Pic(unsigned char* scr, unsigned char* dst, int height, int width, int rad);
unsigned char clamp(float n);

int main()
{
	Mat img_in;

	// image 읽고 gray로 바꾸기
	img_in = imread("Lena_256x256.png");
	cvtColor(img_in, img_in, cv::COLOR_RGB2GRAY);
	imshow("source img", img_in);
	int h;
	int w;

	///////////Resize///////////

	h = 512;
	w = 512;

	Mat ResizedPic_512x512(h, w, CV_8UC1);
	Resize_Pic(img_in.data, ResizedPic_512x512.data, img_in.rows, img_in.cols, h, w);
	
	h = 128;
	w = 128;
	Mat ResizedPic_436x436(h, w, CV_8UC1);
	Resize_Pic(img_in.data, ResizedPic_436x436.data, img_in.rows, img_in.cols, h, w);

	////////////회전////////////

	Mat Rotate_30(256, 256, CV_8UC1);
	Mat Rotate_45(256, 256, CV_8UC1);
	Mat Rotate_60(256, 256, CV_8UC1);
	Mat Rotate_r(256, 256, CV_8UC1);


	/// 사용자 입력
	//int r;
	//cout << "얼마나 회전할까요: ";
	//cin >> r;
	//
	//Rotate_Pic(img_in.data, Rotate_r.data, img_in.rows, img_in.cols, r);

	Rotate_Pic(img_in.data, Rotate_30.data, img_in.rows, img_in.cols, 30);
	Rotate_Pic(img_in.data, Rotate_45.data, img_in.rows, img_in.cols, 45);
	Rotate_Pic(img_in.data, Rotate_60.data, img_in.rows, img_in.cols, 60);



	imshow("output image 512x512", ResizedPic_512x512);
	imshow("output image 436x436", ResizedPic_436x436);

	imshow("output image user Rotate", Rotate_r);
	imshow("output image Rotate 30", Rotate_30);
	imshow("output image Rotate 45", Rotate_45);
	imshow("output image Rotate 60", Rotate_60);


	waitKey(0);

	return 0;
}



void Resize_Pic(unsigned char* scr, unsigned char* dst, int height, int width, int nh, int nw) {
	float x, y;
	y = (float)height / nh;
	x = (float)width / nw;
	for (int j = 0; j < nh; j++) for (int i = 0; i < nw; i++) {

		dst[nw * j + i] = interpolation(scr, width, height, i * x, j * y);
	}
}


void Rotate_Pic(unsigned char* scr, unsigned char* dst, int height, int width, int rad){
	int mid_x = width/2;
	int mid_y = height/2;

	float c = cos(-rad * (PI / 180.0));
	float s = sin(-rad * (PI / 180.0));

	float x, y;
	float new_x, new_y;
	for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
		x = i - mid_x;
		y = j - mid_y;

		new_x = c* x - s * y + mid_x;
		new_y = s * x + c * y + mid_y;

		
		dst[width * j + i] = interpolation(scr, width, height, new_x, new_y);
		
	}

}


unsigned char interpolation(const unsigned char* scr, int width, int height,float x, float y) {	
	if (x < 0 || x >= width || y < 0 || y >= height)
		return 0;

	int x1 = int(x);
	int y1 = int(y);
	int x2 = x1 + 1;
	int y2 = y1 + 1;

	if (x2 >= width) x2 = width - 1;
	if (y2 >= height) y2 = height - 1;

	
	unsigned char p1 = scr[width * y1 + x1];
	unsigned char p2 = scr[width * y1 + x2];
	unsigned char p3 = scr[width * y2 + x1];
	unsigned char p4 = scr[width * y2 + x2];

	float a = x - x1;
	float b = y - y1;

	
	float q1 = (1 - a) * p1 + a * p2;
	float q2 = (1 - a) * p3 + a * p4;

	
	unsigned char q = clamp((1 - b) * q1 + b * q2);

	return q;
}

unsigned char clamp(float n) {
	if (n < 0)
		return 0;
	if (n > 255)
		return 255;
	return (unsigned char)n;
}