// CImgScalingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFC.h"
#include "afxdialogex.h"
#include "CImgScalingDlg.h"


// CImgScalingDlg 대화 상자

IMPLEMENT_DYNAMIC(CImgScalingDlg, CDialogEx)

CImgScalingDlg::CImgScalingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCALE, pParent)
{

}

CImgScalingDlg::~CImgScalingDlg()
{
}

void CImgScalingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCALE, m_EditScaleRate);
}


BEGIN_MESSAGE_MAP(CImgScalingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CImgScalingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CImgScalingDlg 메시지 처리기



void CImgScalingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cstrTemp;

	m_EditScaleRate.GetWindowTextW(cstrTemp);
	dScaleRate = _wtof(cstrTemp);

	CDialogEx::OnOK();
}

double CImgScalingDlg::GetScaleRate() { return dScaleRate; }
