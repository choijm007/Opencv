
// MFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDlg 대화 상자



CMFCDlg::CMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_FILEOPEN, &CMFCDlg::OnFileFileopen)
	ON_COMMAND(ID_EDIT_SCALE, &CMFCDlg::OnEditScale)
	ON_COMMAND(ID_SHOW_INPUTIMAGE, &CMFCDlg::OnShowInputimage)
	ON_COMMAND(ID_SHOW_OUTPUTIMAGE, &CMFCDlg::OnShowOutputimage)
	ON_COMMAND(ID_EDIT_ROTATE, &CMFCDlg::OnEditRotate)
	ON_COMMAND(ID_HISTOGRAM_OUTPUT, &CMFCDlg::OnHistogramOutput)
	ON_COMMAND(ID_HISTOGRAM_INPUTT, &CMFCDlg::OnHistogramInput)
	ON_COMMAND(ID_HISTOGRAMEQUALIZATION_EQUALIZATION, &CMFCDlg::OnHistogramequalizationEqualization)
	ON_COMMAND(ID_HISTOGRAM_MATCHING, &CMFCDlg::OnHistogramMatching)
	ON_COMMAND(ID_HISTOGRAM_GRAY, &CMFCDlg::OnHistogramGray)
END_MESSAGE_MAP()


// CMFCDlg 메시지 처리기

BOOL CMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDlg::OnFileFileopen()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "jpg" && dlg.GetFileExt() != "JPG") {
			MessageBox(_T("JPG 파일이 아닙니다."));
			return;
		}
		isImageOpened = true;

		CString filePath = dlg.GetPathName();
		CStringA asciiPath(filePath);  // CString을 ASCII 문자열로 변환

		InpImg = imread(std::string(asciiPath));  // imread에 std::string을 전달

		if (InpImg.channels() != 1) {
			cvtColor(InpImg, GrayImg, cv::COLOR_BGR2GRAY);
		}
		else {
			GrayImg = InpImg.clone();
		}

		//Mat scr;
		//cvtColor(InpImg, scr, cv::COLOR_BGR2GRAY);
		//DisplayImage(scr);
		imshow("입력영상", InpImg);
		waitKey(0);
	}
}


unsigned char Bicubicinterpolation(const unsigned char* scr, int width, int height, float x, float y, Mat M) {

	// x,y 좌표를 기준으로 인접해있는 총 16개의 좌표를 위해 정의
	int x1 = int(x)-1;
	int y1 = int(y)-1;

	int x2 = x1+1;
	int y2 = y1+1;

	int x3 = x1 + 2;
	int y3 = y1 + 2;
	
	int x4 = x1 + 3;
	int y4 = y1 + 3;

	// 각 좌표가 범위 안에 있는지 확인
	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	//if (x2 >= width) x2 = width - 1;
	//if (y2 >= height) y2 = height - 1;
	if (x3 >= width) x3 = width - 1;
	if (y3 >= height) y3 = height - 1;
	if (x4 >= width) x4 = width - 1;
	if (y4 >= height) y4 = height - 1;
	
	// 첫 번째 행에 대한 cubic interpolation
	double p1 = (cubicInterpolation((double)scr[width * y1 + x1], (double)scr[width * y1 + x2], 
		(double)scr[width * y1 + x3], (double)scr[width * y1 + x4], x-x1 -1, M));

	// 두 번째 행에 대한 cubic interpolation
	double p2 = (cubicInterpolation((double)scr[width * (y2) + x1], (double)scr[width * (y2) + x2],
		(double)scr[width * (y2) + x3], (double)scr[width * (y2) + x4], x - x1 -1, M));

	// 세 번째 행에 대한 cubic interpolation
	double p3 = (cubicInterpolation((double)scr[width * (y3) + x1], (double)scr[width * (y3) + x2],
		(double)scr[width * (y3) + x3], (double)scr[width * (y3) + x4], x - x1 -1, M));

	// 네 번째 행에 대한 cubic interpolation
	double p4 = (cubicInterpolation((double)scr[width * (y4) + x1], (double)scr[width * (y4) + x2],
		(double)scr[width * (y4) + x3], (double)scr[width * (y4) + x4], x - x1 -1, M));

	
	// 첫번째 부터 네번째 행에 대한 cubic interpolation값을 이번엔 열을 기준으로 cubic interpolation 한 결과
	double result = cubicInterpolation(p1, p2, p3, p4, y - y1-1,M);
	return clamp(result);
}

