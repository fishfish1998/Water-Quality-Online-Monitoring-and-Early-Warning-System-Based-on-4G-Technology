
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
//	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
private:
//	CString editwd;
//	CString editry;
//	CString editph;
//	CString editzd;
//	CString editdd;
//	CString edityd;
	CComboBox m_comb1;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox comb2;
	afx_msg void OnBnClickedButtonOpen();
	CMscomm1 m_mscom;
//	CString editsend;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
private:
//	CString edittest;
public:
	CMscomm1 m_mscom2;
	CMscomm1 m_mscom3;
	afx_msg void OnCbnSelchangeCombo6();
	afx_msg void OnCbnSelchangeCombo3();
private:
	CComboBox comb3;
public:
	CComboBox comb4;
	afx_msg void OnCbnSelchangeCombo5();
	CComboBox comb5;
	CComboBox comb6;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnCommMscomm2();
private:
	CString m_NbiotReceive;
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnChangeEditnum();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEditwd();
	afx_msg void OnEnChangeEdityd();
	afx_msg void OnEnChangeEditph();
private:
	CString ccc;
};
