#pragma once
#include "afxdialogex.h"


// CImgScalingDlg 대화 상자

class CImgScalingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImgScalingDlg)

public:
	CImgScalingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CImgScalingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCALE };
#endif

private:
	CEdit m_EditScaleRate;

	double dScaleRate;
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double GetScaleRate();

	afx_msg void OnBnClickedOk();
};
