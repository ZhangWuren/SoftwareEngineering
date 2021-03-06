
// sudokuGUIDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "sudokuGUI.h"
#include "sudokuGUIDlg.h"
#include "sudokugen.h"
#include "afxdialogex.h"
#include "iostream"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CsudokuGUIDlg 对话框



CsudokuGUIDlg::CsudokuGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SUDOKUGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	count = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) {
			rightsudoku[i][j] = 0;
		}
	}
}

void CsudokuGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsudokuGUIDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(GBTN, &CsudokuGUIDlg::OnBnClickedGbtn)
	ON_BN_CLICKED(OKBTN, &CsudokuGUIDlg::OnBnClickedOkbtn)
	ON_BN_CLICKED(RIGHTBTN, &CsudokuGUIDlg::OnBnClickedRightbtn)
END_MESSAGE_MAP()


// CsudokuGUIDlg 消息处理程序

BOOL CsudokuGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CsudokuGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsudokuGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsudokuGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsudokuGUIDlg::OnBnClickedGbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(GBTN)->SetWindowText(_T("生成数独"));
	count++;
	int *sudoku81;
	int csudoku[81];
	int *blankgrid;
	int cblankgrid[81];

	sudoku81 = generateSudoku(count);
	for (int i = 0; i < 81; i++)
	{
		csudoku[i] = *sudoku81;
		sudoku81++;
	}
	for (int i = 0, k = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			rightsudoku[i][j] = csudoku[k];
			k++;
		}
	}
	
	blankgrid = generateBlank(count % 3);
	for (int i = 0; i < 36; i++)
	{
		cblankgrid[i] = *blankgrid;
		blankgrid++;
	}


	{
		edits[0] = (CEdit*)GetDlgItem(IDC_EDIT1);
		edits[1] = (CEdit*)GetDlgItem(IDC_EDIT2);
		edits[2] = (CEdit*)GetDlgItem(IDC_EDIT3);
		edits[3] = (CEdit*)GetDlgItem(IDC_EDIT4);
		edits[4] = (CEdit*)GetDlgItem(IDC_EDIT5);
		edits[5] = (CEdit*)GetDlgItem(IDC_EDIT6);
		edits[6] = (CEdit*)GetDlgItem(IDC_EDIT7);
		edits[7] = (CEdit*)GetDlgItem(IDC_EDIT8);
		edits[8] = (CEdit*)GetDlgItem(IDC_EDIT9);
		edits[9] = (CEdit*)GetDlgItem(IDC_EDIT10);
		edits[10] = (CEdit*)GetDlgItem(IDC_EDIT11);
		edits[11] = (CEdit*)GetDlgItem(IDC_EDIT12);
		edits[12] = (CEdit*)GetDlgItem(IDC_EDIT13);
		edits[13] = (CEdit*)GetDlgItem(IDC_EDIT14);
		edits[14] = (CEdit*)GetDlgItem(IDC_EDIT15);
		edits[15] = (CEdit*)GetDlgItem(IDC_EDIT16);
		edits[16] = (CEdit*)GetDlgItem(IDC_EDIT17);
		edits[17] = (CEdit*)GetDlgItem(IDC_EDIT18);
		edits[18] = (CEdit*)GetDlgItem(IDC_EDIT19);
		edits[19] = (CEdit*)GetDlgItem(IDC_EDIT20);
		edits[20] = (CEdit*)GetDlgItem(IDC_EDIT21);
		edits[21] = (CEdit*)GetDlgItem(IDC_EDIT22);
		edits[22] = (CEdit*)GetDlgItem(IDC_EDIT23);
		edits[23] = (CEdit*)GetDlgItem(IDC_EDIT24);
		edits[24] = (CEdit*)GetDlgItem(IDC_EDIT25);
		edits[25] = (CEdit*)GetDlgItem(IDC_EDIT26);
		edits[26] = (CEdit*)GetDlgItem(IDC_EDIT27);
		edits[27] = (CEdit*)GetDlgItem(IDC_EDIT28);
		edits[28] = (CEdit*)GetDlgItem(IDC_EDIT29);
		edits[29] = (CEdit*)GetDlgItem(IDC_EDIT30);
		edits[30] = (CEdit*)GetDlgItem(IDC_EDIT31);
		edits[31] = (CEdit*)GetDlgItem(IDC_EDIT32);
		edits[32] = (CEdit*)GetDlgItem(IDC_EDIT33);
		edits[33] = (CEdit*)GetDlgItem(IDC_EDIT34);
		edits[34] = (CEdit*)GetDlgItem(IDC_EDIT35);
		edits[35] = (CEdit*)GetDlgItem(IDC_EDIT36);
		edits[36] = (CEdit*)GetDlgItem(IDC_EDIT37);
		edits[37] = (CEdit*)GetDlgItem(IDC_EDIT38);
		edits[38] = (CEdit*)GetDlgItem(IDC_EDIT39);
		edits[39] = (CEdit*)GetDlgItem(IDC_EDIT40);
		edits[40] = (CEdit*)GetDlgItem(IDC_EDIT41);
		edits[41] = (CEdit*)GetDlgItem(IDC_EDIT42);
		edits[42] = (CEdit*)GetDlgItem(IDC_EDIT43);
		edits[43] = (CEdit*)GetDlgItem(IDC_EDIT44);
		edits[44] = (CEdit*)GetDlgItem(IDC_EDIT45);
		edits[45] = (CEdit*)GetDlgItem(IDC_EDIT46);
		edits[46] = (CEdit*)GetDlgItem(IDC_EDIT47);
		edits[47] = (CEdit*)GetDlgItem(IDC_EDIT48);
		edits[48] = (CEdit*)GetDlgItem(IDC_EDIT49);
		edits[49] = (CEdit*)GetDlgItem(IDC_EDIT50);
		edits[50] = (CEdit*)GetDlgItem(IDC_EDIT51);
		edits[51] = (CEdit*)GetDlgItem(IDC_EDIT52);
		edits[52] = (CEdit*)GetDlgItem(IDC_EDIT53);
		edits[53] = (CEdit*)GetDlgItem(IDC_EDIT54);
		edits[54] = (CEdit*)GetDlgItem(IDC_EDIT55);
		edits[55] = (CEdit*)GetDlgItem(IDC_EDIT56);
		edits[56] = (CEdit*)GetDlgItem(IDC_EDIT57);
		edits[57] = (CEdit*)GetDlgItem(IDC_EDIT58);
		edits[58] = (CEdit*)GetDlgItem(IDC_EDIT59);
		edits[59] = (CEdit*)GetDlgItem(IDC_EDIT60);
		edits[60] = (CEdit*)GetDlgItem(IDC_EDIT61);
		edits[61] = (CEdit*)GetDlgItem(IDC_EDIT62);
		edits[62] = (CEdit*)GetDlgItem(IDC_EDIT63);
		edits[63] = (CEdit*)GetDlgItem(IDC_EDIT64);
		edits[64] = (CEdit*)GetDlgItem(IDC_EDIT65);
		edits[65] = (CEdit*)GetDlgItem(IDC_EDIT66);
		edits[66] = (CEdit*)GetDlgItem(IDC_EDIT67);
		edits[67] = (CEdit*)GetDlgItem(IDC_EDIT68);
		edits[68] = (CEdit*)GetDlgItem(IDC_EDIT69);
		edits[69] = (CEdit*)GetDlgItem(IDC_EDIT70);
		edits[70] = (CEdit*)GetDlgItem(IDC_EDIT71);
		edits[71] = (CEdit*)GetDlgItem(IDC_EDIT72);
		edits[72] = (CEdit*)GetDlgItem(IDC_EDIT73);
		edits[73] = (CEdit*)GetDlgItem(IDC_EDIT74);
		edits[74] = (CEdit*)GetDlgItem(IDC_EDIT75);
		edits[75] = (CEdit*)GetDlgItem(IDC_EDIT76);
		edits[76] = (CEdit*)GetDlgItem(IDC_EDIT77);
		edits[77] = (CEdit*)GetDlgItem(IDC_EDIT78);
		edits[78] = (CEdit*)GetDlgItem(IDC_EDIT79);
		edits[79] = (CEdit*)GetDlgItem(IDC_EDIT80);
		edits[80] = (CEdit*)GetDlgItem(IDC_EDIT81);
	}

	for (int i = 0; i < 81; i++)
	{
		CString str;
		str.Format(_T("%d"), csudoku[i]);
		LPCTSTR lpctstr = LPCTSTR(str);
		edits[i]->SetWindowText(lpctstr);
		edits[i]->SetReadOnly(true);
	}

	for (int i = 0; i < 36; i++) {
		edits[cblankgrid[i]]->SetReadOnly(false);
		CString str;
		str.Format(_T(""));
		LPCTSTR lpctstr = LPCTSTR(str);
		edits[cblankgrid[i]]->SetWindowText(lpctstr);
	}
}