double cubicInterpolation(double p1, double p2, double p3, double p4, double x, Mat M) {


	// 각 픽셀값을 행렬로 정의
	Mat P = (Mat_<double>(4, 1) << p1, p2, p3, p4);

	// 앞서 구한 역행렬을 P행렬과 곱셈연산
	Mat C = M * P;

	// 행렬에서 계수를 추출(a,b,c,d)
	double a = C.at<double>(0, 0);
	double b = C.at<double>(1, 0);
	double c = C.at<double>(2, 0);
	double d = C.at<double>(3, 0);

	// 3차 다항식 계산
	return a * pow(x, 3) + b * pow(x, 2) + c * x + d;

	// 위 코드는 생각보다 오래 걸려서
	// 인터넷 검색해보니 이런 방식으로도 사용할 수 있다고 나와있었습니다.
	// 
	//double a = -0.5 * p1 + 1.5 * p2 - 1.5 * p3 + 0.5 * p4;
	//double b = p1 - 2.5 * p2 + 2 * p3 - 0.5 * p4;
	//double c = -0.5 * p1 + 0.5 * p3;
	//double d = p2;

	//return a * pow(x, 3) + b * pow(x, 2) + c * x + d;

}

bool isInsideBoundary(int nh, int nw, double h, double w) {
	if (h >= 0 && h < nh && w >= 0 && w < nw)
		return true;
	return false;
}

void CMFCDlg::OnEditScale()
{
	if (isImageOpened && ImgScalingDlg.DoModal() == IDOK) {

		// Scaling SIze를 가져오는 Dialog에서 Rate을 가져오는 코드
		double dScaleRate = ImgScalingDlg.GetScaleRate();

		// 이를 통해 커진 영상의 크기 계산
		int nHeight_Scale = InpImg.rows * dScaleRate;
		int nWidth_Scale = InpImg.cols * dScaleRate;

		// 흑백 영상으로 전환
		Mat scr;
		cvtColor(InpImg, scr, cv::COLOR_BGR2GRAY);

		// 각각 Bicubic와 Bilinear interpolation을 한 결과를 저장할 Mat 객체 생성
		Mat Bicubic = Mat::zeros(nHeight_Scale, nWidth_Scale, CV_8UC1);
		Mat Bilinear = Mat::zeros(nHeight_Scale, nWidth_Scale, CV_8UC1);

		// ratio 계산
		float x, y;
		y = (float)scr.rows / nHeight_Scale;
		x = (float)scr.cols / nWidth_Scale;

		// 강의 자료에 나와있는 행렬 생성 및 역행열 계산
		Mat inv_M = (Mat_<double>(4, 4) << -1, 1, -1, 1,
			0, 0, 0, 1,
			1, 1, 1, 1,
			2, 4, 8, 1);
		inv_M = inv_M.inv();

		for (int j = 0; j < nHeight_Scale; j++) for (int i = 0; i < nWidth_Scale; i++) {
			// 범위 안에 새로운 좌표가 있으면 interpolation 실행
			// 각 좌표(i,j)에서 ratio(x,y)를 곱한것이 새로운 좌표
			if (isInsideBoundary(scr.rows, scr.cols, j * y, i * x)) {
				// interpolation 함수 실행
				Bicubic.data[nWidth_Scale * j + i] = Bicubicinterpolation(scr.data, scr.cols, scr.rows, (double)i * x, (double)j * y, inv_M);
				Bilinear.data[nWidth_Scale * j + i] = Bilinearinterpolation(scr.data, scr.cols, scr.rows, i * x, j * y);
			}
				

		}
		imshow("Bilinear", Bilinear);
		imshow("Bicubic", Bicubic);

		// opencv에서 제공하는 Bicubic interpolation을 실행
		Mat cv_bicubic;
		resize(scr, cv_bicubic, Size(nWidth_Scale, nHeight_Scale), 0, 0, INTER_CUBIC);

		imshow("opencv Bicubic", cv_bicubic);
		//DisplayImage(rs);
		waitKey(0);
	}
}

unsigned char Bilinearinterpolation(const unsigned char* scr, int width, int height, float x, float y) {

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



void Rotate_Pic(unsigned char* scr, unsigned char* dst, int height, int width, int rad) {
	int mid_x = width / 2;
	int mid_y = height / 2;

	float c = cos(-rad * (PI / 180.0));
	float s = sin(-rad * (PI / 180.0));

	float x, y;
	float new_x, new_y;
	for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
		x = i - mid_x;
		y = j - mid_y;

		new_x = c * x - s * y + mid_x;
		new_y = s * x + c * y + mid_y;
		if(isInsideBoundary(height, width, new_y, new_x))
			dst[width * j + i] = Bilinearinterpolation(scr, width, height, new_x, new_y);

	}

}

