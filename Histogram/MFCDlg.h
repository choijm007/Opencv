
// MFCDlg.h: 헤더 파일
//

#pragma once
#include <opencv2/opencv.hpp>
#include "CImgScalingDlg.h"
#include "CHistogramMatchingDlg.h"

#define PI 3.141592
#define   CLAMP(value) ((value) < (0) ? (0) : ((value) > (255) ? (255) : (value)))
using namespace cv;

// CMFCDlg 대화 상자
class CMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileFileopen();
	

private:
	Mat InpImg, OutImg, TempImg;
	Mat GrayImg;

	

	bool isImageOpened;
	
	CImgScalingDlg ImgScalingDlg;
	CHistogramMatchingDlg  HistogramMatchingDlg;
	

public:
	afx_msg void OnEditScale();
	void DisplayImage(Mat Display);
	afx_msg void OnShowInputimage();
	afx_msg void OnShowOutputimage();
	afx_msg void OnEditRotate();
	afx_msg void OnHistogramOutput();
	afx_msg void OnHistogramInput();
	afx_msg void OnHistogramequalizationEqualization();
	afx_msg void OnHistogramMatching();
	afx_msg void OnHistogramGray();
};
unsigned char Bilinearinterpolation(const unsigned char* scr, int width, int height, float x, float y);
unsigned char Bicubicinterpolation(const unsigned char* scr, int width, int height, float x, float y, Mat M);
int clamp(double v);
bool isInsideBoundary(int nh, int nw, double h, double w);
void Rotate_Pic(unsigned char* scr, unsigned char* dst, int height, int width, int rad);
double cubicInterpolation(double p1, double p2, double p3, double p4, double x, Mat M);
void HistogramMatching(const unsigned char* scr, unsigned char* dst, int width, int height, int* f, int total);
void ShowHistogram(int* p, int total);
