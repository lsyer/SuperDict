// VC6DemoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "SuperDict.h"
#include "SuperDictDlg.h"
#include "Getword_Misc.h"
#include "LicenseID.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define HOTKEY_SHOW_HIDE				1000    // the hotkey message
#define HOTKEY_EN_DBLCLICKCAP			1001    // the hotkey message

/////////////////////////////////////////////////////////////////////////////
// CContentDlg dialog used for App Content

CContentDlg::CContentDlg() : CDialog(CContentDlg::IDD)
{
	//{{AFX_DATA_INIT(CContentDlg)
	//}}AFX_DATA_INIT

	sbrush = NULL;
}

BOOL CContentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowLong(this->GetSafeHwnd(),
				  GWL_EXSTYLE, 
				  GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)| 0x80000);  //设定窗体使用扩展模式 
	COLORREF maskColor = RGB(255,255,255);   //掩码颜色
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)
			fun(this->GetSafeHwnd(),maskColor,255,1);
		FreeLibrary(hInst); 
	}
	//SetLayeredWindowAttributes(maskColor,255,1);

	//设置字体
	font.CreatePointFont(10*10,_T("黑体"));
	GetDlgItem(IDC_EDIT1)->SetFont(&font,TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

HBRUSH CContentDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
 
    // TODO:  在此更改 DC 的任何特性
    // 
	if(sbrush)
	{
		DeleteObject(sbrush);
	}
    if(nCtlColor == CTLCOLOR_DLG)   //此处设置为窗体透明，CTLCOLOR_DLG表示对话框
    {
		sbrush = CreateSolidBrush(RGB(255,255,255)); 
		return sbrush;
    }
	else if(nCtlColor == CTLCOLOR_EDIT)   //此处设置为编辑框文字背景色和字体颜色，CTLCOLOR_EDIT表示编辑框
    {
		pDC->SetBkMode(TRANSPARENT);  //文字背景透明
		//pDC->SetTextColor(RGB(0,0,0));
		//pDC->SetBkColor(RGB(250, 250, 250));//设置字体背景颜色
		sbrush = CreateSolidBrush(RGB(255,255,255)); 
		return sbrush; 
    }
	/*
    switch(pWnd->GetDlgCtrlID())   //此处为设置控件为特定ID的文本透明。
    { 
		case IDC_EDIT1 : 
		{
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(125,0,0)); 
			sbrush = CreateSolidBrush(RGB(255,255,255));
			return sbrush;
			//return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		}
		default:
			break; 
    } 
	*/

	sbrush = CDialog::OnCtlColor(pDC,pWnd, nCtlColor);
    return sbrush;
}

void CContentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContentDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CContentDlg, CDialog)
	//{{AFX_MSG_MAP(CContentDlg)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SuperDictDlg dialog

SuperDictDlg::SuperDictDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SuperDictDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SuperDictDlg)
	//read setting.ini
	m_bEnableMouseCap = GetPrivateProfileInt(_T("SuperDict"),_T("EnMouseCap"),0,_T(".\\setting.ini"));
	if (m_bEnableMouseCap)
	{
		g_fpEnableCursorCapture(TRUE);
	}
	m_bEnableHotkeyCap = GetPrivateProfileInt(_T("SuperDict"),_T("EnHotkeyCap"),0,_T(".\\setting.ini"));
	if (m_bEnableHotkeyCap)
	{
		// register hotkey
		UINT vk = 'C';
		UINT fsModifiers = 0;
		fsModifiers = fsModifiers|MOD_ALT;
		g_fpEnableHotkeyCapture(TRUE, fsModifiers, vk);
	}
	m_bEnableHighlight = GetPrivateProfileInt(_T("SuperDict"),_T("EnHightlightCap"),0,_T(".\\setting.ini"));
	if (m_bEnableHighlight)
	{
		g_fpEnableHighlightCapture(TRUE);
	}
	m_bEnableDBClickCap = GetPrivateProfileInt(_T("SuperDict"),_T("EnDBClickCap"),0,_T(".\\setting.ini"));
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	pThis = this;

	AfxOleInit();
	m_pConnection.CreateInstance(__uuidof(Connection));
	try                
	{
		// 打开本地Access库Demo.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source='c:\\dict.mdb'","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("数据库连接失败，确认数据库dict.mdb是否在当前路径下!"));
		return;
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
}
SuperDictDlg::~SuperDictDlg()
{
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;

	if(m_pRecordset->State)
		m_pRecordset->Close();
	m_pRecordset= NULL;
}

void SuperDictDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SuperDictDlg)
	DDX_Check(pDX, IDC_CHECK_HIGHLIGHT, m_bEnableHighlight);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editresult);
	DDX_Check(pDX, IDC_CHECK_MOUSE, m_bEnableMouseCap);
	DDX_Check(pDX, IDC_CHECK_HOTKEY, m_bEnableHotkeyCap);
	DDX_Check(pDX, IDC_CHECK_DBCLICK, m_bEnableDBClickCap);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(SuperDictDlg, CDialog)
	//{{AFX_MSG_MAP(SuperDictDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_MOUSE, OnCheckMouseCap)
	ON_BN_CLICKED(IDC_CHECK_HOTKEY, OnCheckHotkeyCap)
	ON_BN_CLICKED(IDC_SETDLGBTN, OnSetDlg)
	ON_BN_CLICKED(IDC_INSTALLBTN, OnInstallPlugin)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_HIGHLIGHT, OnCheckHighlightCap)
	ON_BN_CLICKED(IDC_CHECK_DBCLICK, OnCheckDBClickCap)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY, DealHotKey) // register hotkey
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SuperDictDlg message handlers

BOOL SuperDictDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(SUPERDICT_TITLE);

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// set the window to the topmost
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE|SWP_HIDEWINDOW);
	CenterWindow();
	ShowWindow(SWP_SHOWWINDOW);

/**/
	// register hotkey to show or hide APP window 
	HWND hWnd = GetSafeHwnd();
	UINT vk = 'H';
	UINT fsModifiers = 0;
	fsModifiers = fsModifiers|MOD_ALT;
	RegisterHotKey(hWnd, HOTKEY_SHOW_HIDE, fsModifiers, vk);
	m_hotSign = FALSE;

	//register hotkey to en dblclickcap
	vk = 'M';
	fsModifiers = 0;
	fsModifiers = fsModifiers|MOD_ALT;
	RegisterHotKey(hWnd, HOTKEY_EN_DBLCLICKCAP, fsModifiers, vk);

	// register callback
	g_fpSetLicenseID(LICENSEID);
	g_fpSetCaptureReadyCallback(CaptureText);
	g_fpSetHighlightReadyCallback(CaptureHighlightText);
	g_fpSetMouseMonitorCallback(MoniterMouseEvent);

	int x,y;
	x = GetPrivateProfileInt(_T("SuperDict"),_T("CONTENTDLG_X"),0,_T(".\\setting.ini"));
	y = GetPrivateProfileInt(_T("SuperDict"),_T("CONTENTDLG_Y"),0,_T(".\\setting.ini"));
	//cdlg = new CContentDlg;
	cdlg.Create(IDD_CONTENTDLG);
	cdlg.SetWindowPos(&wndTopMost,x,y,0,0,SWP_NOSIZE);
	//cdlg->ModifyStyleEx(0, WS_EX_LAYERED/*|WS_EX_TRANSPARENT*/); //如果加上WS_EX_TRANSPARENT属性，则鼠标会穿透此窗体。这里由于在窗体设计中设置了属性，无须在此再次设置。
	//cdlg->SetLayeredWindowAttributes(0, 192, LWA_ALPHA);    // 设置半透明
	cdlg.ModifyStyle(WS_CAPTION,0,0); //去除标题栏及边框

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void SuperDictDlg::OnDestroy() 
{
	// unregister hotkey
	UnregisterHotKey(GetSafeHwnd(), HOTKEY_SHOW_HIDE);
	UnregisterHotKey(GetSafeHwnd(), HOTKEY_EN_DBLCLICKCAP);

	// unregister callback
	g_fpRemoveCaptureReadyCallback(CaptureText);
	g_fpRemoveHighlightReadyCallback(CaptureHighlightText);
	g_fpRemoveMouseMonitorCallback(MoniterMouseEvent);

	//save setting.ini
	if(m_bEnableMouseCap){
		WritePrivateProfileString(_T("SuperDict"),_T("EnMouseCap"),_T("1"),_T(".\\setting.ini"));
	}else{
		WritePrivateProfileString(_T("SuperDict"),_T("EnMouseCap"),_T("0"),_T(".\\setting.ini"));
	}
	if(m_bEnableHotkeyCap){
		WritePrivateProfileString(_T("SuperDict"),_T("EnHotkeyCap"),_T("1"),_T(".\\setting.ini"));
	}else{
		WritePrivateProfileString(_T("SuperDict"),_T("EnHotkeyCap"),_T("0"),_T(".\\setting.ini"));
	}
	if(m_bEnableHighlight){
		WritePrivateProfileString(_T("SuperDict"),_T("EnHightlightCap"),_T("1"),_T(".\\setting.ini"));
	}else{
		WritePrivateProfileString(_T("SuperDict"),_T("EnHightlightCap"),_T("0"),_T(".\\setting.ini"));
	}
	if(m_bEnableDBClickCap){
		WritePrivateProfileString(_T("SuperDict"),_T("EnDBClickCap"),_T("1"),_T(".\\setting.ini"));
	}else{
		WritePrivateProfileString(_T("SuperDict"),_T("EnDBClickCap"),_T("0"),_T(".\\setting.ini"));
	}

	CDialog::OnDestroy();
}

