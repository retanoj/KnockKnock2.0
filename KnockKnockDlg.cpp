// KnockKnockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KnockKnock.h"
#include "KnockKnockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char * CKnockKnockDlg::m_FileName = "knockknock.cfg";

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKnockKnockDlg dialog

CKnockKnockDlg::CKnockKnockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKnockKnockDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKnockKnockDlg)
	//m_Port = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKnockKnockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKnockKnockDlg)
	DDX_Control(pDX, IDC_EDT_PORT, m_edtPort);
	DDX_Control(pDX, IDC_LST_KNOCKSEQ, m_KnockSeq);
	DDX_Control(pDX, IDC_IPADDRESS, m_IP);
	DDX_Text(pDX, IDC_EDT_PORT, m_Port);
	//DDV_MinMaxInt(pDX, m_Port, 1, 65535);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKnockKnockDlg, CDialog)
	//{{AFX_MSG_MAP(CKnockKnockDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_UP, OnBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, OnBtnDown)
	ON_BN_CLICKED(IDC_BTN_REMOVE, OnBtnRemove)
	ON_BN_CLICKED(IDC_BTN_KNOCK, OnBtnKnock)
	//}}AFX_MSG_MAP	
	ON_EN_SETFOCUS(IDC_EDT_PORT, &CKnockKnockDlg::OnEnSetfocusEdtPort)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKnockKnockDlg message handlers

BOOL CKnockKnockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_edtPort.SetWindowText("8080:udp");
	m_color = RGB(128,128,128);

	ReadConfig();	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKnockKnockDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKnockKnockDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKnockKnockDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKnockKnockDlg::OnBtnExit() 
{
	SaveConfig();

	CDialog::OnCancel();	
}

void CKnockKnockDlg::OnBtnAdd() 
{
	if (!UpdateData())
		return;
	
	CString tmp;
	tmp.Format("%s", m_Port);
	tmp = tmp.MakeLower();
	m_KnockSeq.AddString(tmp);
	m_KnockSeq.SetCurSel(m_KnockSeq.GetCount()-1);

	m_edtPort.SetWindowText("");
	m_edtPort.SetFocus();
}

void CKnockKnockDlg::OnBtnUp() 
{
	int index = m_KnockSeq.GetCurSel();

	if (index <= 0)
		return;

	CString tmp;
	m_KnockSeq.GetText(index, tmp);
	m_KnockSeq.DeleteString(index);
	m_KnockSeq.InsertString(index-1, tmp);
	m_KnockSeq.SetCurSel(index-1);
}

void CKnockKnockDlg::OnBtnDown() 
{
	int index = m_KnockSeq.GetCurSel();

	if (index < 0 || index == m_KnockSeq.GetCount()-1)
		return;

	CString tmp;
	m_KnockSeq.GetText(index, tmp);
	m_KnockSeq.DeleteString(index);
	m_KnockSeq.InsertString(index+1, tmp);
	m_KnockSeq.SetCurSel(index+1);	
}

void CKnockKnockDlg::OnBtnRemove() 
{
	int index = m_KnockSeq.GetCurSel();

	if (index < 0)
		return;

	m_KnockSeq.DeleteString(index);

	if (index == m_KnockSeq.GetCount())
		m_KnockSeq.SetCurSel(index-1);	
	else
		m_KnockSeq.SetCurSel(index);
}

void CKnockKnockDlg::OnBtnKnock() 
{
	CString ip;
	m_IP.GetWindowText(ip);	

	int cnt = m_KnockSeq.GetCount();
	if (cnt == 0) {
		AfxMessageBox("Please specify the knock sequence!");
		m_edtPort.SetFocus();
		return;
	}
	
	CString tmp;
	CString sPort;
	CString sProtocol;
	int i;

	for (i = 0; i < cnt; i++) {
		m_KnockSeq.GetText(i, tmp);
		AfxExtractSubString(sPort, tmp, 0, ':');
		AfxExtractSubString(sProtocol, tmp, 1, ':');
		if (!SendConnect(ip, atoi(sPort), sProtocol))
			break;
		Sleep(600);
	}

	if (i == cnt) // succeed
		AfxMessageBox("Knock done!");
	else // fail
		AfxMessageBox("Knock Error!");
}

