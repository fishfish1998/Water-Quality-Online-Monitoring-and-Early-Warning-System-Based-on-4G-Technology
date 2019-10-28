
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include <iostream>
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#define Moniter 60000

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void StringtoHex(BYTE *GB, int glen, BYTE* SB, int* slen);
//CString格式的读取数据命令，每两个数字转为一个十六进制数存在SB中

CString resultph(CString ori);
CString resultzd(CString ori);
CString resultyd(CString ori);
CString resultry(CString ori);
//计算溶氧，盐度，ph

CString resultdd(CString oridd);
//计算电导率

CString resultwd(CString oriwd);
//计算温度

int hex2dec(char*s);
//CString转化为数组以后，用这个函数转化成十进制数

int getdecnumber(char ch);
//hex2dec的子函数

int num = 0; CString editnum = _T("00"); int i; int flag1; int flag2 = 0;//控制打开串口时采样总次数不变化
//本轮监测超标的总次数
int cap = 0; CString editcap = _T("00");
//目前已采样的次数

//在水质超标且距离上一次采样已经过了3次采样后，再采样

CString m_NbiotSend; int TimeStep = 10000; CString editTimeStep=_T("10");
//读取数据的命令，定时器初始步长

CString temp3, tempdd, tempwd, tempry, tempzd, tempyd, tempph, total;
//向NB_iot发送数据时需要集合的CString

//模块IMEI是868744031003381


UINT ThreadFun(LPVOID para);
//子线程函数，按下开始监测后，两个定时器启动，随即创建这个子线程，使得参数超标时，“本轮
//超标次数”编辑框改变值


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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	
	
	, m_NbiotReceive(_T(""))
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDITwd, editwd);
	//  DDX_Text(pDX, IDC_EDITry, editry);
	//  DDX_Text(pDX, IDC_EDITph, editph);
	//  DDX_Text(pDX, IDC_EDITzd, editzd);
	//  DDX_Text(pDX, IDC_EDITdd, editdd);
	//  DDX_Text(pDX, IDC_EDITyd, edityd);
	DDX_Control(pDX, IDC_COMBO1, m_comb1);
	DDX_Control(pDX, IDC_COMBO2, comb2);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	//DDX_Text(pDX, IDC_EDITsend, editsend);
	//  DDX_Text(pDX, IDC_EDITwd, edittest);
	DDX_Control(pDX, IDC_MSCOMM2, m_mscom2);
	DDX_Control(pDX, IDC_MSCOMM3, m_mscom3);
	DDX_Control(pDX, IDC_COMBO3, comb3);
	DDX_Control(pDX, IDC_COMBO4, comb4);
	DDX_Control(pDX, IDC_COMBO5, comb5);
	DDX_Control(pDX, IDC_COMBO6, comb6);
	DDX_Text(pDX, IDC_EDIT2, m_NbiotReceive);
	//DDX_Text(pDX, IDC_EDIT1, ccc);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	//ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMFCApplication1Dlg::OnBnClickedButton4)
//	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplication1Dlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCApplication1Dlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCApplication1Dlg::OnBnClickedButtonOpen)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CMFCApplication1Dlg::OnCbnSelchangeCombo6)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCApplication1Dlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CMFCApplication1Dlg::OnCbnSelchangeCombo5)
	ON_WM_TIMER()//!!!定时器
	//ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDITnum, &CMFCApplication1Dlg::OnChangeEditnum)
	//ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	//ON_EN_CHANGE(IDC_EDITwd, &CMFCApplication1Dlg::OnEnChangeEditwd)
	//ON_EN_CHANGE(IDC_EDITyd, &CMFCApplication1Dlg::OnEnChangeEdityd)
	//ON_EN_CHANGE(IDC_EDITph, &CMFCApplication1Dlg::OnEnChangeEditph)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	//选择串口
	CString str;
	
	for (int i = 0; i < 13; i++)
	{
		str.Format(_T("com%d"), i + 1);
		m_comb1.InsertString(i, str);
		comb3.InsertString(i, str);
		comb5.InsertString(i, str);
	}
	m_comb1.SetCurSel(0);
	comb3.SetCurSel(0);
	comb5.SetCurSel(0);

	CString str1[] = {_T("9600")  };

	for (int i = 0; i < 1; i++)
	{
		int judge_tf = comb2.AddString(str1[i]);
		int judge_tf2 = comb4.AddString(str1[i]);
		int judge_tf3 = comb6.AddString(str1[i]);
		//if ((judge_tf = CB_ERR) || judge_tf == CBN_ERRSPACE)
			//MessageBox(_T("build baud error"));
		
	}
	comb2.SetCurSel(1); comb4.SetCurSel(1); comb6.SetCurSel(1);

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

	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//初始化函数，在其中添加了选择串口、波特率的语句

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_mscom.get_PortOpen())
	{
		m_mscom.put_PortOpen(false);
	}
	CDialogEx::OnCancel();

}