void SuperDictDlg::OnPaint() 
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
		if(!m_hotSign){
			ShowWindow(SW_HIDE); //启动时自动隐藏
		}
	}
}

HCURSOR SuperDictDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void SuperDictDlg::OnCheckMouseCap() 
{
	UpdateData(TRUE);

	if (m_bEnableMouseCap)
	{
		g_fpEnableCursorCapture(TRUE);
	}
	else
	{
		// disable text-capturing with mouse cursor
		g_fpEnableCursorCapture(FALSE);
	}
}

void SuperDictDlg::OnCheckHighlightCap() 
{
	UpdateData(TRUE);

	if (m_bEnableHighlight)
	{
		g_fpEnableHighlightCapture(TRUE);
	}
	else
	{
		g_fpEnableHighlightCapture(FALSE);
	}
}

void SuperDictDlg::OnCheckDBClickCap() 
{
	UpdateData(TRUE);

	if (m_bEnableDBClickCap)
	{
		// register hotkey to cap when doubleclick
	}
	else
	{
		//unregister
	}
}

void SuperDictDlg::OnCheckHotkeyCap() 
{
	UpdateData(TRUE);

	UINT vk = 'C';
	UINT fsModifiers = 0;
	fsModifiers = fsModifiers|MOD_ALT;

	if (m_bEnableHotkeyCap)
	{
		// register hotkey
		g_fpEnableHotkeyCapture(TRUE, fsModifiers, vk);
	}
	else
	{
		// unregister hotkey
		g_fpEnableHotkeyCapture(FALSE, fsModifiers, vk);
	}
}

HRESULT	WINAPI SuperDictDlg::CaptureText(long wParam, long lParam)
{
	POINT ptCursor;
	::GetCursorPos(&ptCursor);
	BOOL bOK = FALSE;
	BSTR bstr=NULL;
	long pos;
	bOK = g_fpGetString(ptCursor.x, ptCursor.y, &bstr, &pos);
	if (bOK){
		CString strText;
		strText = bstr;
		pThis->GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(strText);
		pThis->SetDlgItemInt(IDC_EDIT_CURSOR, pos);

		CString answer;
		CString searchStr=strText;

		if (pos != -1)
		{
			pThis->SeperateByChar(' ',pos,searchStr);
			pThis->SeperateByChar('.',pos,searchStr);
			pThis->GetDlgItem(IDC_EDIT_TEXT2)->SetWindowText(searchStr);
			/*
			CString strCursor;
			strCursor=strText.Mid(pos);
			pThis->GetDlgItem(IDC_EDIT_TEXT2)->SetWindowText(strCursor);
			*/
		}
		else
		{
			pThis->GetDlgItem(IDC_EDIT_TEXT2)->SetWindowText(_T(""));	
		}

		pThis->GetAnswer(searchStr,answer);
		pThis->GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(answer);
		pThis->cdlg.GetDlgItem(IDC_EDIT1)->SetWindowText(answer);
		pThis->cdlg.ShowWindow(SW_SHOW);

		pThis->ptCursor = ptCursor;
		//AfxMessageBox(strText, MB_OK|MB_ICONERROR);
		g_fpFreeString(&bstr);
	}else{
		//AfxMessageBox(_T("Error!"), MB_OK|MB_ICONERROR);
	}

	return TRUE;
}

