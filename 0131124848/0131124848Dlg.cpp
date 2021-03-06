// 0131124848Dlg.cpp : 实现文件

#include "stdafx.h"
#include "0131124848.h"
#include "0131124848Dlg.h"
#include "afxdialogex.h"
#include"stdafx.h"

#include <windows.h>
#include <mmsystem.h>
#include <locale.h>
#include "pdflib.hpp"
#pragma comment(lib,"WINMM.LIB")
#include "pdflib.h"
#include "afxwin.h"
#pragma comment(lib,"pdflib.lib")
using namespace std;
using namespace pdflib;

#define _countof(arr) (sizeof(arr)/sizeof(arr[0])) 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	void SetPdf();
//	CStatic icon;
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC1, icon);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMy0131124848Dlg 对话框


CMy0131124848Dlg::CMy0131124848Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0131124848Dlg::IDD, pParent)
	, ShowTime(_T(""))
	, ExamNumber(_T("11111111111"))
	, IDNumber(_T("111111111111111111"))
	, WriteIn(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


//MCI_OPEN_PARMS op;
//DWORD cdlen;
UINT m_ulCount; 
unsigned char key[] = "xcysoft123" ;
void CMy0131124848Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3ST, ShowTime);
	DDX_Text(pDX, IDC_EDIT5WI, WriteIn);
	DDX_Control(pDX, IDC_COMBO1EN, ComboBox);
	DDX_Control(pDX, IDC_EDIT5WI, writein);
	DDX_Text(pDX, IDC_EDIT2IDN, IDNumber);
	DDV_MaxChars(pDX, IDNumber, 18);
	DDX_Text(pDX, IDC_EDIT4ERN, ExamNumber);
	DDV_MaxChars(pDX, ExamNumber, 11);
	DDX_Control(pDX, IDC_EDIT2IDN, idnumber);
	DDX_Control(pDX, IDC_EDIT4ERN, examnumber);
}


BEGIN_MESSAGE_MAP(CMy0131124848Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2BT, &CMy0131124848Dlg::OnBnClickedButton2bt)
	ON_BN_CLICKED(IDC_BUTTON3SM, &CMy0131124848Dlg::OnBnClickedButton3sm)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON4PT, &CMy0131124848Dlg::OnBnClickedButton4pt)
	ON_WM_SETFOCUS()
	ON_EN_SETFOCUS(IDC_EDIT5WI, &CMy0131124848Dlg::OnEnSetfocusEdit5wi)
	END_MESSAGE_MAP()


// CMy0131124848Dlg 消息处理程序


BOOL CMy0131124848Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	// TODO:  在此添加额外的初始化代码
	DWORD dwattr = GetFileAttributes(_T("D:\\您的应用程序"));
	if (dwattr == 0xffffffff)
		CreateDirectory(_T("D:\\您的应用程序"), NULL);
	ReadConfigurationFile();
	AddInitialValueCombo();
	Encryption();
	SetTimer(1, 1000, NULL);
	writein.SetReadOnly(true);
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON4PT);//提交以后就不能在进行操作
	if (pBtn != NULL)
	{
		pBtn->EnableWindow(false);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CMy0131124848Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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


//如果向对话框添加最小化按钮 则需要下面的代码
//来绘制该图标  对于使用文档/视图模型的 MFC 应用程序
//这将由框架自动完成


void CMy0131124848Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。


HCURSOR CMy0131124848Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMy0131124848Dlg::OnTimer(UINT_PTR nIDEvent)//倒计时运行
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnTimer(nIDEvent);
	CString str = _T("\r\n考试剩余时间\r\n\r\n"), str1, str2;
	int Minute, Second; //分，秒
	if (sumTimer == timer + 1)
	{
		writein.SetReadOnly(true);
		CString str = _T("\r\n您考试所用时间为\r\n\r\n"), str1, str2;
		str1.Format(_T("%02d分"), sumTimer / 60);
		str2.Format(_T("%02d秒"), sumTimer % 60);
		str += str1;
		str += str2;
		SetDlgItemText(IDC_EDIT3ST, str);
	}
	if (count != 0)
	{
		Minute = count / 60; //分 
		Second = count % 60;  //秒
		if (Second == 0){
			Second = 59;
			if (Minute > 0)
				Minute = Minute - 1;

		}
		else{
			Second = Second - 1;
		}
		str2.Format(_T("%02d分"), Minute);
		str1 = str1 + str2;
		str2.Format(_T("%02d秒"), Second);
		str1 = str1 + str2;
		str += str1;
		SetDlgItemText(IDC_EDIT3ST, str);
		if (Minute == 0 && Second == 0)
			KillTimer(1);
		count = count - 1;
		timer += 1;
	}
	else{
		return;
	}
}


