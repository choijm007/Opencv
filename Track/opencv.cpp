#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void onMouse(int evt, int x, int y, int flags, void* params);
vector<Mat> vid;
bool click = false;
int lx, ly;
Mat tmp;
Mat frame;
int num = 0;
Rect window;
Rect tmp_rect;

int main()
{
	VideoCapture capture("video.mp4");
	int k;

	if (!capture.isOpened()) {
		printf("Video file can not open.\n");
		return 0;

	}
	namedWindow("video");
	setMouseCallback("video", onMouse, &frame);
	//while (1) {
	//	Mat r;
	//	capture >> r;
	//	if (r.empty())
	//		break;

	//	vid.push_back(r);
	//}
	capture >> frame;

	imshow("video", frame);
	waitKey(0);


	Mat roi, hsv_roi, mask;

	roi = frame(window);
	cvtColor(roi, hsv_roi, COLOR_BGR2HSV);
	inRange(hsv_roi, Scalar(0, 60, 32), Scalar(180, 255, 255), mask);
	float range_[] = { 0, 180 };
	const float* range[] = { range_ };
	Mat roi_hist;
	int histSize[] = { 180 };
	int channels[] = { 0 };
	calcHist(&hsv_roi, 1, channels, mask, roi_hist, 1, histSize, range);
	normalize(roi_hist, roi_hist, 0, 255, NORM_MINMAX);

	TermCriteria term_crit(TermCriteria::EPS | TermCriteria::COUNT, 10, 1);
	while (true) {
		Mat hsv, dst;
		capture >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		calcBackProject(&hsv, 1, channels, roi_hist, dst, range);
		// apply camshift to get the new location
		RotatedRect rot_rect = CamShift(dst, window, term_crit);
		// Draw it on image
		Point2f points[4];
		rot_rect.points(points);
		for (int i = 0; i < 4; i++)
			line(frame, points[i], points[(i + 1) % 4], 255, 2);
		imshow("img2", frame);
		int keyboard = waitKey(30);
		if (keyboard == 'q' || keyboard == 27)
			break;
	}



	

    return 0;

}


void onMouse(int evt, int x, int y, int flags, void* params) {
	if (evt == EVENT_LBUTTONDOWN) {
		click = true;
		lx = x;
		ly = y;
	}
	else if (evt == EVENT_LBUTTONUP) {
		click = false;

		window = tmp_rect;
		imshow("video", tmp);
		// vid[num] = tmp.clone();
	}
	else if (evt == EVENT_MOUSEMOVE) {
		if (click) {
			tmp = frame.clone();
			
			int a = min(lx, x);
			int b = min(ly, y);
			int width = abs(x - lx);
			int height = abs(y - ly);

			tmp_rect = Rect(a, b, width, height);
			rectangle(tmp, window, Scalar(0, 0, 255));
			imshow("video", tmp);
		}

	}
}
