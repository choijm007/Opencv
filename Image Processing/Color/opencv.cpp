#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

uchar clamp(double n);
void Gamma(unsigned char* scr, unsigned char* dst, int height, int width, double gamma, int channel);
void Navi(unsigned char* scr, unsigned char* dst, int height, int width, int channel);
void onMouse(int evt, int x, int y, int flags, void* params);
void HSIconvert(Mat& hsi, Mat& rgb);
void RGBconvert(Mat& rgb, Mat& hsi);
void GetPSNR(Mat& scr, Mat& comp);
void Equalization(unsigned char* scr, unsigned char* dst, int height, int width);
void Equalization_I(unsigned char* scr, int height, int width);

bool click = false;
Mat graph;
Mat tmp;
Mat scr;
Mat rst;
int r1=0, s1=255;
int r2=255, s2=0;
bool first=false, second = false;

bool f1=false, f2=false;

int main()
{
    
    scr = imread("lena.jpg");

    /////////////////// 문제 1 /////////////////// 
    
    //Mat gam = scr.clone();
    //Mat nav = scr.clone();
    //Gamma(scr.data, gam.data, scr.rows, scr.cols, 0.25, 3);
    //Navi(scr.data, nav.data, scr.rows, scr.cols, 3);
    //imshow("Gamma", gam);
    //imshow("Negative", nav);

    /////////////////// 문제 2 /////////////////// 

    //graph = Mat(256, 256, CV_8UC1);
    //

    //memset(graph.data, 255, 256 * 256);
    //line(graph, Point(0, 255), Point(255, 0), Scalar(0, 0, 0), 5);
    //imshow("graph", graph);
    //setMouseCallback("graph", onMouse, &graph);
    //
    //rst = scr.clone();
    

    /////////////////// 문제 3 /////////////////// 

    //Mat hs = scr.clone();
    //Mat rg = scr.clone();
    //RGBconvert(scr, hs);
    //HSIconvert(hs, rg);
    //
    //Mat his = scr.clone();
    //Mat his_res = scr.clone();
    //RGBconvert(scr, his);
    //Equalization_I(his.data, scr.rows, scr.cols);
    //HSIconvert(his, his_res);

    //Mat col = scr.clone();
    //Equalization(scr.data, col.data, scr.rows, scr.cols);
    //

    //imshow("color Histogram", col);
    //imshow("I histogram", his_res);
    //imshow("convert", rg);

    //GetPSNR(scr, rg);
    //

    /////////////////// 문제 4 /////////////////// 

    Mat mask = getStructuringElement(MORPH_RECT, Size(7, 7));
    Mat black = imread("black.png", IMREAD_GRAYSCALE);
    Mat white = imread("white.png", IMREAD_GRAYSCALE);
    
    resize(black, black, Size(256, 256));
    resize(white, white, Size(256, 256));
    Mat dilate_black;
    Mat erode_black;
    Mat dilate_white;
    Mat erode_white;
    Mat opening_white;
    Mat opening_black;
    Mat closing_white;
    Mat closing_black;

    // black 배경 영상을 팽창 침식
    dilate(black, dilate_black, mask, Point(-1, -1));   // 팽창
    erode(black, erode_black, mask, Point(-1, -1));     // 침식

    // white 배경 영상을 팽창 침식
    dilate(white, dilate_white, mask, Point(-1, -1));   //팽창
    erode(white, erode_white, mask, Point(-1, -1));     // 침식
    
    // opening
    dilate(erode_black, opening_black, mask, Point(-1, -1));
    dilate(erode_white, opening_white, mask, Point(-1, -1));

    //closing
    erode(dilate_black, closing_black, mask, Point(-1, -1));
    erode(dilate_white, closing_white, mask, Point(-1, -1));

    imshow("opening white", opening_white);
    imshow("closing white", closing_white);
    imshow("opening black", opening_black);
    imshow("closing black", closing_black);

    imshow("dilate white", dilate_white);
    imshow("erode white", erode_white);
    imshow("dilate black", dilate_black);
    imshow("erode black", erode_black);



    imshow("input", scr);
    waitKey(0);
    return 0;

}
void HSIconvert(Mat& hsi, Mat& rgb) {
    int height = rgb.rows;
    int width = rgb.cols;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            double H = static_cast<double>(hsi.data[3 * (h * width + w) + 2]);
            double S = static_cast<double>(hsi.data[3 * (h * width + w) + 1])/255.0;
            double I = static_cast<double>(hsi.data[3 * (h * width + w)]);

            H *= (360.0 / 255.0);  // HSI에서 Hue는 0-255 범위 -> 0-360으로 변환
            double H_rad = H * CV_PI / 180.0; // 라디안으로 변환

            double R = 0.0, G = 0.0, B = 0.0;

            if (H < 120) {  // H < 120도
                R = I * (1 + (S * cos(H_rad)) / cos(CV_PI / 3 - H_rad));
                B = I * (1 - S);
                G = 3 * I - (R + B);
            }
            else if (H < 240) {  // H < 240도
                H_rad = (H - 120.0) * CV_PI / 180.0; // 다시 라디안으로 변환
                G = I * (1 + (S * cos(H_rad)) / cos(CV_PI / 3 - H_rad));
                R = I * (1 - S);
                B = 3 * I - (R + G);
            }
            else {  // H >= 240도
                H_rad = (H - 240.0) * CV_PI / 180.0;
                B = I * (1 + (S * cos(H_rad)) / cos(CV_PI / 3 - H_rad));
                G = I * (1 - S);
                R = 3 * I - (G + B);
            }


            rgb.data[3 * (h * width + w) + 2] = clamp(R);
            rgb.data[3 * (h * width + w) + 1] = clamp(G);
            rgb.data[3 * (h * width + w)] = clamp(B);
        }
    }
}
void RGBconvert(Mat& rgb, Mat& hsi) {
    int height = rgb.rows;
    int width = rgb.cols;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            double R = static_cast<double>(rgb.data[3 * (h * width + w) + 2]);
            double G = static_cast<double>(rgb.data[3 * (h * width + w) + 1]);
            double B = static_cast<double>(rgb.data[3 * (h * width + w)]);

            double H, S, I;
            I = (R + G + B) / 3.0;


            S = 1 - 3 * (min({ R, G, B }) / (R + G + B));
            

            
                double up = 0.5 * ((R - G) + (R - B));
                double down = sqrt((R - G) * (R - G) + (R - B) * (G - B));

                double theta = acos(up / down);  // acos 범위 문제 해결

                if (B <= G) {
                    H = theta;
                }
                else {
                    H = 2 * CV_PI - theta;
                }

                H = H * 180 / CV_PI;  // 라디안에서 도 단위로 변환
                if (H < 0) H += 360;
            

                hsi.data[3 * (h * width + w) + 2] = (uchar)(H * (255 / 360)); // H 값은 0-255로 변환
            hsi.data[3 * (h * width + w) + 1] = (uchar)(S * 255);  // S 값은 0-255로 변환
            hsi.data[3 * (h * width + w)] = (uchar)(I);  // I 값은 0-255로 변환
        }
    }
}
void onMouse(int evt, int x, int y, int flags, void* params) {
    if (evt == EVENT_LBUTTONDOWN) {
        click = true;
        int f = 255 - x;
        
        if (!first) {
            graph = Mat(256, 256, CV_8UC1);
            memset(graph.data, 255, 256 * 256);
            if (abs(f - y) < 50) {
                first = true;
                r1 = x;
                f1 = true;
            }

        }
        else if (!second) {
            if (tmp.data[y*256+x]==0) {
                second = true;
                r2 = x;
                f2 = true;
            }          
        }
        else {
            if (pow(x - r1, 2) + pow(s1 - y, 2) < 25) {
                f1 = true;
            }
            else if (pow(x - r2, 2) + pow(s2 - y, 2) < 25) {
                f2 = true;
            }
        }
    }
    else if (evt == EVENT_LBUTTONUP) {
        click = false;
        if (f1) {
            f1 = false;
            s1 = y;
            r1 = x;
        }
        else if (f2) {
            f2 = false;
            s2 = y;
            r2 = x;
        }
        imshow("graph", tmp);

        for (int h = 0; h < scr.rows; h++) for (int w = 0; w < scr.cols; w++) {
            for (int c = 0; c < scr.channels(); c++) {
                uchar pix = scr.data[scr.channels() * (h * scr.cols +w) + c];
                double f;
                if (pix < r1) {
                    f = ((255 - s1) / r1) * pix;
                }
                else if (pix < r2) {
                    f = (s1 - s2) / (r2 - r1) * (pix - r1) + 255 - s1;
                }
                else {
                    f = (s2 / (256 - r2)) * (pix-r2) + 255-s2;
                }
                rst.data[scr.channels() * (h * scr.cols + w) + c] = clamp(f);
            }
        }
        imshow("result", rst);
    }
    else if (evt == EVENT_MOUSEMOVE) {
        // printf("x : %d, y : %d, y2 : %d\n",x , 255 - x, y);
        if (click) {
            
            if (f1) {
                tmp = graph.clone();
                line(tmp, Point(0, 255), Point(x, y), Scalar(0, 0, 0), 5);
                line(tmp, Point(x, y), Point(r2, s2), Scalar(0, 0, 0), 5);
                line(tmp, Point(r2, s2), Point(255, 0), Scalar(0, 0, 0), 5);
            }else if(f2) {
                tmp = graph.clone();
                line(tmp, Point(0, 255), Point(r1, s1), Scalar(0, 0, 0), 5);
                line(tmp, Point(r1, s1), Point(x, y), Scalar(0, 0, 0), 5);
                line(tmp, Point(x, y), Point(255, 0), Scalar(0, 0, 0), 5);

            }


            imshow("graph", tmp);
        }


    }
}
void Gamma(unsigned char* scr, unsigned char* dst, int height, int width, double gamma, int channel) {

    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        for (int c = 0; c < channel; c++) {
            dst[channel*(h*width+w)+c]= clamp(pow((double)scr[channel * (h * width + w) + c] / 255, gamma) * 255);
        }
    }

    return;

}
void Navi(unsigned char* scr, unsigned char* dst, int height, int width, int channel) {
    for (int i = 0; i < height * width*channel; i++) {
        dst[i] = 255 - scr[i];
    }
    return;
}
uchar clamp(double n) {
    if (n > 255) {
        return 255;
    }
    if (n < 0)return 0;
    return (uchar)n;
}
void Equalization(unsigned char* scr, unsigned char* dst, int height, int width) {

    for (int c = 0; c < 3; c++) {
        // 각 픽셀 값의 해당하는 픽셀 수를 저장할 배열(Histogram)
        int p[256] = { 0 };
        for (int i = 0; i < height * width; i++) {
            // 각 픽셀 값의 해당하는 픽셀 수를 저장하는 로직
            p[scr[3 * i + c]]++;
        }

        // 입력 영상의 cdf을 저장할 배열
        double cdf[256] = { 0 };

        int nested = 0;
        for (int i = 0; i < 256; i++) {
            // 픽셀 갯수를 중첩하게 더해주며, 그 값에 전체 픽셀 수를 나눈 값을 cdf배열에 저장
            nested += p[i];
            cdf[i] = (double)(nested) / (height * width);
        }

        for (int i = 0; i < width * height; i++) {
            // 강의자료에 나와있는 식을 구현한 코드입니다.
            // round 함수는 반올림을 해주는 함수입니다.
            dst[3 * i + c] = round(255 * cdf[scr[3 * i + c]]);
        }
    }
    
}
void GetPSNR(Mat& scr, Mat& comp) {

    int height = scr.rows;
    int width = scr.cols;
    char a[3] = { 'B', 'G', 'R'};

    for (int c = 0; c < scr.channels(); c++) {
        float MSE = 0;
        for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
            MSE += pow(scr.data[scr.channels()*(h*width+w)+c] - comp.data[scr.channels() * (h * width + w) + c], 2);
        }
        MSE /= height * width;
        std::cout<< a[c]<< " : " << 10 * log(pow(255, 2) / MSE) << std::endl;
    }

}
void Equalization_I(unsigned char* scr, int height, int width) {

    // 각 픽셀 값의 해당하는 픽셀 수를 저장할 배열(Histogram)
    int p[256] = { 0 };
    for (int i = 0; i < height * width; i++) {
        // 각 픽셀 값의 해당하는 픽셀 수를 저장하는 로직
        p[scr[3*i]]++;
    }

    // 입력 영상의 cdf을 저장할 배열
    double cdf[256] = { 0 };

    int nested = 0;
    for (int i = 0; i < 256; i++) {
        // 픽셀 갯수를 중첩하게 더해주며, 그 값에 전체 픽셀 수를 나눈 값을 cdf배열에 저장
        nested += p[i];
        cdf[i] = (double)(nested) / (height * width);
    }

    for (int i = 0; i < width * height; i++) {
        // 강의자료에 나와있는 식을 구현한 코드입니다.
        // round 함수는 반올림을 해주는 함수입니다.
        scr[3*i] = round(255 * cdf[scr[3*i]]);
    }
}