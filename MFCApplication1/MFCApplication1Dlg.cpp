
// MFCApplication1Dlg.cpp : ʵ���ļ�
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
//CString��ʽ�Ķ�ȡ�������ÿ��������תΪһ��ʮ������������SB��

CString resultph(CString ori);
CString resultzd(CString ori);
CString resultyd(CString ori);
CString resultry(CString ori);
//�����������ζȣ�ph

CString resultdd(CString oridd);
//����絼��

CString resultwd(CString oriwd);
//�����¶�

int hex2dec(char*s);
//CStringת��Ϊ�����Ժ����������ת����ʮ������

int getdecnumber(char ch);
//hex2dec���Ӻ���

int num = 0; CString editnum = _T("00"); int i; int flag1; int flag2 = 0;//���ƴ򿪴���ʱ�����ܴ������仯
//���ּ�ⳬ����ܴ���
int cap = 0; CString editcap = _T("00");
//Ŀǰ�Ѳ����Ĵ���

//��ˮ�ʳ����Ҿ�����һ�β����Ѿ�����3�β������ٲ���

CString m_NbiotSend; int TimeStep = 10000; CString editTimeStep=_T("10");
//��ȡ���ݵ������ʱ����ʼ����

CString temp3, tempdd, tempwd, tempry, tempzd, tempyd, tempph, total;
//��NB_iot��������ʱ��Ҫ���ϵ�CString

//ģ��IMEI��868744031003381


UINT ThreadFun(LPVOID para);
//���̺߳��������¿�ʼ����������ʱ���������漴����������̣߳�ʹ�ò�������ʱ��������
//����������༭��ı�ֵ


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCApplication1Dlg �Ի���



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
	ON_WM_TIMER()//!!!��ʱ��
	//ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDITnum, &CMFCApplication1Dlg::OnChangeEditnum)
	//ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	//ON_EN_CHANGE(IDC_EDITwd, &CMFCApplication1Dlg::OnEnChangeEditwd)
	//ON_EN_CHANGE(IDC_EDITyd, &CMFCApplication1Dlg::OnEnChangeEdityd)
	//ON_EN_CHANGE(IDC_EDITph, &CMFCApplication1Dlg::OnEnChangeEditph)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	//ѡ�񴮿�
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

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//��ʼ�������������������ѡ�񴮿ڡ������ʵ����

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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_mscom.get_PortOpen())
	{
		m_mscom.put_PortOpen(false);
	}
	CDialogEx::OnCancel();

}

//�˳��ĺ���



