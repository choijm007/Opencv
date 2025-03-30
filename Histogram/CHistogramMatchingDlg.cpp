// CHistogramMatchingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFC.h"
#include "afxdialogex.h"
#include "CHistogramMatchingDlg.h"


// CHistogramMatchingDlg 대화 상자

IMPLEMENT_DYNAMIC(CHistogramMatchingDlg, CDialogEx)

CHistogramMatchingDlg::CHistogramMatchingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HISTOGRAM, pParent)
{

}

CHistogramMatchingDlg::~CHistogramMatchingDlg()
{
}

void CHistogramMatchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PIXEL, m_Pixel);
	DDX_Control(pDX, IDC_EDIT_PERCENT, m_Percent);
}


BEGIN_MESSAGE_MAP(CHistogramMatchingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHistogramMatchingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHistogramMatchingDlg 메시지 처리기


void CHistogramMatchingDlg::OnBnClickedOk()
{
	CString cstrTemp;

	m_Pixel.GetWindowTextW(cstrTemp);
	pixel = _wtof(cstrTemp);

	m_Percent.GetWindowTextW(cstrTemp);
	percent = _wtof(cstrTemp);

	CDialogEx::OnOK();
}
