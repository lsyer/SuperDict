 // VC6Demo.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "SuperDict.h"
#include "SuperDictDlg.h"
#include "Getword_Misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SuperDictApp

BEGIN_MESSAGE_MAP(SuperDictApp, CWinApp)
	//{{AFX_MSG_MAP(SuperDictApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SuperDictApp construction

SuperDictApp::SuperDictApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only SuperDictApp object

SuperDictApp theApp;

#pragma data_seg("Shared") 
int volatile g_lAppInstance = 0; 
#pragma data_seg() 
#pragma comment(linker,"/section:Shared,RWS")


/////////////////////////////////////////////////////////////////////////////
// SuperDictApp initialization

BOOL SuperDictApp::InitInstance()
{
	// Dectect if there has running AppInstance.
	if (0 == g_lAppInstance)
	{
		g_lAppInstance = 1;
	}
	else if (1 == g_lAppInstance)
	{
		AfxMessageBox(_T("已经有一个实例在运行了。"), MB_OK|MB_ICONWARNING);
		//::MessageBox(NULL, TEXT("已经有一个实例在运行了。"), TEXT("注意"), MB_OK);
		return FALSE;
	}

	// Load ICall Lib
	BOOL bOK = LoadICallLib();
	if (!bOK)
	{
		AfxMessageBox(_T("Load ICall module failed."), MB_OK|MB_ICONERROR);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	SuperDictDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int SuperDictApp::ExitInstance() 
{
	// free ICall Lib
	FreeICallLib();	
	
	return CWinApp::ExitInstance();
}

SuperDictDlg* SuperDictDlg::pThis=NULL;