HBRUSH CMy0131124848Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)//设置倒计时字体颜色
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_EDIT3ST)
	{
		pDC->SetTextColor(RGB(255, 2, 255));
	}
	return hbr;
}


void CMy0131124848Dlg::OnBnClickedButton2bt()//开始考试按钮
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (ExamNumber.GetLength()!= 11||IDNumber.GetLength()!=18)
	{
		MessageBox(_T("准考证号或者身份证号长度不够！无法进行考试！"), _T("提示"), MB_ICONINFORMATION | MB_YESNO);
		return;
	}
	OnPlay();
	WriteIn = "请在以下输入您听到的答案";
	GetDlgItem(IDC_COMBO1EN)->EnableWindow(FALSE);
	writein.SetReadOnly(false);
	idnumber.SetReadOnly(true);
	examnumber.SetReadOnly(true);
	DWORD k = getinfo(MCI_STATUS_LENGTH);
	int hm = k / 3600000;
	int ms = (k - 3600000 * hm) / 60000;
	int se = (k - 3600000 * hm - 60000 * ms) / 1000;
	count = ms * 60 + se;
	sumTimer = ms * 60 + se;
	UpdateData(false);
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON2BT);
	if (pBtn != NULL)
	{
		pBtn->EnableWindow(false);
	}
}


void CMy0131124848Dlg::OnBnClickedButton3sm()//提交按钮
{
	// TODO:  在此添加控件通知处理程序代码
	pause();
	KillTimer(1);
	resultsign = MessageBox(TEXT("提交以后您的本次考试将结束.\r\n您确定提交吗？"), TEXT("提示"), MB_ICONINFORMATION | MB_YESNO);
	if (resultsign == 6)
	{
		count = 0;
		MCI_GENERIC_PARMS gp;
		gp.dwCallback = NULL;
		mciSendCommand(m_ulCount, MCI_STOP, MCI_WAIT, (DWORD)&gp);
		CString str = _T("\r\n您考试所用时间为\r\n\r\n"), str1, str2;
		str1.Format(_T("%02d分"), timer / 60);
		str2.Format(_T("%02d秒"), timer % 60);
		str += str1;
		str += str2;
		SetDlgItemText(IDC_EDIT3ST, str);
		UpdateData(true);
		writein.SetReadOnly(true);
		CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON3SM);//提交以后不能再进行重复提交操作
		if (pBtn != NULL)
		{
			pBtn->EnableWindow(false);
		}
		pBtn = (CButton *)GetDlgItem(IDC_BUTTON4PT);//提交以后才能在进行打印PDF操作
		if (pBtn != NULL)
		{
			pBtn->EnableWindow(true);
		}
		ReadFile();
	}
	if (resultsign == 7)
	{
		resume();
		SetTimer(1, 1000, NULL);
	}
}


void CMy0131124848Dlg::OnBnClickedButton4pt()//打印成绩单按钮
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	SetPdf();
}


void CMy0131124848Dlg::OnEnSetfocusEdit5wi()//清除编辑框的默认内容
{
	// TODO:  在此添加控件通知处理程序代码
	if (WIsign == 0&&WriteIn!="")
	{
		SetDlgItemText(IDC_EDIT5WI, _T(""));
		WIsign++;
	}
}