HRESULT	WINAPI SuperDictDlg::CaptureHighlightText(long wParam, long lParam)
{
	POINT ptCursor;
	::GetCursorPos(&ptCursor);

	CString strText;
	BOOL bOK = FALSE;
	BSTR bstr = NULL;
	bOK = g_fpGetHighlightText2(ptCursor.x,ptCursor.y, &bstr);
	if (bOK)
	{
		strText = bstr;
		g_fpFreeString(&bstr);
	}

	pThis->GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(strText);
	
	CString answer;
	CString searchStr=strText;
	//pThis->GetDlgItem(IDC_EDIT_TEXT2)->SetWindowText(searchStr);
	pThis->GetAnswer(searchStr,answer);
	pThis->GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(answer);
	pThis->cdlg.GetDlgItem(IDC_EDIT1)->SetWindowText(answer);
	pThis->cdlg.ShowWindow(SW_SHOW);

	pThis->SetDlgItemInt(IDC_EDIT_CURSOR, NULL);
	pThis->GetDlgItem(IDC_EDIT_TEXT2)->SetWindowText(_T(""));	

	return TRUE;
}

HRESULT	WINAPI SuperDictDlg::MoniterMouseEvent(long wParam, long lParam)
{
	POINT ptCursor;
	::GetCursorPos(&ptCursor);
	if(abs(ptCursor.x - pThis->ptCursor.x) > 5 || abs(ptCursor.y - pThis->ptCursor.y) > 5 )
	{
		pThis->cdlg.ShowWindow(SW_HIDE);
		/*
		CString tstr,t;
		tstr+="(";
		t.Format(_T("%d"),ptCursor.x);
		tstr+=t;
		tstr+=",";
		t.Format(_T("%d"),ptCursor.y);
		tstr+=t;
		tstr+=")(";
		t.Format(_T("%d"),pThis->ptCursor.x);
		tstr+=t;
		tstr+=",";
		t.Format(_T("%d"),pThis->ptCursor.y);
		tstr+=t;
		tstr+=")";
		pThis->GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(tstr);
		*/
	}
	if(pThis->m_bEnableDBClickCap && (wParam == WM_LBUTTONDBLCLK) )
	{
		pThis->CaptureText(0,0);
	}
	return TRUE;
}

void SuperDictDlg::OnSetDlg() 
{
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); 
	typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
	MYFUNC fun = NULL;
	if(hInst) 
	{ 
		//取得SetLayeredWindowAttributes函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
	}
	if(cdlg.IsWindowVisible())
	{
		CRect trect;
		cdlg.GetWindowRect(trect);
		CString tstr;
		tstr.Format(_T("%d"),trect.left);
		WritePrivateProfileString(_T("SuperDict"),_T("CONTENTDLG_X"),tstr,_T(".\\setting.ini"));
		tstr.Format(_T("%d"),trect.top);
		WritePrivateProfileString(_T("SuperDict"),_T("CONTENTDLG_Y"),tstr,_T(".\\setting.ini"));

		cdlg.ShowWindow(SW_HIDE);
		pThis->GetDlgItem(IDC_SETDLGBTN)->SetWindowText(_T("配置翻译窗口"));
		cdlg.ModifyStyle(WS_CAPTION,0,0); //去除标题栏及边框
		cdlg.GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
		
		SetWindowLong(cdlg.GetSafeHwnd(),
					  GWL_EXSTYLE, 
					  GetWindowLong(cdlg.GetSafeHwnd(),GWL_EXSTYLE)| 0x80000);  //设定窗体使用扩展模式 
		COLORREF maskColor = RGB(255,255,255);   //掩码颜色
		if(fun)
			fun(cdlg.GetSafeHwnd(),maskColor,255,1);
		g_fpSetMouseMonitorCallback(MoniterMouseEvent);
	}else{
		cdlg.ShowWindow(SW_SHOW);
		pThis->GetDlgItem(IDC_SETDLGBTN)->SetWindowText(_T("配置完毕"));
		if(fun)
			fun(cdlg.GetSafeHwnd(),0, 192, 2);
		//cdlg.SetLayeredWindowAttributes(0, 192, 2);    // 设置半透明
		cdlg.ModifyStyle(0,WS_CAPTION,0); //添加标题栏及边框
		cdlg.GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		g_fpRemoveMouseMonitorCallback(MoniterMouseEvent);
	}

	FreeLibrary(hInst); 

	return;
}