void CMFCDlg::DisplayImage(Mat Display) {
	OutImg = Display.clone();
	imshow("결과 영상", OutImg);
}

int clamp(double v) {
	if (v < 0)
		return 0;
	if (v > 255)
		return 255;
	return int(v);
}

void CMFCDlg::OnShowInputimage()
{
	imshow("Input", InpImg);
	waitKey(0);
}


void CMFCDlg::OnShowOutputimage()
{
	imshow("Output", OutImg);
	waitKey(0);
}


void CMFCDlg::OnEditRotate()
{
	Mat scr;
	cvtColor(InpImg, scr, COLOR_BGR2GRAY);
	Mat rs = Mat::zeros(InpImg.rows, InpImg.cols, CV_8UC1);
	Rotate_Pic(scr.data, rs.data, InpImg.rows, InpImg.cols, 30);
	DisplayImage(rs);
}


void CMFCDlg::OnHistogramOutput()
{
	int height = OutImg.rows;
	int width = OutImg.cols;


	if (OutImg.channels() == 1) {
		int p[256] = { 0 };
		for (int i = 0; i < height * width; i++) {
			p[OutImg.data[i]]++;
		}

		double P[256] = { 0 };

		double max_value = 0;

		for (int i = 0; i < 256; i++) {
			P[i] = (double)p[i] / (height * width);
			max_value = max(max_value, P[i]);
		}
		int w= 200;
		
		Mat his = Mat::zeros(w, 256, CV_8UC1);

		float ratio = w/max_value;

		for (int i = 0; i < 256; i++) {
			line(his, Point(i, 0), Point(i, w - P[i]*ratio), Scalar(255, 255, 255));
		}
		imshow("Output Gray", his);

	}
	else {
		int R[256] = { 0 };
		int G[256] = { 0 };
		int B[256] = { 0 };

		for (int i = 0; i < height * width; i += 3) {
			B[OutImg.data[i]]++;
			G[OutImg.data[i + 1]]++;
			R[OutImg.data[i + 2]]++;
		}

		double Rp[256] = { 0 };
		double Gp[256] = { 0 };
		double Bp[256] = { 0 };

		double max_R = 0;
		double max_G = 0;
		double max_B = 0;

		for (int i = 0; i < 256; i++) {
			Rp[i] = (double)R[i] / (height * width);
			Gp[i] = (double)G[i] / (height * width);
			Bp[i] = (double)B[i] / (height * width);
			max_R = max(max_R, Rp[i]);
			max_G = max(max_G, Gp[i]);
			max_B = max(max_B, Bp[i]);
		}
		int w= 200;

		Mat hisR = Mat::zeros(w, 256, CV_8UC1);
		Mat hisG = Mat::zeros(w, 256, CV_8UC1);
		Mat hisB = Mat::zeros(w, 256, CV_8UC1);

		Mat his = Mat::zeros(w, 256, CV_8UC1);

		for (int i = 0; i < 256; i++) {
			line(hisR, Point(i, 0), Point(i, w - Rp[i] * (w/max_R)), Scalar(255, 255, 255));
			line(hisG, Point(i, 0), Point(i, w - Gp[i] * (w / max_G)), Scalar(255, 255, 255));
			line(hisB, Point(i, 0), Point(i, w - Bp[i] * (w / max_B)), Scalar(255, 255, 255));
		}

		imshow("Output Red", hisR);
		imshow("Output Green", hisG);
		imshow("Output Blue", hisB);
	}
}