int k=1;
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	CString name;
	GetDlgItemText(IDC_BUTTON_SEND,name);
	CWnd *h3;
	h3 = GetDlgItem(IDC_BUTTON_SEND);
	if (name == _T("��ʼ���"))
	{
		// TODO: �ڴ���ӿؼ�֪ͨ����������
		if ((!m_mscom.get_PortOpen()) || (!m_mscom2.get_PortOpen()) || (!m_mscom3.get_PortOpen()))
		{
			CString str3;
			str3 = _T("δ�����ݽ��ܶ˴��ڣ��޷�����!");
			MessageBox(str3);
		}
		else
		{   
			name = _T("ֹͣ���");
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
	else if (name == _T("ֹͣ���"))
		{
		    k = 0;
			KillTimer(1);
			KillTimer(2);
			name = _T("��ʼ���");
			h3->SetWindowText(name);
		}
	
}//��ʼ���ĺ��������°���������������ʱ��

	//���ƿ�ʼ��⡢ֹͣ���ĺ���


void StringtoHex(BYTE *GB, int glen, BYTE* SB, int* slen)
{
	int i; //����������ַ���
	int a = 0;
	char temp; //�����ַ��������ж��Ƿ�Ϊ�ո�����������
	char temp1, temp2; //����һ���ֽڵ������ַ� ����EB����temp1='E',temp2 = 'B'
	*slen = 0; //�����16�����ַ�������
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

////CString��ʽ�Ķ�ȡ�������ÿ��������תΪһ��ʮ������������SB�У��뿪ʼ��ֹͣ������

void CMFCApplication1Dlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnCbnSelchangeCombo2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str, str11,str12,str13, n;///
	CWnd *h1;
	h1 = GetDlgItem(IDC_BUTTON_OPEN);//h1���򿪴��ڵİ�ť
	GetDlgItemText(IDC_BUTTON_OPEN, str);//��ť�ϵ�����
	//���δ���������
	
	if (str==_T("�򿪴���"))
	{
		if (m_mscom.get_PortOpen())
		{
			m_mscom.put_PortOpen(false);//�򿪴���
		}
			comb2.GetLBText(comb2.GetCurSel(), str11);
			str11 = str11 + ',' + 'n' + ',' + '8' + ',' + '1';
			m_mscom.put_Settings(str11);//���ò�����

			m_mscom.put_CommPort((m_comb1.GetCurSel() + 1));  //ѡ�񴮿�

			m_mscom.put_InputMode(1);
			m_mscom.put_InputLen(1024);
			m_mscom.put_RThreshold(1);
			m_mscom.put_RTSEnable(1);//���������룬�������ݳ��ȣ�һ���ַ������¼���RT����

			m_mscom.put_PortOpen(true);//�򿪴���


		if (m_mscom2.get_PortOpen())
		{
			m_mscom2.put_PortOpen(false);
		}
			comb4.GetLBText(comb4.GetCurSel(), str12);
			str12 = str12 + ',' + 'n' + ',' + '8' + ',' + '1';
			m_mscom2.put_Settings(str12);//���ò�����

			m_mscom2.put_CommPort((comb3.GetCurSel() + 1));  //ѡ�񴮿�

			m_mscom2.put_InputMode(1); 
			m_mscom2.put_InputLen(1024);
			m_mscom2.put_RThreshold(1);
			m_mscom2.put_RTSEnable(1);//���������룬�������ݳ��ȣ�һ���ַ������¼���RT����

			m_mscom2.put_PortOpen(true);//�򿪴���
		
			if (m_mscom3.get_PortOpen())
			{
				m_mscom3.put_PortOpen(false);
			}
			comb6.GetLBText(comb6.GetCurSel(), str13);
			str13 = str13 + ',' + 'n' + ',' + '8' + ',' + '1';
			m_mscom3.put_Settings(str13);//���ò�����

			m_mscom3.put_CommPort((comb5.GetCurSel() + 1));  //ѡ�񴮿�

			m_mscom3.put_InputMode(1);
			m_mscom3.put_InputLen(1024);
			m_mscom3.put_RThreshold(1);
			m_mscom3.put_RTSEnable(1);//���������룬�������ݳ��ȣ�һ���ַ������¼���RT����

			m_mscom3.put_PortOpen(true);//�򿪴���


		if ((m_mscom2.get_PortOpen())&& (m_mscom.get_PortOpen())&& (m_mscom3.get_PortOpen()))
		{
			str = _T("�رմ���");
			UpdateData(true);
			h1->SetWindowText(str);
			SetTimer(3, Moniter, NULL);
		}
		/*else
		{
			m_mscom.put_PortOpen(false);
			if (str != _T("�򿪴���"))
			{
				str = _T("�򿪴���");
				UpdateData(true);//�ؼ���ֵ������Ա����
				h1->SetWindowText(str);
			}
		}*/
	}
	else if(str == _T("�رմ���"))
	{
		m_mscom.put_PortOpen(false);
		m_mscom2.put_PortOpen(false);
		m_mscom3.put_PortOpen(false);
		if ((!m_mscom2.get_PortOpen()) && (!m_mscom.get_PortOpen()) && (!m_mscom3.get_PortOpen()))
		{
			str = _T("�򿪴���");
			KillTimer(3);
			//UpdateData(true);//�ؼ���ֵ������Ա����
			h1->SetWindowText(str);
		}
	}
}
	
//�򿪡��رմ��ڵĺ���

BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnCommMscomm1, VTS_NONE)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM2, 1, CMFCApplication1Dlg::OnCommMscomm2, VTS_NONE)
END_EVENTSINK_MAP()


//hex2dec�Ӻ���

CString temp2, temp; long L; CString editdd, editwd, editry, editzd, edityd, editph;
float feditdd = 0.0, feditwd = 0.0, feditry = 0.0, feditzd = 0.0, fedityd = 0.0, feditph = 0.0;

//temp,temp2����Ϣ�������õ���֮��6��CString������������,float�������߳����ж��Ƿ񳬱�

void CMFCApplication1Dlg::OnCommMscomm1()
{
	byte rxdata[1024] = { 0 };
	COleSafeArray fs;
	VARIANT InputData;
	long len, k; 
	CString strtemp;//!!!!!
	// TODO: �ڴ˴������Ϣ����������
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
				//CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)para;//����Dialog���ݹ���
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
					editwd = resultwd(tempwd) + "��";
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

//��Ϣ����������temp2�н��������ݣ���ת�������㣬�Ӻ���result

UINT ThreadFun(LPVOID para)
{
	Sleep(13000);
	CMFCApplication1Dlg* pDlg = (CMFCApplication1Dlg*)para;//����Dialog���ݹ���
	while (k)
	{
		if ((feditdd > 3000.0) || ((feditph > 8.5) || ((feditph < 6.5) && (feditph != 0.0))) || ((feditwd >40.0) || ((feditwd < 10.0) && (feditwd != 0.0))) || (feditry > 8.9) || (fedityd > 1.5))
		{
			
			num += 1; flag2 = 1;
			editnum.Format("%02d", num);
			pDlg->SetDlgItemText(IDC_EDITnum, editnum);//�������ֱ�Ӱ�int��ʾ�ڱ༭���У�ˮ�����ݵ���ʾӦ��
												  //Ҳ�����Ʒ�����
		}
		Sleep(TimeStep);   
	}
	return 0;
}

//���߳�

//���̺߳��������¿�ʼ����������ʱ���������漴����������̣߳�ʹ�ò�������ʱ��������
//����������༭��ı�ֵ


//����ĺ�������CString ת��Ϊʮ���������飬ʮ����������תΪʮ������������ָ��ֵ����OnCommMscomm1�й�





void CMFCApplication1Dlg::OnCbnSelchangeCombo3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnCbnSelchangeCombo5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CMFCApplication1Dlg::OnCbnSelchangeCombo6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CByteArray HexDataBuf;
	int i = 0;
	BYTE SendBuf[128] = { 0 };
	BYTE GetData[256] = { 0 };
	int SendLen = 0;
	int GetLen = 0;
	CString editsend1 = "08 04 00 00 00 06 70 91";//��ȡ����1
	CString editsend2 = "03 04 00 00 00 03 B1 E9";//��ȡ����2
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		
		HexDataBuf.RemoveAll();    //������� 
		GetLen = editsend1.GetLength();
		for (i = 0; i<GetLen; i++)
		{
			GetData[i] = (BYTE)editsend1.GetBuffer()[i];
		}
		StringtoHex(GetData, GetLen, SendBuf, &SendLen);//���ַ���ת��Ϊ�ֽ�����

		HexDataBuf.SetSize(SendLen);   //���������СΪ֡���� 
		for (i = 0; i<SendLen; i++)
		{
			HexDataBuf.SetAt(i, SendBuf[i]);
		}
		m_mscom.put_Output(COleVariant(HexDataBuf)); //����ʮ����������
		break;
	case 2:
		
		HexDataBuf.RemoveAll();    //������� 
		GetLen = editsend2.GetLength();
		for (i = 0; i<GetLen; i++)
		{
			GetData[i] = (BYTE)editsend2.GetBuffer()[i];
		}
		StringtoHex(GetData, GetLen, SendBuf, &SendLen);//���ַ���ת��Ϊ�ֽ�����

		HexDataBuf.SetSize(SendLen);   //���������СΪ֡���� 
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

//��ʱ�����뿪ʼ����йأ��ں�

void CMFCApplication1Dlg::OnCommMscomm2()
{
	// TODO: �ڴ˴������Ϣ����������
	byte rxdata2[1024] = { 0 };
	COleSafeArray fs2;
	VARIANT InputData2;
	long len2, k2;
	CString strtemp2;
	CString name;
	GetDlgItemText(IDC_BUTTON_SEND, name);
	CWnd *h3;
	h3 = GetDlgItem(IDC_BUTTON_SEND);
					// TODO: �ڴ˴������Ϣ����������
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
			name = _T("��ʼ���");
			h3->SetWindowText(name);
			

		}
		else if (temp5 == "01000001")
		{
			m_NbiotReceive += temp5;
			if ((!m_mscom.get_PortOpen()) || (!m_mscom2.get_PortOpen()) || (!m_mscom3.get_PortOpen()))
			{
				CString str3;
				str3 = _T("δ�����ݽ��ܶ˴��ڣ��޷�����!");
				MessageBox(str3);
			}
			else
			{
				m_NbiotReceive += temp5;
				name = _T("ֹͣ���");
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

//�뿪ʼ����йأ������ϴ��˽�����Ϣ�ĺ�������������NBIot���ص���Ϣ

void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnChangeEditnum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
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
	
//editnumֵ�ı䣬�Ҳ�������С��4��ʱ����ͨ���������ƶ��ٴη��Ͳ���ָ��
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

//CStringת��Ϊ�����Ժ����������ת����ʮ����������OnCommMscomm1������result�������


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
CString resultdd(CString oridd)//����絼��
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
CString resultwd(CString oriwd)//����絼��
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