void CMy0131124848Dlg::OnPlay()//播放音乐
{
	// TODO: Add your command handler code here  
	UpdateData(true);
	int nIndex = ComboBox.GetCurSel();//得到当前ComboBox的选中索引
	CString strCBText, temp = _T(".\\");
	ComboBox.GetLBText(nIndex, strCBText);//得到当前ComboBox的字符串值
	temp += strCBText;
	temp += ".mp3";
	mciSendString(_T("close wave"), 0, 0, NULL);
	mciSendCommand(m_ulCount, MCI_CLOSE, 0, NULL);//向多媒体设备发送消息，关闭多媒体设备   
	MCI_OPEN_PARMS mciopenparms;//打开   
	MCI_PLAY_PARMS mciplayparms;//播放   
	mciopenparms.lpstrElementName = temp;//播放路径   
	mciopenparms.lpstrDeviceType = NULL;//文件类型   
	mciSendCommand(0, MCI_OPEN, MCI_DEVTYPE_WAVEFORM_AUDIO, (DWORD)(LPVOID)&mciopenparms);//向MCI设备发送命令消息，包含歌曲文件的类型和路径   
	m_ulCount = mciopenparms.wDeviceID;//多媒体设备类型编号   
	mciplayparms.dwCallback = (DWORD)GetSafeHwnd();//歌曲播放支持类型   
	DWORD cdlen = 0;//某个音频文件的总时间长度   
	cdlen = getinfo(MCI_STATUS_LENGTH);//得到曲目长度
	DWORD cdfrom = 0;//歌曲的起点
	DWORD cdto = 0;//歌曲的终点
	cdto = MCI_MAKE_HMS(MCI_HMS_HOUR(cdlen), MCI_HMS_MINUTE(cdlen), MCI_HMS_SECOND(cdlen));//设置播放完毕某音频文件需要的时间n时n分n秒     
	mciplayparms.dwFrom = cdfrom;
	mciplayparms.dwTo = cdto;
	mciSendCommand(m_ulCount, MCI_PLAY, MCI_TO | MCI_FROM, (DWORD)(LPVOID)& mciplayparms);//向多媒体设备发送播放文件命令   
	UpdateData(false);
}