//退出的函数



int k=1;
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	CString name;
	GetDlgItemText(IDC_BUTTON_SEND,name);
	CWnd *h3;
	h3 = GetDlgItem(IDC_BUTTON_SEND);
	if (name == _T("开始监测"))
	{
		// TODO: 在此添加控件通知处理程序代码
		if ((!m_mscom.get_PortOpen()) || (!m_mscom2.get_PortOpen()) || (!m_mscom3.get_PortOpen()))
		{
			CString str3;
			str3 = _T("未打开数据接受端串口，无法接收!");
			MessageBox(str3);
		}
		else
		{   
			name = _T("停止监测");
			h3->SetWindowText(name);
			flag2 = 0; cap = 0; num = 0;
			editcap.Format("%02d", cap);
			editnum.Format("%02d", num);
			SetDlgItemText(IDC_EDITTimeStep, editTimeStep);
			SetDlgItemText(IDC_EDITnum, editnum);
			SetDlgItemText(IDC_EDITcap, editcap);
			flag1 = 0;
			m_NbiotSend = _T("ATI\r\n");
			m_mscom2.put_Output(COleVariant(m_NbiotSend));
			Sleep(50);
			m_NbiotSend = _T("AT+NCDP?\r\n");
			m_mscom2.put_Output(COleVariant(m_NbiotSend));
			Sleep(50);
			m_NbiotSend = _T("AT+NNMI=1\r\n");
			m_mscom2.put_Output(COleVariant(m_NbiotSend));
			SetTimer(1, TimeStep, NULL);
			Sleep(1000);
			SetTimer(2, TimeStep, NULL);
			CWinThread* pThread = AfxBeginThread(ThreadFun, this);
		}
	}
	else if (name == _T("停止监测"))
		{
		    k = 0;
			KillTimer(1);
			KillTimer(2);
			name = _T("开始监测");
			h3->SetWindowText(name);
		}
	
}//开始监测的函数，按下按键，设置两个定时器

	//控制开始监测、停止监测的函数


void StringtoHex(BYTE *GB, int glen, BYTE* SB, int* slen)
{
	int i; //遍历输入的字符串
	int a = 0;
	char temp; //接收字符，用来判断是否为空格，若是则跳过
	char temp1, temp2; //接收一个字节的两个字符 例如EB，则temp1='E',temp2 = 'B'
	*slen = 0; //输出的16进制字符串长度
	for (i = 0; i<glen; i++)
	{
		temp = GB[i];
		if (temp == ' ')
			continue;

		if (a == 0)
			temp1 = GB[i];
		if (a == 1)
			temp2 = GB[i];
		a++;

		if (a == 2)
		{
			a = 0;
			temp1 = temp1 - '0';
			if (temp1>10)
				temp1 = temp1 - 7;
			temp2 = temp2 - '0';
			if (temp2>10)
				temp2 = temp2 - 7;

			SB[*slen] = temp1 * 16 + temp2;
			(*slen)++;
		}
	}

}

////CString格式的读取数据命令，每两个数字转为一个十六进制数存在SB中，与开始、停止监测相关

