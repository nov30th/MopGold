/*

  Author :- Nish [BusterBoy]
  EMail :- nishinapp@yahoo.com
  WWW :- http://www.busterboy.org

  */
#include "stdafx.h"
#include "SimpleTcpClient.h"
#include "SimpleTcpClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_SIMPLETCPCLIENT_DIALOG };
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
// CSimpleTcpClientDlg dialog

CSimpleTcpClientDlg::CSimpleTcpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleTcpClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleTcpClientDlg)
	m_url = _T("");
	m_gold = _T("");
	m_cookies = _T("");
	m_username = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleTcpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleTcpClientDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_url);
	DDX_Text(pDX, IDC_GOLD, m_gold);
	DDX_Text(pDX, IDC_EDIT2, m_cookies);
	DDX_Text(pDX, IDC_EDIT3, m_username);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleTcpClientDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleTcpClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleTcpClientDlg message handlers

BOOL CSimpleTcpClientDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	WSADATA wsaData;
	int wsaret=WSAStartup(0x101,&wsaData);
	if(wsaret)	
		exit(1);
	m_url="7176563";
	m_cookies = "javascript:document.write(document.cookie);";
	UpdateData(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleTcpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleTcpClientDlg::OnPaint() 
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
HCURSOR CSimpleTcpClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSimpleTcpClientDlg::ParseURL(CString m_url, CString &server, CString &filepath, CString &filename)
{
	int n;
	CString url=m_url;
	if(url.Left(7)=="http://")
		url=url.Mid(7);
	n=url.Find('/');
	server=url.Left(n);
	filepath=url.Mid(n);
	n=filepath.ReverseFind('/');
	filename=filepath.Right(filepath.GetLength()-(n+1));

}

bool CSimpleTcpClientDlg::DownloadFile(CString username,CString valueStr)
{
	UpdateData(true);
	m_username = username;
	char buffresult[10240];
	unsigned long seekresult = 0;
	char buff[5120];
	CString s;
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	CString servername; 
	CString filepath;
	CString filename;	
	ParseURL("http://search2.mop.com/treasures/getonejs.jsp?sid=" + m_url,servername,filepath,filename);
	SOCKET conn;
	conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(conn==INVALID_SOCKET)
		return false;
	if(inet_addr(servername)==INADDR_NONE)
	{
		hp=gethostbyname(servername);
	}
	else
	{
		addr=inet_addr(servername);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	if(hp==NULL)
	{
		closesocket(conn);
		return false;
	}
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(80);
	if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
	{
		closesocket(conn);
		return false;	
	}
	sprintf(buff,"GET %s HTTP/1.1\r\n\
Accept: */*\r\n\
Accept-Language: zh-cn\r\n\
UA-CPU: x86\r\n\
Accept-Encoding: gzip, deflate\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727; InfoPath.1) \r\n\
Host: %s\r\n\
Connection: Close\r\n\
Cookie: %s\r\n\r\n",filepath,servername,m_cookies);
	send(conn,buff,strlen(buff),0);
	int y;
	while(y=recv(conn,buff,512,0))
	{
		memcpy(buffresult+seekresult,buff,y);
		//f.Write(buff,y);
		seekresult += y;
	}
	buffresult[seekresult]='\0';
	//AfxMessageBox(buffresult);
	closesocket(conn);
	s.Format("%s",buffresult);
	//m_cookies = s.Mid(s.Find("Set-Cookie: ") + 12 , s.Find("\r\n" , s.Find("Cookie: ") + 12) - s.Find("Cookie: ") - 12);
	//s.MakeLower();
	UpdateData(false);
	if (s.Find("JSESSIONID=") >1)
	{
		unsigned long seekcookiestart = s.Find("JSESSIONID=");
		unsigned long seekcookieend = s.Find("; ",seekcookiestart);
		m_cookies += s.Mid(seekcookiestart,seekcookieend - seekcookiestart + 2);
	}
	if (s.Find("gold") < 1)
		return true;
	else
	{
		//找到金币并开始行动
		unsigned long strbeginpos = s.Find("http://search2.mop.com/treasures/addGoldItem.jsp");
		unsigned long strendpos = s.Find("\"",strbeginpos);
		//AfxMessageBox(s.Mid(strbeginpos,strendpos-strbeginpos));
		return GetGold(s.Mid(strbeginpos,strendpos-strbeginpos));
	}
}

void CSimpleTcpClientDlg::OnOK() 
{	
	m_list.ResetContent();
	UpdateData(true);
	m_gold = "0";
	UpdateData(false);
	AfxBeginThread(StartDownload,this);
}


UINT CSimpleTcpClientDlg::StartDownload(LPVOID pParam )
{
	CSimpleTcpClientDlg* pDlg=(CSimpleTcpClientDlg*)pParam;
	//pDlg->DownloadFile();
	CStdioFile fp;
	if (!fp.Open("mop_nov30th.txt",CFile::modeRead))
	{
		AfxMessageBox("请将用户名密码文件(mop_nov30th.txt)放在和程序同一目录下.");
		return 0;
	}
	CString username,password;
	while(fp.ReadString(username))
	{
		if (!fp.ReadString(password))
			return 0;
		CString tempCookie;
		tempCookie = pDlg->HttpPostUP("http://passport.mop.com/Login?url=a","flag=1&user_name=" + username + "&password=" + password + "&submit=submit");
		pDlg->GetAndSetCookie(tempCookie);
		while(pDlg->DownloadFile(username,""))
			NULL;
	}
	fp.Close();
	return 0;
}

void CSimpleTcpClientDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	::ShellExecute(NULL,"open","http://www.nov30th.com/blog/mop刷金币.html",NULL,NULL,SW_SHOW);
}

bool CSimpleTcpClientDlg::GetGold(CString goldAddress)
{

	char buffresult[10240];
	unsigned long seekresult = 0;
	char buff[512];
	CString s;
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	CString servername; 
	CString filepath;
	CString filename;	
	ParseURL(goldAddress,servername,filepath,filename);
	SOCKET conn;
	conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(conn==INVALID_SOCKET)
		return false;
	if(inet_addr(servername)==INADDR_NONE)
	{
		hp=gethostbyname(servername);
	}
	else
	{
		addr=inet_addr(servername);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	if(hp==NULL)
	{
		closesocket(conn);
		return false;
	}
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(80);
	if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
	{
		closesocket(conn);
		return false;	
	}
	sprintf(buff,"GET %s HTTP/1.1\r\n\
Accept: */*\r\n\
Accept-Language: zh-cn\r\n\
UA-CPU: x86\r\n\
Accept-Encoding: gzip, deflate\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727; InfoPath.1) \r\n\
Host: %s\r\n\
Connection: Close\r\n\
Cookie: %s\r\n\r\n",filepath,servername,m_cookies);
	send(conn,buff,strlen(buff),0);
	s.Format("GOLD CATCHING.....");
	m_list.AddString(s);
	int y;
	while(y=recv(conn,buff,512,0))
	{
		memcpy(buffresult+seekresult,buff,y);
		//f.Write(buff,y);
		seekresult += y;
	}
	buffresult[seekresult]='\0';
	//AfxMessageBox(buffresult);
	closesocket(conn);
	s.Format("%s",buffresult);
	//m_cookies = s.Mid(s.Find("Set-Cookie: ") + 12 , s.Find("\r\n" , s.Find("Cookie: ") + 12) - s.Find("Cookie: ") - 12);
	//s.MakeLower();
	if (s.Find("您获得了一个小金币") < 1)
	{
		s.MakeLower();
		m_list.AddString(s.Mid(s.Find("<p>")+3));
		return false;
	}
	m_gold.Format("%d",atoi(m_gold)+1);
	m_url.Format("%ld",atol(m_url)+1);
	m_list.AddString(_T("Gold catch(ed)."));
	UpdateData(false);
	return true;
}


CString CSimpleTcpClientDlg::HttpPostUP(CString urlStr, CString valueStr)
{

	char buffresult[10240];
	unsigned long seekresult = 0;
	char buff[512];
	CString s;
	struct hostent *hp;
	unsigned int addr;
	struct sockaddr_in server;
	CString servername; 
	CString filepath;
	CString filename;	
	ParseURL(urlStr,servername,filepath,filename);
	SOCKET conn;
	conn=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(conn==INVALID_SOCKET)
		return "failed";
	if(inet_addr(servername)==INADDR_NONE)
	{
		hp=gethostbyname(servername);
	}
	else
	{
		addr=inet_addr(servername);
		hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);
	}
	if(hp==NULL)
	{
		closesocket(conn);
		return "failed";
	}
	server.sin_addr.s_addr=*((unsigned long*)hp->h_addr);
	server.sin_family=AF_INET;
	server.sin_port=htons(80);
	if(connect(conn,(struct sockaddr*)&server,sizeof(server)))
	{
		closesocket(conn);
		return "failed";	
	}
	s.Format("Login to server...");
	m_list.AddString(s);
	sprintf(buff,"POST %s HTTP/1.1\r\n\
Accept: */*\r\n\
Accept-Language: zh-cn\r\n\
Content-Type: application/x-www-form-urlencoded\r\n\
UA-CPU: x86\r\n\
Accept-Encoding: gzip, deflate\r\n\
User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.2; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727; InfoPath.1) \r\n\
Host: %s\r\n\
Content-Length: %d\r\n\
Connection: Close\r\n\
Cache-Control: no-cache \r\n\r\n\
%s",filepath,servername,valueStr.GetLength(),valueStr);
	send(conn,buff,strlen(buff),0);
	int y;
	while(y=recv(conn,buff,512,0))
	{
		memcpy(buffresult+seekresult,buff,y);
		seekresult += y;
	}
	buffresult[seekresult]='\0';
	//AfxMessageBox(buffresult);
	s.Format("Logined.");
	m_list.AddString(s);
	closesocket(conn);
	s.Format("%s",buffresult);
	return s;
}


bool CSimpleTcpClientDlg::GetAndSetCookie(CString orgHtml)
{
	UpdateData(true);
	m_cookies.Empty();
	//CString tempStr;
	unsigned long seekcookiestart=0;
	unsigned long seekcookieend=0;
	while(1)
	{
		seekcookiestart = orgHtml.Find("Set-Cookie: ",seekcookiestart);
		if (seekcookiestart <1 || seekcookiestart > 10000)
			break;
		seekcookiestart += 12;
		seekcookieend = orgHtml.Find("; ",seekcookiestart);
		m_cookies += orgHtml.Mid(seekcookiestart,seekcookieend - seekcookiestart) + "; ";
		//tempStr = orgHtml.Mid(seekcookiestart,seekcookieend - seekcookiestart) + "; ";
	}
	//AfxMessageBox(m_cookies);
	UpdateData(false);
	return true;
}