DWORD CMy0131124848Dlg::getinfo(DWORD item)//得到音乐时间
{
	MCI_STATUS_PARMS mcistatusparms;//MCI接口对象的状态
	mcistatusparms.dwCallback = (DWORD)GetSafeHwnd();//歌曲格式
	mcistatusparms.dwItem = item;//待获取的项目
	mcistatusparms.dwReturn = 0;
	mciSendCommand(m_ulCount, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}


void CMy0131124848Dlg::SetPdf()//设置PDF文件，以及显示
{
	UpdateData(true);
	int font;
	PDFlib p;
	double acuracy = similarity(WriteIn, answer);
	int speed = WriteIn.GetLength() / (timer / 60.0);
	double p_accuracy = atof(percentage_accuracy);
	double p_speed = atof(percentage_speed);
	double score = 0;
	if (speed >= max_speed)
	{
		speed = 100;
	}
	score = p_accuracy * acuracy * 100 + p_speed*speed;
	t1 = "准考证号 : ";
	t1 += ExamNumber;
	t2 = "身份证号码 : ";
	t2 += IDNumber;
	t3 = "您打字的准确率是";
	t4.Format(_T("%f"), acuracy * 100);
	t4 = t4.Left(5);
	t3 += t4;
	t3 += "%,速度是";
	t5.Format(_T("%d"), speed);
	t3 += t5;
	t3 += "个字/分钟,本次考试的成绩是";
	t6.Format(_T("%f"), score);
	t6 = t6.Left(5);
	t3 += t6;
	t3 += "分";
	t7 = "以下是您本次录入的内容：";
	//This means we must check return values of load_font() etc.
	p.set_option(L"errorpolicy=return");
	p.begin_document(L"D:\\您的应用程序\\0131124848.pdf", L"");
	p.set_info(L"Creator", L"0131124848");
	p.set_info(L"Author", L"mzs");
	p.set_info(L"Title", L"ExamTest");
	p.begin_page_ext(a4_width, a4_height, L"");
	// Change "host" encoding to "winansi" or whatever you need!
	font = p.load_font(L"宋体", L"unicode", L"");
	p.setfont(font, 15);
	p.set_text_pos(50, 700);
	CStringW strw,strw1(WriteIn);
	wstring wstr;
	strw = t1;
	wstr = strw;
	p.show(wstr);
	strw = t2;
	wstr = strw;
	p.continue_text(wstr);
	strw = t3;
	wstr = strw;
	p.continue_text(wstr);
	strw = t7;
	wstr = strw;
	p.continue_text(wstr);
	p.continue_text(L"");
	CStringW t;
	int s1=0,s2=0;
	t = WriteIn;
	WriteIn = "";
	int temp = (int)t.GetLength();
	for (int i = 0; i <= (t.GetLength()/40); i++)
	{
		s1 = i * 40;
		WriteIn += t.Mid(s1,40);
		WriteIn += "\r\n";
	}
	font = p.load_font(L"宋体", L"unicode", L"");
	p.setfont(font, 10);
	CString sCombEdit=_T("");
	CString sTemp;
	CString s;
	sTemp.Empty();
	CString sFind = _T("\r\n");//寻找回车确认编辑
	int iStart = 0;
	int iPos = 0;
	int iCnt = 0;
	int idEdit = 0;
	iPos = WriteIn.Find(sFind, iStart);
	if ((iPos = WriteIn.Find(sFind, iStart)) != -1)
	{
		while ((iPos = WriteIn.Find(sFind, iStart)) != -1)
		{
			iCnt = iPos - iStart;
			for (int i = 0; i < iCnt; i++)
			{
				sTemp = WriteIn.GetAt(iStart + i);
				sCombEdit += sTemp;
			}
			strw = sCombEdit;
			wstr = strw;
			p.continue_text(wstr);
			idEdit++;
			iStart = iPos + 2;
			sCombEdit = "";
		}
	}
	else
	{
		strw = WriteIn;
		wstr = strw;
		p.continue_text(wstr);
	}
	iCnt = WriteIn.GetLength() - iStart;
	for (int i = 0; i < iCnt; i++)
	{
		sTemp = WriteIn.GetAt(iStart + i);
		sCombEdit += sTemp;
	}
	strw = sCombEdit;
	wstr = strw;
	p.continue_text(wstr);
	p.end_page_ext(L"");
	p.end_document(L"");
	ShellExecute(NULL, _T("open"),
	_T("D:\\您的应用程序\\0131124848.pdf"),
	NULL, NULL, SW_SHOWMAXIMIZED);//打印完后，立即使用默认pdf阅读器，全屏打开<span>
}


void CMy0131124848Dlg::ReadFile()//读正确答案
{
	int nIndex = ComboBox.GetCurSel();//得到当前ComboBox的选中索引
	CString strCBText, temp = _T(".\\");
	ComboBox.GetLBText(nIndex, strCBText);
	temp += strCBText;
	temp += ".txt";
	char * old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");
	GetPrivateProfileString(_T("Examanswer"), _T("answer"), _T(""),answer.GetBufferSetLength(10000), 10000, temp);
	answer.ReleaseBuffer();
	char chLetter[10000];
	int i = 0;
	for (; i < answer.GetLength(); i++)
	{
		chLetter[i]= answer.GetAt(i)-1;
	}
	chLetter[i] = '\0';
	answer = chLetter;
	setlocale(LC_CTYPE, old_locale);
}


double CMy0131124848Dlg::similarity(CString str1, CString str2)//求准确率
{
	int len1 = str1.GetLength();
	int len2 = str2.GetLength();
	int **dif = new int*[len1 + 1];
	for (int i = 0; i < len1 + 1; ++i){
		dif[i] = new int[len2 + 1];
	}
	for (int i = 0; i <= len1; i++)
	{
		dif[i][0] = i;
	}
	for (int i = 0; i <= len2; i++)
	{
		dif[0][i] = i;
	}
	int temp = 0;
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (str1.GetAt(i - 1) == str2.GetAt(j - 1))
			{
				temp = 0;
			}
			else
			{
				temp = 1;
			}
			dif[i][j] = Min(dif[i - 1][j - 1] + temp, dif[i - 1][j] + 1, dif[i][j - 1] + 1);
		}
	}
	return 1 - (double)dif[len1][len2] / Max(str1.GetLength(), str2.GetLength());
}


