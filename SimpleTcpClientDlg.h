// SimpleTcpClientDlg.h : header file
//

#if !defined(AFX_SIMPLETCPCLIENTDLG_H__59F83987_2D03_11D6_AA7C_00C026A39668__INCLUDED_)
#define AFX_SIMPLETCPCLIENTDLG_H__59F83987_2D03_11D6_AA7C_00C026A39668__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimpleTcpClientDlg dialog

class CSimpleTcpClientDlg : public CDialog
{
// Construction
public:
	static UINT StartDownload(LPVOID pParam );
	bool DownloadFile(CString username,CString valueStr);
	void ParseURL(CString url, CString& server, CString& filepath, CString& filename);
	bool GetGold(CString goldAddress);
	CString HttpPostUP(CString urlStr, CString valueStr);
	bool GetAndSetCookie(CString orgHtml);
	CSimpleTcpClientDlg(CWnd* pParent = NULL);	// standard constructor
	
	
	// Dialog Data
	//{{AFX_DATA(CSimpleTcpClientDlg)
	enum { IDD = IDD_SIMPLETCPCLIENT_DIALOG };
	CListBox	m_list;
	CString	m_url;
	CString	m_gold;
	CString	m_cookies;
	CString	m_username;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleTcpClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSimpleTcpClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLETCPCLIENTDLG_H__59F83987_2D03_11D6_AA7C_00C026A39668__INCLUDED_)