void CKnockKnockDlg::SaveConfig() {
	CStdioFile f(m_FileName, CFile::modeWrite | CFile::modeCreate);

	CString tmp;
	m_IP.GetWindowText(tmp);
	tmp += "\n";
	f.WriteString(tmp);

	int cnt = m_KnockSeq.GetCount();
	unsigned int port;
	//int r;
	char r[5] = "----";
	for (int i = 0; i < cnt; i++) {
		//r = rand();
		f.Write(r, 4);

		m_KnockSeq.GetText(i, tmp);
		//port = atoi(tmp);
		//f.Write(&port, sizeof(port));
		tmp += "\n";
		f.WriteString(tmp);
	}

	f.Close();
}

void CKnockKnockDlg::ReadConfig() {
	CStdioFile f;
	if (!f.Open(m_FileName, CFile::modeRead | CFile::typeBinary))
		return;

	
	CString tmp;
	f.ReadString(tmp);
	m_IP.SetWindowText(tmp);

	//int r;
	char r[5];
	unsigned int port;	
	while (f.Read(r, 4) == 4) {
		//f.Read(&port, sizeof(port));	
		//tmp.Format("%d", port);
		f.ReadString(tmp);
		tmp.Replace('\r',0);
		tmp.Replace('\n',0);
		m_KnockSeq.AddString(tmp);
	}
	

	f.Close();
}

bool CKnockKnockDlg::SendConnect(const char *ip, int port, CString sProtocol) {
	int nret;
	LPHOSTENT hostEntry; // To store information about the server
	//in_addr iaHost;
	SOCKET theSocket;
	SOCKADDR_IN serverInfo;
	unsigned long nonBlock = 1;

	CString csTCP("tcp");
	CString csUDP("udp");

	//hostEntry = gethostbyname("www.hal-pc.org");	// Specifying the server by its name;
	// another option is gethostbyaddr() (see below)
	/*
	iaHost.s_addr = inet_addr(ip);
	
	hostEntry = gethostbyaddr((const char *)&iaHost, sizeof(struct in_addr), AF_INET);
	
	if (hostEntry == NULL)
	{
		nret = WSAGetLastError();
		ReportError(nret, "gethostbyaddr()");	// Report the error
		WSACleanup();
		return false;
	}
	*/

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = inet_addr(ip);
	//serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(port);	//Change to network-byte order

	// Create the socket
	if (sProtocol.MakeLower().Compare(csTCP) == 0){
		theSocket = socket(PF_INET,		// Go over TCP/IP
			SOCK_STREAM,				// This is a stream-oriented socket
			IPPROTO_TCP);				// Use TCP rather than UDP

		if (theSocket == INVALID_SOCKET)
		{
			nret = WSAGetLastError();
			ReportError(nret, "socket()");
			WSACleanup();
			return false;
		}

		/* Set the socket to nonblocking */
		if (ioctlsocket(theSocket, FIONBIO, &nonBlock) == SOCKET_ERROR)
		{
			nret = WSAGetLastError();
			ReportError(nret, "ioctlsocket()");
			WSACleanup();
			return false;
		}
		
		// Connect to the server
		connect(theSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
	}
	else if (sProtocol.MakeLower().Compare(csUDP) == 0){
		theSocket = socket(PF_INET,		// Go over TCP/IP
			SOCK_DGRAM,			
			IPPROTO_UDP);				// Use UDP
		
		if (theSocket == INVALID_SOCKET)
		{
			nret = WSAGetLastError();
			ReportError(nret, "socket()");
			WSACleanup();
			return false;
		}

		// Send sth to the server
		sendto(theSocket,"",1,0,(SOCKADDR*)&serverInfo,sizeof(struct sockaddr));
	}
	else{
		return false;
	}
	
	closesocket(theSocket);

	return true;
}

void CKnockKnockDlg::ReportError(int errorCode, const char *whichFunc) {
   CString tmp;
   tmp.Format("Call to %s returned error %d", whichFunc, errorCode);
   AfxMessageBox(tmp);
}


void CKnockKnockDlg::OnEnSetfocusEdtPort()
{
	// TODO: 在此添加控件通知处理程序代码
	m_color = RGB(0,0,0);
	m_edtPort.SetRedraw(true);
	m_edtPort.SetWindowText("");
}


HBRUSH CKnockKnockDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if(nCtlColor==CTLCOLOR_EDIT && pWnd->GetDlgCtrlID()==IDC_EDT_PORT){
		pDC->SetTextColor(m_color);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CKnockKnockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && pMsg->hwnd == ((CEdit*)GetDlgItem(IDC_EDT_PORT))->m_hWnd){
		OnBtnAdd();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}