void SuperDictDlg::OnInstallPlugin() 
{
	WinExec(".\\install_plugin.exe",SW_HIDE);
}

void SuperDictDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void SuperDictDlg::SeperateByChar(char c,int pos,CString &str)
{
	int n;
	n=str.Find(c,pos);
	if(n!=-1)
		str=str.Left(n);

	n=str.ReverseFind(c);
	if(n!=-1)
		str=str.Mid(n+1);

	return;
}
void SuperDictDlg::GetAnswer(CString &searchStr,CString &result)
{
	CString sql=_T("SELECT * FROM dictTable where question like '%") + searchStr + _T("%'");
	//_RecordsetPtr   m_pRecordset;
	//m_pRecordset.CreateInstance(__uuidof(Recordset));
	if(m_pRecordset->State)
		m_pRecordset->Close();

	try
	{
		m_pRecordset->Open((_variant_t)sql,
							m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
							adOpenDynamic,
							adLockOptimistic,
							adCmdText);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
		return;
	}

	_variant_t var;
	if(!m_pRecordset->BOF)
		m_pRecordset->MoveFirst();
	else
	{
		result=_T("未找到记录!");
		return;
	}

	result=""; 
	// 读入库中各字段并加入列表框中
	while(!m_pRecordset->adoEOF)
	{
		var = m_pRecordset->GetCollect("question");
		if(var.vt != VT_NULL)
			result += (LPCSTR)_bstr_t(var);

		var = m_pRecordset->GetCollect("answer");
		if(var.vt != VT_NULL)
			result += (LPCSTR)_bstr_t(var);
 
		m_pRecordset->MoveNext();
	}
	return;
}

LRESULT SuperDictDlg::DealHotKey(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case HOTKEY_SHOW_HIDE:
		{
            if( m_hotSign )
            {// 隐藏程序
                HWND hWnd = GetSafeHwnd();
                LONG lStyle = ::GetWindowLong(m_hWnd,GWL_STYLE);
                lStyle |= WS_POPUP;
                ::SetWindowLong(m_hWnd, GWL_STYLE, lStyle);
                ::ShowWindow(m_hWnd,SW_HIDE);								   
                m_hotSign = FALSE;
                break;
            }
			else
			{// 呼出程序 
                HWND hWnd = GetSafeHwnd();
                LONG lStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
                lStyle &= ~WS_POPUP;
                ::SetWindowLong(m_hWnd, GWL_STYLE, lStyle);
                ::ShowWindow(m_hWnd,SW_SHOW);
                CWnd::SetForegroundWindow();								   
                m_hotSign = TRUE;
                break;
            }
			//AfxMessageBox(_T("HotKey is enabled!"), MB_OK|MB_ICONINFORMATION);
		}
		break;

	case HOTKEY_EN_DBLCLICKCAP:
		if(m_bEnableDBClickCap)
		{
			m_bEnableDBClickCap = FALSE;
			UpdateData(FALSE);
			pThis->GetDlgItem(IDC_CHECK_DBCLICK)->UpdateWindow();
		}
		else
		{
			m_bEnableDBClickCap = TRUE;
			UpdateData(FALSE);
			pThis->GetDlgItem(IDC_CHECK_DBCLICK)->UpdateWindow();
		}
		break;

	default:
		break;
	}

	return 0L;
}
