
// sudokuGUIDlg.h: 头文件
//

#pragma once


// CsudokuGUIDlg 对话框
class CsudokuGUIDlg : public CDialog
{
// 构造
public:
	CsudokuGUIDlg(CWnd* pParent = NULL);	// 标准构造函数
	int count;
	int rightsudoku[9][9];
	CEdit* edits[81];
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUDOKUGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void OnBnClickedGbtn();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOkbtn();
	afx_msg void OnBnClickedRightbtn();
};