int CMy0131124848Dlg::Min(int a, int b, int c)
{
	if (a < b);
	else
		a = b;
	if (a < c);
	else
		a = c;
	return a;
}


int CMy0131124848Dlg::Max(int a, int b)
{
	if (a < b)
		return b;
	else
		return a;
}


void CMy0131124848Dlg::pause()//暂停音乐
{
	MCI_PLAY_PARMS PlayParms;
	mciSendCommand(m_ulCount, MCI_PAUSE, 0, (DWORD)(LPVOID)&PlayParms);
}


void CMy0131124848Dlg::resume()//恢复音乐
{
	MCI_PLAY_PARMS PlayParms;
	mciSendCommand(m_ulCount, MCI_RESUME, 0, (DWORD)(LPVOID)&PlayParms);
}


void CMy0131124848Dlg::ReadConfigurationFile()//读取配置文件
{
		CString temp;
		temp = ".\\";
		temp += "1.ini";
		GetPrivateProfileString(_T("ExamInfo"), _T("total_minutes"), _T(""), total_minutes.GetBufferSetLength(20), 20, temp);
		total_minutes.ReleaseBuffer();
		total_question = GetPrivateProfileInt(_T("ExamInfo"), _T("total_question"), 0, temp);
		GetPrivateProfileString(_T("ExamInfo"), _T("audio_format"), _T(""), audio_format.GetBufferSetLength(20), 20, temp);
		audio_format.ReleaseBuffer();
		max_speed = GetPrivateProfileInt(_T("ExamInfo"), _T("total_question"), 0, temp);
		GetPrivateProfileString(_T("ExamInfo"), _T("percentage_accuracy"), _T(""), percentage_accuracy.GetBufferSetLength(20), 20, temp);
		percentage_accuracy.ReleaseBuffer();
		GetPrivateProfileString(_T("ExamInfo"), _T("percentage_speed"), _T(""), percentage_speed.GetBufferSetLength(20), 20, temp);
		percentage_speed.ReleaseBuffer();
}


void CMy0131124848Dlg::AddInitialValueCombo()//给ComboBox初始化值
{
	CString strTemp;
	ComboBox.ResetContent();
	//((CComboBox*)GetDlgItem(IDC_COMBO1EN))->ResetContent(); //消除ID为IDC_COMBO_CF现有所有内容
	for (int i = 1; i <= total_question; i++)
	{
		strTemp.Format(_T("%d"), i);
		ComboBox.AddString(strTemp);
		//((CComboBox*)GetDlgItem(IDC_COMBO1EN))->AddString(strTemp); //为控件添加初始化数据
	}
	ComboBox.SetCurSel(0);
}


void CMy0131124848Dlg::Encryption()//给答案进行异或加密
{
	for (int i = 1; i <= total_question; i++)
	{
		CString temp=_T(".\\");
		CString turn;
		turn.Format(_T("%d"), i);
		temp += turn;
		temp += ".txt";
		int text=GetPrivateProfileInt(_T("Examanswer"),_T("sign"),0,temp);
		if (text == 1)
		{
			CString str;
			GetPrivateProfileString(_T("Examanswer"), _T("answer"), _T(""), str.GetBufferSetLength(10000), 10000, temp);
			str.ReleaseBuffer();
			char chLetter[10000];
			int i=0;
			for (; i < str.GetLength(); i++)
			{
				chLetter[i]= str.GetAt(i)+1;
			}
			chLetter[i] = '\0';
			str = chLetter;
			WritePrivateProfileString(_T("Examanswer"), _T("answer"), str, temp);
			str.Format(_T("%d"), 0);
			WritePrivateProfileString(_T("Examanswer"), _T("sign"), str, temp);
		}
	}
}



BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