void CsudokuGUIDlg::OnBnClickedOkbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (count == 0) {
		AfxMessageBox(_T("请先点击生成数独"));
		return;
	}

	int sudoku[9][9];
	for (int i = 0, k = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			CString temp;
			edits[k]->GetWindowText(temp);
			k++;
			if (_ttoi(temp) < 0) { 
				std::cout << "wrong"; 
			}
			else { 
				sudoku[i][j] = _ttoi(temp); 
			}
		}
	}

	int flag = 0;
	for (int i = 0; i < 9; i++)
	{
		if (flag)break;
		for (int j = 0; j < 9; j++) {
			if (!isOK(sudoku, i, j, sudoku[i][j]))
			{
				AfxMessageBox(_T("错误！"));
				flag = 1;
				break;
			}
		}
	}
	if (!flag)
	{
		AfxMessageBox(_T("成功！"));
		GetDlgItem(GBTN)->SetWindowText(_T("下一个数独"));
	}
}


void CsudokuGUIDlg::OnBnClickedRightbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (count == 0) {
		AfxMessageBox(_T("请先点击生成数独"));
		return;
	}

	for (int i = 0,k = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			CString str;
			str.Format(_T("%d"), rightsudoku[i][j]);
			LPCTSTR lpctstr = LPCTSTR(str);
			edits[k]->SetWindowText(lpctstr);
			k++;
		}
	}
}
