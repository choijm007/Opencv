#include <iostream>
#include <opencv2/opencv.hpp>

#define PI 3.14159265359

using namespace cv;
void Filtering(Mat& scr, Mat& dst, Mat& filter, int v);
Mat Padding(Mat& scr, int width, int height, int FilterSize);
void AverageFilter(Mat& scr, Mat& dst, int v);
unsigned char clamp(double v);
void GuassianFilter(Mat& scr, Mat& dst, int n, int sigma);
float Guassian(int h, int w, int sigma);
void GaussianNoise(Mat& scr, Mat& dst, float Mean, float stdev);
float GetNoise(float* PDF, int Length);
void SaltPepperNoise(Mat& scr, Mat& dst, float SP, float PP);
void GeometricMeanFilter(Mat& scr, Mat& dst, int n);
void MedianFilter(Mat& scr, Mat& dst, int n);
void AdaptiveMedianFilter(Mat& scr, Mat& dst, int maxWindowSize);
float GetPSNR(Mat& scr, Mat& comp);

int main()
{
    Mat scr = imread("lena.jpg");
    Mat scr_gray = imread("lena.jpg", IMREAD_GRAYSCALE);
    Mat Noise_Gau;
    Mat Noise_SP;
    /////////////// 문제 2 //////////////

    //Mat tmp_3 = scr.clone();
    //Mat tmp_5 = scr.clone();
    //Mat tmp_11 = scr.clone();
    //Mat tmp_25 = scr.clone();

    //AverageFilter(scr, tmp_3, 1);
    //AverageFilter(scr, tmp_5, 2);
    //AverageFilter(scr, tmp_11, 5);
    //AverageFilter(scr, tmp_25, 12);

    //imshow("3x3", tmp_3);
    //imshow("5x5", tmp_5);
    //imshow("11x11", tmp_11);
    //imshow("25x25", tmp_25);

    /////////////// 문제 3 //////////////

    //Mat temp, temp1;
    //GaussianBlur(scr, temp, Size(3, 3), 0.1, 0.1);
    //GaussianBlur(scr, temp1, Size(7,7), 5, 5);
    //imshow("3x3", temp);
    //imshow("7x7", temp1);



    /////////////// 문제 4 //////////////
    
    //Noise_Gau = scr_gray.clone();
    //Noise_SP = scr_gray.clone();
    //float mean, dev;
    //float SP, FP;

    //std::cout << "평균, 표준편차 : ";
    //std::cin >> mean >> dev;
    //std::cout << std::endl;
    //std::cout << "Salt 확률, Pepper 확률 : ";
    //std::cin >> SP >> FP;
    //GaussianNoise(scr_gray, Noise_Gau, mean, dev);
    //SaltPepperNoise(scr_gray, Noise_SP, SP, FP);

    //imshow("GaussianNoise", Noise_Gau);
    //imshow("SaltPepperNoise", Noise_SP);
    //imshow("gray", scr_gray);

    /////////////// 문제 5, 6, 7 //////////////

    
    //Noise_Gau = scr_gray.clone();
    //Noise_SP = scr_gray.clone();

    //Mat Geometric = scr_gray.clone();
    //Mat Median = scr_gray.clone();
    //Mat Adaptive = scr_gray.clone();

    //GaussianNoise(scr_gray, Noise_Gau, 0, 5);
    //SaltPepperNoise(scr_gray, Noise_SP, 0.1, 0.1);

    //GeometricMeanFilter(Noise_Gau, Geometric,3);
    //MedianFilter(Noise_Gau, Median,3);
    //AdaptiveMedianFilter(Noise_Gau, Adaptive, 11);

    //imshow("Adaptive Median Filter", Adaptive);
    //imshow("Median Filter", Median);
    //imshow("gray_scr", scr_gray);
    //imshow("Noise Gray", Noise_Gau); 

    //imshow("SaltPepper", Noise_SP);
    //imshow("Geometric Mean filter", Geometric);

    /////////////// 문제 8, 9 //////////////
    // 
    // 
    /////////////// Gaussian Noise //////////////

    //Mat Noise_Gau1 = scr_gray.clone();
    //Mat Noise_Gau2 = scr_gray.clone();
    //Mat Noise_Gau3 = scr_gray.clone();

    //GaussianNoise(scr_gray, Noise_Gau1,0,5);
    //GaussianNoise(scr_gray, Noise_Gau2, 0, 10);
    //GaussianNoise(scr_gray, Noise_Gau3, 0, 30);

    //Mat rst3x3_5 = scr_gray.clone();
    //Mat rst3x3_10 = scr_gray.clone();
    //Mat rst3x3_30 = scr_gray.clone();
    //Mat rst5x5_5 = scr_gray.clone();
    //Mat rst5x5_10 = scr_gray.clone();
    //Mat rst5x5_30 = scr_gray.clone();

    //GeometricMeanFilter(Noise_Gau1, rst3x3_5, 3);
    //GeometricMeanFilter(Noise_Gau2, rst3x3_10, 3);
    //GeometricMeanFilter(Noise_Gau3, rst3x3_30, 3);
    //GeometricMeanFilter(Noise_Gau1, rst5x5_5, 5);
    //GeometricMeanFilter(Noise_Gau2, rst5x5_10, 5);
    //GeometricMeanFilter(Noise_Gau3, rst5x5_30, 5);
    //
    //imshow("rst3x3_5", rst3x3_5); 
    //imshow("rst3x3_10", rst3x3_10); 
    //imshow("rst3x3_30", rst3x3_30); 
    //imshow("rst5x5_5", rst5x5_5); 
    //imshow("rst5x5_10", rst5x5_10); 
    //imshow("rst5x5_30", rst5x5_30); 

    //std::cout << "3x3 (0,5) : " << GetPSNR(scr_gray, rst3x3_5) << std::endl;
    //std::cout << "3x3 (0,10) : " << GetPSNR(scr_gray, rst3x3_10) << std::endl;
    //std::cout << "3x3 (0,30) : " << GetPSNR(scr_gray, rst3x3_30) << std::endl;
    //std::cout << "5x5 (0,5) : " << GetPSNR(scr_gray, rst5x5_5) << std::endl;
    //std::cout << "5x5 (0,10) : " << GetPSNR(scr_gray, rst5x5_10) << std::endl;
    //std::cout << "5x5 (0,30) : " << GetPSNR(scr_gray, rst5x5_30) << std::endl;

    /////////////// Salt Pepper //////////////

    Mat Noise_SP1 = scr_gray.clone();
    Mat Noise_SP2 = scr_gray.clone();
    Mat Noise_SP3 = scr_gray.clone();

    SaltPepperNoise(scr_gray, Noise_SP1, 0.05, 0.05);
    SaltPepperNoise(scr_gray, Noise_SP2, 0.1, 0.1);
    SaltPepperNoise(scr_gray, Noise_SP3, 0.25, 0.25);

    Mat median_5 = scr_gray.clone();
    Mat median_10 = scr_gray.clone();
    Mat median_25 = scr_gray.clone();
    Mat adaptive_5 = scr_gray.clone();
    Mat adaptive_10 = scr_gray.clone();
    Mat adaptive_25 = scr_gray.clone();

    MedianFilter(Noise_SP1, median_5, 3);
    MedianFilter(Noise_SP2, median_10, 3);
    MedianFilter(Noise_SP3, median_25, 3);
    AdaptiveMedianFilter(Noise_SP1, adaptive_5, 7);
    AdaptiveMedianFilter(Noise_SP2, adaptive_10, 7);
    AdaptiveMedianFilter(Noise_SP3, adaptive_25, 7);

    imshow("median_5", median_5);
    imshow("median_10", median_10);
    imshow("median_25", median_25);
    imshow("adaptive_5", adaptive_5);
    imshow("adaptive_10", adaptive_10);
    imshow("adaptive_25", adaptive_25);

    std::cout << "median 5 : " << GetPSNR(scr_gray, median_5) << std::endl;
    std::cout << "median 10 : " << GetPSNR(scr_gray, median_10) << std::endl;
    std::cout << "median 25 : " << GetPSNR(scr_gray, median_25) << std::endl;
    std::cout << "adaptive 5 : " << GetPSNR(scr_gray, adaptive_5) << std::endl;
    std::cout << "adaptive 10 : " << GetPSNR(scr_gray, adaptive_10) << std::endl;
    std::cout << "adaptive 25 : " << GetPSNR(scr_gray, adaptive_25) << std::endl;


    imshow("scr", scr);

    waitKey(0);
    return 0;
}

