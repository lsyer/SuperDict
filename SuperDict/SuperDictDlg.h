// SuperDictDlg.h : header file
//

#if !defined(AFX_SUPERDICTDLG_H__5A9C0E91_9ED4_4ACC_B4D6_F7132244AC88__INCLUDED_)
#define AFX_SUPERDICTDLG_H__5A9C0E91_9ED4_4ACC_B4D6_F7132244AC88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CContentDlg dialog used for App Content

class CContentDlg : public CDialog
{
public:
	CContentDlg();

// Dialog Data
	//{{AFX_DATA(CContentDlg)
	enum { IDD = IDD_CONTENTDLG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CContentDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HBRUSH sbrush;
	CFont font;
};

////////////////////////////////////////////////////////////////////////////
// SuperDictDlg dialog

class SuperDictDlg : public CDialog
{
// Construction
public:
	SuperDictDlg(CWnd* pParent = NULL);	// standard constructor
	~SuperDictDlg();

// Dialog Data
	//{{AFX_DATA(SuperDictDlg)
	enum { IDD = IDD_SUPERDICT_DIALOG };
	CEdit	m_editresult;
	BOOL	m_bEnableMouseCap;
	BOOL	m_bEnableHighlight;
	BOOL	m_bEnableHotkeyCap;
	BOOL	m_bEnableDBClickCap;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SuperDictDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
	static SuperDictDlg* pThis;
	static HRESULT	WINAPI CaptureText(long wParam, long lParam);
	static HRESULT	WINAPI CaptureHighlightText(long wParam, long lParam);
	static HRESULT	WINAPI MoniterMouseEvent(long wParam, long lParam);
	bool m_hotSign; // TRUE:show; FALSE:hide.
	CContentDlg cdlg;
	POINT ptCursor;
	_ConnectionPtr  m_pConnection;
	_RecordsetPtr   m_pRecordset;
	void GetAnswer(CString &searchStr,CString &result);
	void SeperateByChar(char c,int pos,CString &str);

	// Implementation
protected:
	HICON				m_hIcon;

private:
	// Generated message map functions
	//{{AFX_MSG(SuperDictDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnCheckMouseCap();
	afx_msg void OnCheckHotkeyCap();
	afx_msg void OnCheckHighlightCap();
	afx_msg void OnCheckDBClickCap();
	afx_msg void OnSetDlg();
	afx_msg void OnInstallPlugin();
	afx_msg void OnAbout();
	//}}AFX_MSG
	afx_msg LRESULT DealHotKey(WPARAM wParam, LPARAM lParam);			   //自定义系统热键
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERDICTDLG_H__5A9C0E91_9ED4_4ACC_B4D6_F7132244AC88__INCLUDED_)