void CMFCDlg::OnHistogramInput()
{
	int height = InpImg.rows;
	int width = InpImg.cols;

	// channel() 함수를 통해 영상이 흑백(channel = 1)인지 컬러(channel =3)인지 판단합니다.
	if (InpImg.channels() == 1) {

		// Histogram 을 저장할 p 배열 생성
		int p[256] = { 0 };
		for (int i = 0; i < height * width; i++) {
			// 각 픽셀 값의 갯수 측정
			p[InpImg.data[i]]++;
		}

		// pdf을 저장할 P 배열과 가장 큰 확률을 찾기 위한 max_value
		double P[256] = { 0 };
		double max_value = 0;

		// pdf 계산
		for (int i = 0; i < 256; i++) {
			P[i] = (double)p[i] / (height * width);
			max_value = max(max_value, P[i]);
		}
		// 높이
		int w = 200;

		// Histogram을 저장할 Mat객체
		Mat his = Mat::zeros(w, 256, CV_8UC1);

		// 비율 계산
		float ratio = w / max_value;

		// 각 픽셀값마다 픽셀의 갯수를 line 형식으로 그리기
		for (int i = 0; i < 256; i++) {
			line(his, Point(i, 0), Point(i, w - P[i] * ratio), Scalar(255, 255, 255));
		}
		imshow("Input Gray", his);

	}
	else {
		// 컬러 영상일때

		// R,G,B의 픽셀값의 픽셀수를 저장할 배열 정의
		int R[256] = { 0 };
		int G[256] = { 0 };
		int B[256] = { 0 };

		for (int i = 0; i < height * width; i += 3) {
			// 각 픽셀 값의 갯수 측정
			B[InpImg.data[i]]++;
			G[InpImg.data[i + 1]]++;
			R[InpImg.data[i + 2]]++;
		}

		// pdf 을 위한 배열 및 가장 큰 확률을 저장할 변수 정의
		double Rp[256] = { 0 };
		double Gp[256] = { 0 };
		double Bp[256] = { 0 };
		double max_R = 0;
		double max_G = 0;
		double max_B = 0;

		// R,G,B 각각의 pdf 계산
		for (int i = 0; i < 256; i++) {
			Rp[i] = (double)R[i] / (height * width);
			Gp[i] = (double)G[i] / (height * width);
			Bp[i] = (double)B[i] / (height * width);
			max_R = max(max_R, Rp[i]);
			max_G = max(max_G, Gp[i]);
			max_B = max(max_B, Bp[i]);
		}

		// 높이
		int w = 200;

		// Histogram을 저장할 Mat 객체를 R,G,B 각각 생성
		Mat hisR = Mat::zeros(w, 256, CV_8UC1);
		Mat hisG = Mat::zeros(w, 256, CV_8UC1);
		Mat hisB = Mat::zeros(w, 256, CV_8UC1);


		for (int i = 0; i < 256; i++) {
			// 각 픽셀 값마다 픽셀의 갯수를 line 형식으로 그리기
			line(hisR, Point(i, 0), Point(i, w - Rp[i] * (w / max_R)), Scalar(255, 255, 255));
			line(hisG, Point(i, 0), Point(i, w - Gp[i] * (w / max_G)), Scalar(255, 255, 255));
			line(hisB, Point(i, 0), Point(i, w - Bp[i] * (w / max_B)), Scalar(255, 255, 255));
		}

		imshow("Input Red", hisR);
		imshow("Input Green", hisG);
		imshow("Input Blue", hisB);
	}
}


void CMFCDlg::OnHistogramequalizationEqualization()
{
	TempImg = InpImg.clone();
	cvtColor(InpImg, TempImg, cv::COLOR_BGR2GRAY);


	int height = TempImg.rows;
	int width = TempImg.cols;

	int p[256] = { 0 };
	for (int i = 0; i < height * width; i++) {
		p[TempImg.data[i]]++;
	}

	double cdf[256] = { 0 };

	int nested = 0;

	for (int i = 0; i < 256; i++) {
		nested += p[i];
		cdf[i] = (double)(nested) / (height * width);
	}

	Mat res = TempImg.clone();

	for (int i = 0; i < width * height; i++) {
		res.data[i] = round(255 * cdf[TempImg.data[i]]);
	}

	DisplayImage(res);
}


void CMFCDlg::OnHistogramMatching()
{
	// Dialg 열기
	if (isImageOpened && HistogramMatchingDlg.DoModal() == IDOK) {
		// Dialog에서 어떤 pixel값을 몇개로 설정할건지 받아오기
		double x = HistogramMatchingDlg.Getpixel();
		double y = HistogramMatchingDlg.Getpercent();
		
		
		// 결과를 담을 result Mat 인스턴스
		Mat result = GrayImg.clone();
		// Specified Histogram을 저장할 배열
		int f[256] = { 0 };
		// Specified Histogram 의 전체 픽셀수를 저장할 변수
		int total = 0;

		// Piesewise-linear로 2개의 Linear line으로 구성하는 Specified Histogram
		for (int i = 0; i < 256; i++) {
			if (i <= x && x!=0) {
				//  x 을 기준으로 왼쪽에는 기울기가 (y/x)인 함수를 대입
				f[i] = (y / x) * i;
				
			}
			else {
				// 오른쪽에는 이 함수를 통해 대입
				f[i] = ((255 - y) / (255 - x))* (i - x) + y;
				
			}
			// 전체 픽셀수를 저장
			total += f[i];
		}
		HistogramMatching(GrayImg.data, result.data, GrayImg.cols, GrayImg.rows, f, total);
		DisplayImage(result);
	}
}