void Filtering(Mat& scr, Mat& dst, Mat& filter, int v) {
    int height = scr.rows;
    int width = scr.cols;
    int channel = scr.channels();
    int n = 2 * v + 1;

    Mat pad = Padding(scr, width, height, n);
    int PadSize = (int)(n / 2);
    int pheight = pad.rows;
    int pwidth = pad.cols;

    int x = 0;
    double conv = 0;
    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        for (int c = 0; c < channel; c++) {
            //  채널의 갯수만큼 반복을 해주면서 각 채널별로 컴볼루션을 진행
            conv = 0;
            for (int j = 0; j < n; j++) {
                x = (h + j) * pwidth + w;
                for (int i = 0; i < n; i++) {
                    // 컨볼루션 계산
                    conv += pad.data[channel*(x + i)+c] * filter.at<float>(j, i);
                }
            }
            // 값을 넣어주기
            dst.data[channel*(h * width + w)+c] = clamp(conv);
        }
    }
}

void AverageFilter(Mat& scr, Mat& dst, int v) {
    int n = 2 * v + 1;

    Mat filter = Mat::ones(n, n, CV_32F) / (float)(n * n);
    Filtering(scr, dst, filter, v);
    return;
}

void GuassianFilter(Mat& scr, Mat& dst, int n, int sigma) {

    Mat filter(n, n, CV_32F);
    int PadSize = n / 2;


    for (int h = -1*PadSize; h <= PadSize; h++) for (int w = -1*PadSize; w <= PadSize; w++) {
        filter.at<float>(h + PadSize, w + PadSize) = Guassian(h, w, sigma);
    }

    std::cout << filter << std::endl;

    float f = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f += filter.at<float>(i, j);
        }   
    
    }
    std::cout << f << std::endl;
    Filtering(scr, dst, filter, (int)(n / 2));
    return;
}

