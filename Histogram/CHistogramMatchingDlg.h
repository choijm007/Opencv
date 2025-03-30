#pragma once
#include "afxdialogex.h"


// CHistogramMatchingDlg 대화 상자

class CHistogramMatchingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistogramMatchingDlg)

public:
	CHistogramMatchingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHistogramMatchingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTOGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Pixel;
	CEdit m_Percent;
	afx_msg void OnBnClickedOk();

	double Getpercent() { return percent; }
	double Getpixel() { return pixel; }

private:
	double percent;
	double pixel;
};
