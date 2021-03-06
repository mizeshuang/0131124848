
// 0131124848Dlg.h : 头文件

#pragma once
#include "afxwin.h"

// CMy0131124848Dlg 对话框
class CMy0131124848Dlg : public CDialogEx
{
// 构造
public:
	CMy0131124848Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0131124848_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void OnPlay();
	DWORD getinfo(DWORD);
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString ShowTime;
	CString WriteIn;
	CComboBox ComboBox;
	CEdit writein;
	CString IDNumber;
	CString ExamNumber;
	CEdit idnumber;
	CEdit examnumber;
	int resultsign;
	int count=0;
	int timer = 0;
	int sumTimer = 0;
	CString total_minutes;
	int total_question;
	CString audio_format;
    int max_speed;
	CString percentage_accuracy;
	CString percentage_speed;
	CString answer;
	int WIsign=0;
	CString t1, t2, t3, t4,t5,t6,t7;
	char *result = new char[1024];
	char *miwen_hex = new char[1024];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2bt();
	afx_msg void OnBnClickedButton3sm();
	afx_msg void OnBnClickedButton4pt();
	afx_msg void OnEnSetfocusEdit5wi();
	void SetPdf();
	void ReadFile();
	double similarity(CString str1, CString str2);
	int Min(int a, int b, int c);
	int Max(int a, int b);
	void pause();
	void resume();
	void ReadConfigurationFile();
	void AddInitialValueCombo();
	void Encryption();
};