void CMFCApplication1Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str, str11,str12,str13, n;///
	CWnd *h1;
	h1 = GetDlgItem(IDC_BUTTON_OPEN);//h1，打开串口的按钮
	GetDlgItemText(IDC_BUTTON_OPEN, str);//按钮上的名字
	//依次打开三个串口
	
	if (str==_T("打开串口"))
	{
		if (m_mscom.get_PortOpen())
		{
			m_mscom.put_PortOpen(false);//打开串口
		}
			comb2.GetLBText(comb2.GetCurSel(), str11);
			str11 = str11 + ',' + 'n' + ',' + '8' + ',' + '1';
			m_mscom.put_Settings(str11);//设置波特率

			m_mscom.put_CommPort((m_comb1.GetCurSel() + 1));  //选择串口

			m_mscom.put_InputMode(1);
			m_mscom.put_InputLen(1024);
			m_mscom.put_RThreshold(1);
			m_mscom.put_RTSEnable(1);//二进制输入，接收数据长度，一个字符引发事件，RT允许

			m_mscom.put_PortOpen(true);//打开串口


		if (m_mscom2.get_PortOpen())
		{
			m_mscom2.put_PortOpen(false);
		}
			comb4.GetLBText(comb4.GetCurSel(), str12);
			str12 = str12 + ',' + 'n' + ',' + '8' + ',' + '1';
			m_mscom2.put_Settings(str12);//设置波特率

			m_mscom2.put_CommPort((comb3.GetCurSel() + 1));  //选择串口

			m_mscom2.put_InputMode(1); 
			m_mscom2.put_InputLen(1024);
			m_mscom2.put_RThreshold(1);
			m_mscom2.put_RTSEnable(1);//二进制输入，接收数据长度，一个字符引发事件，RT允许

			m_mscom2.put_PortOpen(true);//打开串口
		
			if (m_mscom3.get_PortOpen())
			{
				m_mscom3.put_PortOpen(false);
			}
			comb6.GetLBText(comb6.GetCurSel(), str13);
			str13 = str13 + ',' + 'n' + ',' + '8' + ',' + '1';
			m_mscom3.put_Settings(str13);//设置波特率

			m_mscom3.put_CommPort((comb5.GetCurSel() + 1));  //选择串口

			m_mscom3.put_InputMode(1);
			m_mscom3.put_InputLen(1024);
			m_mscom3.put_RThreshold(1);
			m_mscom3.put_RTSEnable(1);//二进制输入，接收数据长度，一个字符引发事件，RT允许

			m_mscom3.put_PortOpen(true);//打开串口


		if ((m_mscom2.get_PortOpen())&& (m_mscom.get_PortOpen())&& (m_mscom3.get_PortOpen()))
		{
			str = _T("关闭串口");
			UpdateData(true);
			h1->SetWindowText(str);
			SetTimer(3, Moniter, NULL);
		}
		/*else
		{
			m_mscom.put_PortOpen(false);
			if (str != _T("打开串口"))
			{
				str = _T("打开串口");
				UpdateData(true);//控件的值赋给成员变量
				h1->SetWindowText(str);
			}
		}*/
	}
	else if(str == _T("关闭串口"))
	{
		m_mscom.put_PortOpen(false);
		m_mscom2.put_PortOpen(false);
		m_mscom3.put_PortOpen(false);
		if ((!m_mscom2.get_PortOpen()) && (!m_mscom.get_PortOpen()) && (!m_mscom3.get_PortOpen()))
		{
			str = _T("打开串口");
			KillTimer(3);
			//UpdateData(true);//控件的值赋给成员变量
			h1->SetWindowText(str);
		}
	}
}
	
//打开、关闭串口的函数

BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnCommMscomm1, VTS_NONE)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM2, 1, CMFCApplication1Dlg::OnCommMscomm2, VTS_NONE)
END_EVENTSINK_MAP()


//hex2dec子函数

CString temp2, temp; long L; CString editdd, editwd, editry, editzd, edityd, editph;
float feditdd = 0.0, feditwd = 0.0, feditry = 0.0, feditzd = 0.0, fedityd = 0.0, feditph = 0.0;

//temp,temp2是消息处理中用到，之后6个CString由它解析而来,float用于子线程中判断是否超标

