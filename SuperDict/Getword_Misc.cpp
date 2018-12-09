// ICall_Misc.cpp

#include "stdafx.h"
#include "Getword_Misc.h"
#include "LicenseID.h"

HINSTANCE						g_hICallInst2 = NULL;
SETLICENSEID					g_fpSetLicenseID = NULL;
SETDELAY						g_fpSetDelay = NULL;
ENABLECURSORCAPTURE				g_fpEnableCursorCapture = NULL;
ENABLEHOTKEYCAPTURE				g_fpEnableHotkeyCapture = NULL;
ENABLEHIGHLIGHTCAPTURE			g_fpEnableHighlightCapture = NULL;
GETSTRING						g_fpGetString = NULL;
GETSTRING2						g_fpGetString2 = NULL;
GETRECTSTRING					g_fpGetRectString = NULL;
GETHIGHLIGHTSTRING2				g_fpGetHighlightText2 = NULL;
FREESTRING						g_fpFreeString = NULL;
SETCAPTUREREADYCALLBACK			g_fpSetCaptureReadyCallback = NULL;
REMOVECAPTUREREADYCALLBACK		g_fpRemoveCaptureReadyCallback = NULL;
SETHIGHLIGHTREADYCALLBACK		g_fpSetHighlightReadyCallback = NULL;
REMOVEHIGHLIGHTREADYCALLBACK	g_fpRemoveHighlightReadyCallback = NULL;
SETMOUSEMONITORCALLBACK			g_fpSetMouseMonitorCallback = NULL;
REMOVEMOUSEMONITORCALLBACK		g_fpRemoveMouseMonitorCallback = NULL;

BOOL LoadICallLib()
{
	g_hICallInst2 = LoadLibrary(_T("GetWord.dll"));
	if (!g_hICallInst2)
	{
		return FALSE; 
	}

	g_fpSetLicenseID  = (SETLICENSEID)GetProcAddress(g_hICallInst2, "SetLicenseID");
	if (!g_fpSetLicenseID )	{		return FALSE;	}

	g_fpSetDelay  = (SETDELAY)GetProcAddress(g_hICallInst2, "SetDelay");
	if (!g_fpSetDelay )	{		return FALSE;	}

	g_fpEnableCursorCapture  = (ENABLECURSORCAPTURE)GetProcAddress(g_hICallInst2, "EnableCursorCapture");
	if (!g_fpEnableCursorCapture )	{		return FALSE;	}

	g_fpEnableHotkeyCapture  = (ENABLEHOTKEYCAPTURE)GetProcAddress(g_hICallInst2, "EnableHotkeyCapture");
	if (!g_fpEnableHotkeyCapture )	{		return FALSE;	}

	g_fpEnableHighlightCapture  = (ENABLEHIGHLIGHTCAPTURE)GetProcAddress(g_hICallInst2, "EnableHighlightCapture");
	if (!g_fpEnableHighlightCapture )	{		return FALSE;	}

	g_fpGetString  = (GETSTRING)GetProcAddress(g_hICallInst2, "GetString");
	if (!g_fpGetString )	{		return FALSE;	}

	g_fpGetString2  = (GETSTRING2)GetProcAddress(g_hICallInst2, "GetString2");
	if (!g_fpGetString2 )	{		return FALSE;	}

	g_fpGetRectString  = (GETRECTSTRING)GetProcAddress(g_hICallInst2, "GetRectString");
	if (!g_fpGetRectString )	{		return FALSE;	}

	g_fpGetHighlightText2   = (GETHIGHLIGHTSTRING2)GetProcAddress(g_hICallInst2, "GetHighlightText2");
	if (!g_fpGetHighlightText2  )	{		return FALSE;	}

	g_fpFreeString  = (FREESTRING)GetProcAddress(g_hICallInst2, "FreeString");
	if (!g_fpFreeString )	{		return FALSE;	}

	g_fpSetCaptureReadyCallback  = (SETCAPTUREREADYCALLBACK)GetProcAddress(g_hICallInst2, "SetCaptureReadyCallback");
	if (!g_fpSetCaptureReadyCallback )	{		return FALSE;	}

	g_fpRemoveCaptureReadyCallback  = (REMOVECAPTUREREADYCALLBACK)GetProcAddress(g_hICallInst2, "RemoveCaptureReadyCallback");
	if (!g_fpRemoveCaptureReadyCallback )	{		return FALSE;	}

	g_fpSetHighlightReadyCallback  = (SETHIGHLIGHTREADYCALLBACK)GetProcAddress(g_hICallInst2, "SetHighlightReadyCallback");
	if (!g_fpSetHighlightReadyCallback )	{		return FALSE;	}

	g_fpRemoveHighlightReadyCallback  = (REMOVEHIGHLIGHTREADYCALLBACK)GetProcAddress(g_hICallInst2, "RemoveHighlightReadyCallback");
	if (!g_fpRemoveHighlightReadyCallback )	{		return FALSE;	}

	g_fpSetMouseMonitorCallback  = (SETMOUSEMONITORCALLBACK)GetProcAddress(g_hICallInst2, "SetMouseMonitorCallback");
	if (!g_fpSetMouseMonitorCallback )	{		return FALSE;	}

	g_fpRemoveMouseMonitorCallback  = (REMOVEMOUSEMONITORCALLBACK)GetProcAddress(g_hICallInst2, "RemoveMouseMonitorCallback");
	if (!g_fpRemoveMouseMonitorCallback )	{		return FALSE;	}

	return TRUE;
}	

BOOL FreeICallLib(void)
{
	if (g_hICallInst2)
	{
		FreeLibrary(g_hICallInst2);	
		g_hICallInst2 = NULL;

		return TRUE;
	}

	return FALSE;
}
