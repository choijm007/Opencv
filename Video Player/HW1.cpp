#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void make_square(Point x, Point y, Mat& pic);
void onMouse(int evt, int x, int y, int flags, void* params);
vector<Mat> vid;
bool click = false;
int lx, ly;
Mat tmp;
Mat frame;
int num = 0;

int main()
{
	VideoCapture capture("video.mp4");
	int k;

	if (!capture.isOpened()) {
		printf("Video file can not open.\n");
		return 0;

	}

	while (1) {
		Mat r;
		capture >> r;
		if (r.empty())
			break;

		vid.push_back(r);
		
	}
	printf("done");
	namedWindow("video");
	bool play = false;
	
	
	imshow("video", vid[0]);

	while (1) {
		k = waitKey(33);
		
		if (k == 32) {
			play = !play;
			if (play == false) {
				frame = vid[num];
				setMouseCallback("video", onMouse, &frame);
			}
		}
		else if (k == 'p' && play==false) {
			// p
			--num;
			if (num < 0) num = 0;
			imshow("video", vid[num]);
		}
		else if (k == 'n' && play == false) {
			// n
			++num;
			if (num >= vid.size()) num = vid.size() - 1;
			imshow("video", vid[num]);
		}

		if (num >= vid.size()) {
			play = false;
			continue;
		}

		if (play) {
			imshow("video", vid[num]);
			num++;
		}	

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
		
		vid[num] = tmp.clone();
	}
	else if (evt == EVENT_MOUSEMOVE) {
		if (click) {
			tmp = vid[num].clone();
			Point a(lx, ly);
			Point b(x, y);

			make_square(a, b, tmp);

			imshow("video", tmp);
		}

	}
}

void make_square(Point x, Point y, Mat& pic) {
	line(pic, Point(x.x, x.y), Point(x.x, y.y), Scalar(0, 0, 255), 1);
	line(pic, Point(x.x, x.y), Point(y.x, x.y), Scalar(0, 0, 255), 1);
	line(pic, Point(x.x, y.y), Point(y.x, y.y), Scalar(0, 0, 255), 1);
	line(pic, Point(y.x, x.y), Point(y.x, y.y), Scalar(0, 0, 255), 1);
}