void CMFCApplication1Dlg::OnCommMscomm1()
{
	byte rxdata[1024] = { 0 };
	COleSafeArray fs;
	VARIANT InputData;
	long len, k; 
	CString strtemp;//!!!!!
	// TODO: 在此处添加消息处理程序代码
	if (m_mscom.get_CommEvent() == 2)
	{

		int up = 0;
		Sleep(100);
		InputData = m_mscom.get_Input();
		fs = InputData;
		len = fs.GetOneDimSize();
		for (k = 0; k < len; k++)
			fs.GetElement(&k, rxdata + k);
		for (k = 0; k < len; k++)
		{
			strtemp.Format("%02x", *(rxdata + k));
			temp += strtemp;
			if (k == len - 1)//!!!!!
			{
				temp2 = temp;
				temp = "";
				//CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)para;//将主Dialog传递过来
				temp3 = temp2.Mid(0, 2);
				if (temp3 == "08")
				{
					tempph = temp2.Mid(18, 4);
					tempzd = temp2.Mid(10, 4);
					tempry = temp2.Mid(6, 4);
					editph = resultph(tempph);
					editzd = resultzd(tempzd) + "NTU";
					editry = resultry(tempry) + "mg/L";//(char)0x0d+ (char)0x0a;
					SetDlgItemText(IDC_EDITry, editry);
					SetDlgItemText(IDC_EDITph, editph);
					SetDlgItemText(IDC_EDITzd, editzd);
					up =1;
				}
				if (temp3 == "03")
				{
					CString A = "2250";
					tempwd = temp2.Mid(10, 4);
					tempdd = temp2.Mid(6, 4);
					tempyd = temp2.Mid(14, 4);
					edityd = resultyd(tempyd)+"ppt";
					editdd = A + _T("us/cm");
					editwd = resultwd(tempwd) + "℃";
					SetDlgItemText(IDC_EDITyd, edityd);
					SetDlgItemText(IDC_EDITwd, editwd);
					SetDlgItemText(IDC_EDITdd, editdd);
					up =2;
				}
			}

			//edittest += temp2;
			UpdateData(false);
		}
		if (up == 2)
		{
			up = 0;
			CString address = "00";
			editnum.Format("%02d", num);
			total = _T("AT+NMGS=15,") + address + tempry + tempzd + tempph + tempdd + tempwd + tempyd + editnum + editcap + _T("\r\n");
			
			m_mscom2.put_Output(COleVariant(total));
		}
	}
}

//消息处理函数，从temp2中解析出数据，并转化、计算，子函数result

UINT ThreadFun(LPVOID para)
{
	Sleep(13000);
	CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)para;//将主Dialog传递过来
	while (k)
	{
		if ((feditdd > 3000.0) || ((feditph > 8.5) || ((feditph < 6.5) && (feditph != 0.0))) || ((feditwd >40.0) || ((feditwd < 10.0) && (feditwd != 0.0))) || (feditry > 8.9) || (fedityd > 1.5))
		{
			
			num += 1; flag2 = 1;
			editnum.Format("%02d", num);
			pDlg->SetDlgItemText(IDC_EDITnum, editnum);//这里可以直接把int显示在编辑框中，水质数据的显示应该
												  //也用类似方法的
		}
		Sleep(TimeStep);   
	}
	return 0;
}

//子线程

//子线程函数，按下开始监测后，两个定时器启动，随即创建这个子线程，使得参数超标时，“本轮
//超标次数”编辑框改变值


//计算的函数，将CString 转化为十六进制数组，十六进制数组转为十进制数并计算指标值，与OnCommMscomm1有关





void CMFCApplication1Dlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnCbnSelchangeCombo5()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CMFCApplication1Dlg::OnCbnSelchangeCombo6()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CByteArray HexDataBuf;
	int i = 0;
	BYTE SendBuf[128] = { 0 };
	BYTE GetData[256] = { 0 };
	int SendLen = 0;
	int GetLen = 0;
	CString editsend1 = "08 04 00 00 00 06 70 91";//读取命令1
	CString editsend2 = "03 04 00 00 00 03 B1 E9";//读取命令2
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		
		HexDataBuf.RemoveAll();    //清空数组 
		GetLen = editsend1.GetLength();
		for (i = 0; i<GetLen; i++)
		{
			GetData[i] = (BYTE)editsend1.GetBuffer()[i];
		}
		StringtoHex(GetData, GetLen, SendBuf, &SendLen);//将字符串转化为字节数据

		HexDataBuf.SetSize(SendLen);   //设置数组大小为帧长度 
		for (i = 0; i<SendLen; i++)
		{
			HexDataBuf.SetAt(i, SendBuf[i]);
		}
		m_mscom.put_Output(COleVariant(HexDataBuf)); //发送十六进制数据
		break;
	case 2:
		
		HexDataBuf.RemoveAll();    //清空数组 
		GetLen = editsend2.GetLength();
		for (i = 0; i<GetLen; i++)
		{
			GetData[i] = (BYTE)editsend2.GetBuffer()[i];
		}
		StringtoHex(GetData, GetLen, SendBuf, &SendLen);//将字符串转化为字节数据

		HexDataBuf.SetSize(SendLen);   //设置数组大小为帧长度 
		for (i = 0; i<SendLen; i++)
		{
			HexDataBuf.SetAt(i, SendBuf[i]);
		}
		m_mscom.put_Output(COleVariant(HexDataBuf));
		break;
	case 3:
		total = _T("AT+NMGS=3,000000\r\n");

		m_mscom2.put_Output(COleVariant(total));

	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//定时器，与开始监测有关，内含

