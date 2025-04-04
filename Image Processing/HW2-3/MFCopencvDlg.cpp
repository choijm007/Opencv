﻿
// MFCopencvDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCopencv.h"
#include "MFCopencvDlg.h"
#include "afxdialogex.h"
#include "oc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int clamp(float v);

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


// CMFCopencvDlg 대화 상자



CMFCopencvDlg::CMFCopencvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCopencvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCopencvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_FILEOPEN, &CMFCopencvDlg::OnFileOpenBtnClick)
	ON_COMMAND(ID_CONVERTCOLOR_CONVERTGARY, &CMFCopencvDlg::OnConvertcolorConvertgary)
	ON_COMMAND(ID_CONVERTCOLOR_CONVERT, &CMFCopencvDlg::OnConvertYUVBtnClick)
END_MESSAGE_MAP()


// CMFCopencvDlg 메시지 처리기

BOOL CMFCopencvDlg::OnInitDialog()
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

void CMFCopencvDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCopencvDlg::OnPaint()
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
HCURSOR CMFCopencvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCopencvDlg::OnFileOpenBtnClick()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		if (dlg.GetFileExt() != "jpg" && dlg.GetFileExt() != "JPG") {
			MessageBox(_T("JPG 파일이 아닙니다."));
			return;
		}
		CString filePath = dlg.GetPathName();
		CStringA asciiPath(filePath);  // CString을 ASCII 문자열로 변환

		InpImg = imread(std::string(asciiPath));  // imread에 std::string을 전달
		
		imshow("InpImg", InpImg);
		waitKey(0);
	}
}


void CMFCopencvDlg::OnConvertcolorConvertgary()
{
	// 실습 3

	if (InpImg.data != NULL) {

		GrayImg = new unsigned char* [InpImg.rows];

		for (int h = 0; h < InpImg.rows; h++) {
			GrayImg[h] = new unsigned char[InpImg.cols];
		}

		for (int j = 0; j < InpImg.rows; j++)for (int i = 0; i < InpImg.cols; i++) {
			GrayImg[j][i] = int(0.114 * InpImg.data[3 * (InpImg.cols * j + i)])
				+ int(0.587 * InpImg.data[3 * (InpImg.cols * j + i) + 1])
				+ int(0.229 * InpImg.data[3 * (InpImg.cols * j + i) + 2]);
		}


		for (int n = 0; n < InpImg.rows; n++) {
			delete[] GrayImg[n];
		}
		delete[] GrayImg;
	}

}


void CMFCopencvDlg::OnConvertYUVBtnClick()
{

	// 실습 4
	if (InpImg.data != NULL) {
		GrayImg = new unsigned char* [InpImg.rows];

		U = new unsigned char* [InpImg.rows];
		V = new unsigned char* [InpImg.rows];


		for (int h = 0; h < InpImg.rows; h++) {
			GrayImg[h] = new unsigned char[InpImg.cols];
			U[h] = new unsigned char[InpImg.cols];
			V[h] = new unsigned char[InpImg.cols];
		}



		for (int j = 0; j < InpImg.rows; j++)for (int i = 0; i < InpImg.cols; i++) {

			unsigned char R = InpImg.data[3 * (InpImg.cols * j + i) + 2];  // R 값
			unsigned char G = InpImg.data[3 * (InpImg.cols * j + i) + 1];  // G 값
			unsigned char B = InpImg.data[3 * (InpImg.cols * j + i)];      // B 값

			GrayImg[j][i] = clamp(0.299 * R + 0.587 * G + 0.114 * B);

			U[j][i] = clamp(0.564 * (B - GrayImg[j][i])+128);
			V[j][i] = clamp(0.713 * (R - GrayImg[j][i])+128);
		}

		FILE* fp;
		fopen_s(&fp, "Result.yuv", "wb");

		for (int h = 0; h < InpImg.rows; h++) {
			fwrite(GrayImg[h], sizeof(unsigned char), InpImg.cols, fp);
		}
		for (int h = 0; h < InpImg.rows; h++) {
			fwrite(U[h], sizeof(unsigned char), InpImg.cols, fp);
		}
		for (int h = 0; h < InpImg.rows; h++) {
			fwrite(V[h], sizeof(unsigned char), InpImg.cols, fp);
		}

		fclose(fp);

		for (int n = 0; n < InpImg.rows; n++) {
			delete[] GrayImg[n];
			delete[] U[n];
			delete[] V[n];
		}
		delete[] GrayImg;
		delete[] U;
		delete[] V;

	}

	
}

int clamp(float v) {
	if (v < 0)
		return 0;
	if (v > 255)
		return 255;
	return int(v);
}