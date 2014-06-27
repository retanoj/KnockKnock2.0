// KnockKnockDlg.h : header file
//

#if !defined(AFX_KNOCKKNOCKDLG_H__79447D86_D96E_4F00_9B4F_00529E0FD191__INCLUDED_)
#define AFX_KNOCKKNOCKDLG_H__79447D86_D96E_4F00_9B4F_00529E0FD191__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKnockKnockDlg dialog

class CKnockKnockDlg : public CDialog
{
// Construction
public:
	CKnockKnockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKnockKnockDlg)
	enum { IDD = IDD_KNOCKKNOCK_DIALOG };
	CEdit	m_edtPort;
	CListBox	m_KnockSeq;
	CIPAddressCtrl	m_IP;
	CString		m_Port;
	//}}AFX_DATA

	//Font Color
	COLORREF m_color;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKnockKnockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKnockKnockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnUp();
	afx_msg void OnBtnDown();
	afx_msg void OnBtnRemove();
	afx_msg void OnBtnKnock();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	static const char *m_FileName;

	void SaveConfig();
	void ReadConfig();
	bool SendConnect(const char *ip, int port, CString sProtocol);
	void ReportError(int errorCode, const char *whichFunc);
public:
	afx_msg void OnEnSetfocusEdtPort();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KNOCKKNOCKDLG_H__79447D86_D96E_4F00_9B4F_00529E0FD191__INCLUDED_)