void CMFCApplication1Dlg::OnCommMscomm2()
{
	// TODO: 在此处添加消息处理程序代码
	byte rxdata2[1024] = { 0 };
	COleSafeArray fs2;
	VARIANT InputData2;
	long len2, k2;
	CString strtemp2;
	CString name;
	GetDlgItemText(IDC_BUTTON_SEND, name);
	CWnd *h3;
	h3 = GetDlgItem(IDC_BUTTON_SEND);
					// TODO: 在此处添加消息处理程序代码
	if (m_mscom2.get_CommEvent() == 2)
	{
		CString temp4,temp5;
		Sleep(100);
		InputData2 = m_mscom2.get_Input();
		fs2 = InputData2;
		len2 = fs2.GetOneDimSize();
		for (k2 = 0; k2 < len2; k2++)
		fs2.GetElement(&k2, rxdata2 + k2);
	    temp4= rxdata2;   
		temp5 = temp4.Mid(10, 8);
		//MessageBox(temp5);
		if (temp5 == "01000000")
		{
			m_NbiotReceive += temp5;
			k = 0;
			KillTimer(1);
			KillTimer(2);
			name = _T("开始监测");
			h3->SetWindowText(name);
			

		}
		else if (temp5 == "01000001")
		{
			m_NbiotReceive += temp5;
			if ((!m_mscom.get_PortOpen()) || (!m_mscom2.get_PortOpen()) || (!m_mscom3.get_PortOpen()))
			{
				CString str3;
				str3 = _T("未打开数据接受端串口，无法接收!");
				MessageBox(str3);
			}
			else
			{
				m_NbiotReceive += temp5;
				name = _T("停止监测");
				h3->SetWindowText(name);
				flag2 = 0; cap = 0; num = 0;
				editcap.Format("%02d", cap);
				editnum.Format("%02d", num);
				SetDlgItemText(IDC_EDITTimeStep, editTimeStep);
				SetDlgItemText(IDC_EDITnum, editnum);
				SetDlgItemText(IDC_EDITcap, editcap);
				
				flag1 = 0;
				m_NbiotSend = _T("ATI\r\n");
				m_mscom2.put_Output(COleVariant(m_NbiotSend));
				Sleep(50);
				m_NbiotSend = _T("AT+NCDP?\r\n");
				m_mscom2.put_Output(COleVariant(m_NbiotSend));
				Sleep(50);
				m_NbiotSend = _T("AT+NNMI=1\r\n");
				m_mscom2.put_Output(COleVariant(m_NbiotSend));
				SetTimer(1, TimeStep, NULL);
				Sleep(1000);
				SetTimer(2, TimeStep, NULL);
				CWinThread* pThread = AfxBeginThread(ThreadFun, this);
				k = 1;
			}
		}
		else if (temp5.Mid(0, 2) == "01")
		{
			m_NbiotReceive += temp5;
			editTimeStep = temp5.Mid(2, 4);
			char* temp7;
			temp7 = (LPSTR)(LPCSTR)editTimeStep;
			TimeStep = hex2dec(temp7);
			
			editTimeStep.Format("%02d", TimeStep);
			SetDlgItemText(IDC_EDITTimeStep, editTimeStep);
			TimeStep = TimeStep * 1000;
			KillTimer(1);
			KillTimer(2);
			SetTimer(1, TimeStep, NULL);
			Sleep(1000);
			SetTimer(2, TimeStep, NULL);
		}
		else 
		{ 
			m_NbiotReceive += temp4;
			this->SendDlgItemMessage(IDC_EDIT2, WM_VSCROLL, SB_BOTTOM, 0);
			
		}
		UpdateData(false);
	}
}