float Guassian(int h, int w, int sigma) {
    float rst;
    rst = (1 / (float)(2 * PI * sigma * sigma)) * exp(-1 *(float)(h*h + w*w) / (2 * sigma*sigma));

    return rst;
}

Mat Padding(Mat& scr, int width, int height, int FilterSize) {
    // repetition padding
    int PadSize = (int)(FilterSize / 2);
    int nheight = height + 2 * PadSize;
    int nwidth = width + 2 * PadSize;


    if (scr.channels() == 1) {
        Mat rtn(nheight, nwidth, CV_8UC1);
        for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
            // 기존 이미지 가운데 넣기
            rtn.data[nwidth * (h + PadSize) + w + PadSize] = scr.data[h*width +w];
        }
        for (int h = 0; h < PadSize; h++) {
            for (int w = 0; w < width; w++) {
                
                // 위쪽 아래쪽 padding
                rtn.data[h * (nwidth) + w + PadSize] = scr.data[w];
                rtn.data[(h + height + PadSize) * nwidth + w + PadSize] = scr.data[(height - 1) * width + w];
            }
        }
        for (int h = 0; h < nheight; h++) {
            for (int w = 0; w < PadSize; w++) {

                // 왼쪽 오른쪽 padding
                rtn.data[h * (nwidth)+ w] = rtn.data[h*nwidth + PadSize];
                rtn.data[h * (nwidth)+ PadSize+width+w] = rtn.data[h * nwidth + PadSize+width-1];
            }
        }
        return rtn;
        
    }
    else {
        Mat rtn(height + 2 * PadSize, width + 2 * PadSize, CV_8UC3);

        for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
            // 기존 이미지 가운데 넣기
            rtn.data[3*(nwidth * (h + PadSize) + w + PadSize)] = scr.data[3*(h * width + w)];
            rtn.data[3*(nwidth * (h + PadSize) + w + PadSize)+1] = scr.data[3*(h * width + w)+1];
            rtn.data[3*(nwidth * (h + PadSize) + w + PadSize)+2] = scr.data[3*(h * width + w)+2];
        }
        for (int h = 0; h < PadSize; h++) {
            for (int w = 0; w < width; w++) {
                // 위쪽 아래쪽 padding
                rtn.data[3*(h * (nwidth)+w + PadSize)] = scr.data[3*w];
                rtn.data[3 * (h * (nwidth)+w + PadSize)+1] = scr.data[3 * w+1];
                rtn.data[3 * (h * (nwidth)+w + PadSize)+2] = scr.data[3 * w+2];

                rtn.data[3*((h + height + PadSize) * nwidth + w + PadSize)] = scr.data[3*((height - 1) * width + w)];
                rtn.data[3 * ((h + height + PadSize) * nwidth + w + PadSize)+1] = scr.data[3 * ((height - 1) * width + w)+1];
                rtn.data[3 * ((h + height + PadSize) * nwidth + w + PadSize)+2] = scr.data[3 * ((height - 1) * width + w)+2];
            }
        }
        for (int h = 0; h < nheight; h++) {
            for (int w = 0; w < PadSize; w++) {
                // 왼쪽 오른쪽 padding
                rtn.data[3*(h * (nwidth)+w)] = rtn.data[3*(h * nwidth + PadSize)];
                rtn.data[3 * (h * (nwidth)+w)+1] = rtn.data[3 * (h * nwidth + PadSize)+1];
                rtn.data[3 * (h * (nwidth)+w)+2] = rtn.data[3 * (h * nwidth + PadSize)+2];

                rtn.data[3*(h * (nwidth)+PadSize + width + w)] = rtn.data[3*(h * nwidth + PadSize + width - 1)];
                rtn.data[3 * (h * (nwidth)+PadSize + width + w)+1] = rtn.data[3 * (h * nwidth + PadSize + width - 1)+1];
                rtn.data[3 * (h * (nwidth)+PadSize + width + w)+2] = rtn.data[3 * (h * nwidth + PadSize + width - 1)+2];
            }
        }
        return rtn;

    }

}

