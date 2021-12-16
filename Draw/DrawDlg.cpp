
// DrawDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Draw.h"
#include "DrawDlg.h"
#include "afxdialogex.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "LagrangeInterpolator.h"
#include "Approximation.h"

#define M_E        2.71828182845904523536// math const e


// диалоговое окно CDrawDlg
CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAW_DIALOG, pParent)
	, a(0)
	, b(2)
	, m(10)
	, n(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_a, a);
	DDX_Text(pDX, IDC_b, b);
	DDX_Text(pDX, IDC_m, m);
	DDX_Text(pDX, IDC_n, n);
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDrawDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CDrawDlg

BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	drv.Create(GetDlgItem(IDC_PICTURE)->GetSafeHwnd());
	//drv2.Create(GetDlgItem(IDC_PICTURE2)->GetSafeHwnd());

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//drv.Draw();
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawDlg::OnBnClickedOk()
{
	UpdateData(true);
	Approximation appr;


	vector<double> ApproxFunc, FuncPoints, OriginalFunc;
	vector<double> X, XPoints;

	double* xPoints = new double[m];
	double* f = new double[m];
	double x = a;

	appr.GetPointsX(xPoints, a, b, m);
	appr.RandomiseF(f, xPoints, m);

	for (int i = 0; i < 1000; i++)
	{
		X.push_back(x);
		ApproxFunc.push_back(appr.Approximate(x, a, b, m, n));
		OriginalFunc.push_back(pow(M_E, x) * cos(x));
		x += 0.01;
	}
	for (int i = 0; i < m; i++)
	{
		xPoints[i] = a + i * (b - a)/ (m - 1);
		XPoints.push_back(xPoints[i]);
		FuncPoints.push_back(f[i]);
	}

	drv.Draw(ApproxFunc, FuncPoints, a, b, X, XPoints);
}
