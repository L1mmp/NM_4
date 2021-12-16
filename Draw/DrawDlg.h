
// DrawDlg.h : ���� ���������
//

#pragma once
#include "Drawer.h"

// ���������� ���� CDrawDlg
class CDrawDlg : public CDialogEx
{
// ��������
public:
	CDrawDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	Drawer drv;	
	double a;
	double b;
	int m;
	int n;
};