unsigned char clamp(double v) {
    if (v > 255)return 255;
    if (v < 0)return 0;
    return (unsigned char)v;
}

void GaussianNoise(Mat& scr, Mat& dst, float Mean, float stdev) {
    float tmp = 0;
    float PDF[256] = { 0 };
    srand((int)time(0));
    int height = scr.rows;
    int width = scr.cols;


    float x;
    for (int n = 0; n < 256; n++) {
        x = (float)(n - 128);
        PDF[n] = (1 / ((float)sqrt(2 * PI) * stdev)) * exp(-pow(x - Mean, 2) / (2 * stdev * stdev));
    }


    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        tmp = (float)scr.data[h * width + w] + GetNoise(PDF, 256);
        dst.data[h * width + w] = clamp(tmp);
    }
}

float GetNoise(float* PDF, int Length) {
    int Center = Length / 2;
    float Rand, Comp, Temp = 0;
    float x = 0, fDiff;
    int n;
    float CDF[256] = { 0 };

    Rand = (float)rand() / (RAND_MAX + 1);

    for (n = 1; n < Length; n++) {
        CDF[n] = (PDF[n] + PDF[n - 1]) / 2 + CDF[n - 1];
        fDiff = Rand - CDF[n];
        if (fDiff < 0) {
            x = ((float)n - Center);
            break;
        }
    }
    Comp = (Rand - CDF[n - 1]) / (CDF[n] - CDF[n - 1]);
    return x + Comp;
}

void SaltPepperNoise(Mat& scr, Mat& dst, float SP, float PP) {
    float Low = SP;
    float High = 1 - PP;
    float Rand;
    int height = scr.rows;
    int width = scr.cols;

    srand((int)time(0));

    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        Rand = ((float)rand() / RAND_MAX);
        if (Rand < Low) {
            dst.data[h * width + w] = 255;
        }
        else if (Rand > High) {
            dst.data[h * width + w] = 0;
        }
        else {
            dst.data[h * width + w] = scr.data[h * width + w];
        }
    }
}