//与开始监测有关，数据上传端接收信息的函数，用来接收NBIot返回的信息

void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnChangeEditnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	if (cap < 4&&flag2>0)
	{
		int GetLen = 1; int i = 0;
		CByteArray charcommand ;
		char chOutput[1] = {'1'};
		charcommand.RemoveAll();          //clear
		charcommand.SetSize(GetLen);       //set lenght
		for (int i = 0; i < 1; i++)              //put data
			charcommand.SetAt(i, chOutput[i]);
		m_mscom3.put_Output(COleVariant(charcommand));
		cap+=1;
	}
	editcap.Format("%02d", cap);
	SetDlgItemText(IDC_EDITcap, editcap);
}
	
//editnum值改变，且采样次数小于4次时，则通过采样控制端再次发送采样指令
int getdecnumber(char ch)
{
	if (ch >= '0'&&ch <= '9') { return ch - '0'; }
	if (ch >= 'A'&&ch <= 'F') { return ch - 'A' + 10; }
	if (ch >= 'a'&&ch <= 'f') { return ch - 'a' + 10; }
	return -1;
}

int hex2dec(char*s)
{
	int len = strlen(s);
	int sum = 0; int t = 1;
	for (int i = len - 1; i >= 0; i--) {
		sum += t*getdecnumber(*(s + i));
		t *= 16;
	}
	return sum;
}

//CString转化为数组以后，用这个函数转化成十进制数，与OnCommMscomm1，各个result函数相关


//extern float feditdd, feditwd, feditry, feditzd, fedityd, feditph;
CString resultph(CString ori)
{
	char* temp7;
	float temp4; int temp3;
	temp7 = (LPSTR)(LPCSTR)ori;
	temp3 = hex2dec(temp7);
	//TRACE("%c", *(temp7 + 1));
	temp4 = temp3 / 1000.0;
	//TRACE("%f", temp4);
	feditph = temp4;
	CString temp5;
	temp5.Format("%.3f", temp4);
	return temp5;
}

CString resultzd(CString ori)
{
	char* temp7;
	double temp4; int temp3;
	temp7 = (LPSTR)(LPCSTR)ori;
	temp3 = hex2dec(temp7);
	//TRACE("%c", *(temp7 + 1));
	temp4 = temp3 / 10000.0;
	//TRACE("%f", temp4);
	feditzd = temp4;
	CString temp5;
	temp5.Format("%.3f", temp4);
	return temp5;
}

CString resultry(CString ori)
{
	char* temp7;
	float temp4; int temp3;
	temp7 = (LPSTR)(LPCSTR)ori;
	temp3 = hex2dec(temp7);
	//TRACE("%c", *(temp7 + 1));
	temp4 = temp3 / 1000.0;
	//TRACE("%f", temp4);
	feditry = temp4;
	CString temp5;
	temp5.Format("%.3f", temp4);
	return temp5;
}
CString resultyd(CString ori)
{
	char* temp7;
	float temp4; int temp3;
	temp7 = (LPSTR)(LPCSTR)ori;
	temp3 = hex2dec(temp7);
	//TRACE("%c", *(temp7 + 1));
	temp4 = temp3 / 1000.0;
	//TRACE("%f", temp4);
	fedityd = temp4;
	CString temp5;
	temp5.Format("%.3f", temp4);
	return temp5;
}
CString resultdd(CString oridd)//计算电导率
{
	char* temp7;
	float temp4; int temp3;
	temp7 = (LPSTR)(LPCSTR)oridd;
	temp3 = hex2dec(temp7);
	//TRACE("%c", *(temp7 + 1));
	temp4 = temp3 / 1.0;
	feditdd = temp4;
	//TRACE("%f", temp4);
	CString temp5;
	temp5.Format("%.f", temp4);
	return temp5;
}
CString resultwd(CString oriwd)//计算电导率
{
	char* temp7;
	float temp4; int temp3;
	temp7 = (LPSTR)(LPCSTR)oriwd;
	temp3 = hex2dec(temp7);
	//TRACE("%c", *(temp7 + 1));
	temp4 = temp3 / 100.0;
	TRACE("%f", temp4);
	feditwd = temp4;
	CString temp5;
	temp5.Format("%.2f", temp4);
	return temp5;
}