void HistogramMatching(const unsigned char* scr, unsigned char* dst, int width ,int height, int *f, int total)
{
	// Histogram을 저장할 배열
	int p[256] = { 0 };
	for (int i = 0; i < height * width; i++) {
		p[scr[i]]++;
	}
	// 입력 영상의 cdf을 저장할 배열
	double cdf[256] = { 0 };

	int nested = 0;

	// cdf 계산
	for (int i = 0; i < 256; i++) {
		nested += p[i];
		cdf[i] = (double)(nested) / (height * width);
	}

	// Specified Histogram의 cdf을 저장할 배열
	double fcdf[256] = { 0 };
	nested = 0;
	for (int i = 0; i < 256; i++) {
		nested += f[i];
		fcdf[i] = (double)nested / (total);
	}

	// Transformation 함수를 배열로 구현
	unsigned char T[256] = { 0 };
	double gap;
	double r;
	int j;
	for (int i = 0; i < 256; i++) {
		// 각 픽셀값을 돌며 cdf[i] 와 fcdf[j]간의 차이가 가장 작아지는 것을 구한다.
		gap = 1;
		r = cdf[i];
		j = 0;

		// 처음 구현할때는 이런식으로 무조건 256*256번을 탐색하는 과정을 했지만
		// 너무 비효율적인 것같아서 아래와 같이 변경함.
		//for (int j = 0; j < 256; j++) {
		//	if (fabs(r - fcdf[j]) < gap) {
		//		gap = fabs(r - fcdf[j]);
		//		T[i] = (unsigned char)j;
		//	}
		//}


		while (j < 255 && fcdf[j] < r) {
			// cdf은 작은 값에서부터 큰 값으로 구성되어있기 때문에 이진 탐색을 이용가능
			// 따라서 입력영상의 픽셀 값 i의 cdf와 Specified Histogram의 cdf을 비교하여 그 차이가 가장 작은 j를 구하는 로직이다.
			// j를 1씩 키우면서 둘의 간격은 점점 좁아지다 fcdf[j]값이 더 커지는 순간 반복문을 탈출
			j++;
		}
		// 반복문을 빠져나왔더라도
		// 아직 fcdf[j-1] 와 r사이의 간격과 fcdf[j] 와 r 사이의 간격 중 어떤게 더 작은지 모르니, 그것을 판단하기 위한 조건문
		if (fabs(fcdf[j - 1] - r) < fabs(fcdf[j] - r)) {
			T[i] = (unsigned char)(j - 1);
		}
		else {
			T[i] = (unsigned char)j;
		}
	}

	// Transformation 함수 인 T배열을 이용하여 모든 픽셀 값을 변경.
	for (int i = 0; i < width * height; i++) {
		dst[i] = T[scr[i]];
	}
	ShowHistogram(f, total);

	return;
}

void ShowHistogram(int* p, int total) {
	double P[256] = { 0 };

	double max_value = 0;

	for (int i = 0; i < 256; i++) {
		P[i] = (double)p[i] / total;
		max_value = max(max_value, P[i]);
	}
	int w = 200;

	Mat his = Mat::zeros(w, 256, CV_8UC1);

	float ratio = w / max_value;

	for (int i = 0; i < 256; i++) {
		line(his, Point(i, 0), Point(i, w - P[i] * ratio), Scalar(255, 255, 255));
	}
	imshow("Histogram", his);
	return;
}

void CMFCDlg::OnHistogramGray()
{
	int height = GrayImg.rows;
	int width = GrayImg.cols;

	int p[256] = { 0 };
	for (int i = 0; i < height * width; i++) {
		p[GrayImg.data[i]]++;
	}

	double P[256] = { 0 };

	double max_value = 0;

	for (int i = 0; i < 256; i++) {
		P[i] = (double)p[i] / (height * width);
		max_value = max(max_value, P[i]);
	}
	int w = 200;

	Mat his = Mat::zeros(w, 256, CV_8UC1);

	float ratio = w / max_value;

	for (int i = 0; i < 256; i++) {
		line(his, Point(i, 0), Point(i, w - P[i] * ratio), Scalar(255, 255, 255));
	}
	imshow("Input Gray", his);
}