void GeometricMeanFilter(Mat& scr, Mat& dst,int n) {
    int height = scr.rows;
    int width = scr.cols;
    int channel = scr.channels();

    Mat pad = Padding(scr, width, height, n);
    int PadSize = (int)(n / 2);
    int pheight = pad.rows;
    int pwidth = pad.cols;

    int x = 0;
    double conv;
    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        for (int c = 0; c < channel; c++) {
            //  채널의 갯수만큼 반복을 해주면서 각 채널별로 컴볼루션을 진행
            conv = 1;
            for (int j = 0; j < n; j++) {
                x = (h + j) * pwidth + w;
                for (int i = 0; i < n; i++) {
                    // 컨볼루션 계산
                    conv *= pad.data[channel * (x + i) + c];
                }
            }
            // 값을 넣어주기
            dst.data[channel * (h * width + w) + c] = clamp(pow(conv,1.0/(n*n)));
        }
    }

    return;
}

void MedianFilter(Mat& scr, Mat& dst, int n) {
    int height = scr.rows;
    int width = scr.cols;
    int channel = scr.channels();

    Mat pad = Padding(scr, width, height, n);
    int PadSize = (int)(n / 2);
    int pheight = pad.rows;
    int pwidth = pad.cols;

    int x = 0;
    std::vector<uchar> arr;
    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        for (int c = 0; c < channel; c++) {
            //  채널의 갯수만큼 반복을 해주면서 각 채널별로 컴볼루션을 진행
            arr.clear();
            for (int j = 0; j < n; j++) {
                x = (h + j) * pwidth + w;
                for (int i = 0; i < n; i++) {
                    // 컨볼루션 계산
                    arr.push_back(pad.data[channel * (x + i) + c]);
                    
                }
            }
            // 값을 넣어주기
            std::sort(arr.begin(), arr.end());
            dst.data[channel * (h * width + w) + c] = clamp(arr[n/2]);
        }
    }

    return;
}

void AdaptiveMedianFilter(Mat& scr, Mat& dst, int maxWindowSize) {
    int n = 3;
    int height = scr.rows;
    int width = scr.cols;
    int channel = scr.channels();

    Mat pad = Padding(scr, width, height, n);
    int PadSize = (int)(n / 2);
    int pheight = pad.rows;
    int pwidth = pad.cols;

    int x = 0;
    uchar med, min, max, Z;
    std::vector<uchar> arr;
    for (int h = 0; h < height; h++) for (int w = 0; w < width; w++) {
        for (int c = 0; c < channel; c++) {
            n = 3;
            while (true) {
                arr.clear();
                for (int j = 0; j < n; j++) {
                    x = (h + j) * pwidth + w;
                    for (int i = 0; i < n; i++) {
                        // 컨볼루션 계산
                        arr.push_back(pad.data[channel * (x + i) + c]);
                    }
                }
                std::sort(arr.begin(), arr.end());
                med = arr[n / 2];
                min = arr[0];
                max = arr.back();
                Z = scr.data[channel * (h * width + w) + c];
                //LEVEL A
                if (med - min > 0 && med - max < 0) {
                    // LEVEL B
                    if (Z - min > 0 && Z - max < 0) {
                        dst.data[channel * (h * width + w) + c] = Z;
                        break;
                    }
                    else {
                        dst.data[channel * (h * width + w) + c] = med;
                        break;
                    }     
                }
                else {
                    n += 2;           
                }
                if (n < maxWindowSize) continue;
                else {
                    dst.data[channel * (h * width + w) + c] = Z;
                    break;
                }
         
            }

        }
    }

    return;
}

float GetPSNR(Mat& scr, Mat& comp) {
    int height = scr.rows;
    int width = scr.cols;

    float MSE = 0;
    for (int i = 0; i < height*width*scr.channels(); i++)  {
        MSE += pow(scr.data[i] - comp.data[i], 2);
    }
    MSE /= height * width;
    return 10 * log(pow(255, 2) / MSE);
}