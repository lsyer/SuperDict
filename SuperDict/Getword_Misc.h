// Getword_Misc.h

#ifndef __ICALL_MISC_H__
#define __ICALL_MISC_H__

typedef void (WINAPI *SETLICENSEID)(
  LPCTSTR szLicenseID   // LicenseID
);
typedef HWND (WINAPI *SETDELAY)(LONG uMilliSec);
typedef BOOL (WINAPI *ENABLECURSORCAPTURE)(BOOL bEnable);
typedef BOOL (WINAPI *ENABLEHOTKEYCAPTURE)(
  BOOL bEnable,      // enable or disable text-capturing with hotkey
  LONG fsModifiers,  // key-modifier options
  LONG vk           // virtual-key code
);
typedef BOOL (WINAPI *ENABLEHIGHLIGHTCAPTURE)(
  BOOL bEnable    // enable or disable text-capturing with mouse selection
);
typedef BOOL (WINAPI *GETSTRING)(
  LONG  x,          // the x position of the point which you want to capture text from
  LONG  y,          // the y position of the point which you want to capture text from
  BSTR* pstr,       // the captured string
  LONG* pos         // zero-based point(x,y) position in the captured string   
);
typedef BOOL (WINAPI *GETSTRING2)(
  LONG  x,          // the x position of the point which you want to capture text from
  LONG  y,          // the y position of the point which you want to capture text from
  BSTR* pstr,       // the captured string
  LONG* pos,        // zero-based point(x,y) position in the captured string   
  LONG* left,       // x-coordinate of upper-left corner of the bounding rectangle of the captured string
  LONG* top,        // y-coordinate of upper-left corner of the bounding rectangle of the captured string
  LONG* right,      // x-coordinate of lower-right corner of the bounding rectangle of the captured string
  LONG* bottom      // y-coordinate of lower-right corner of the bounding rectangle of the captured string
);
typedef BOOL (WINAPI *GETRECTSTRING)(
  LONG  hWnd,       // the window handle to capture
  LONG  left,       // x-coordinate of upper-left corner
  LONG  top,        // y-coordinate of upper-left corner
  LONG  right,      // x-coordinate of lower-right corner
  LONG  bottom,     // y-coordinate of lower-right corner
  BSTR* pstr       // the captured string
);
typedef BOOL (WINAPI *GETHIGHLIGHTSTRING2)(
  LONG  x,       // the x coordinate in screen coordinates
  LONG  y,       // the y coordinate in screen coordinates
  BSTR* pstr    // the captured string
);
typedef BOOL (WINAPI *FREESTRING)(
  BSTR* pstr     // Pointer to a BSTR string
);
typedef HRESULT (WINAPI *NotifyCallBack)(long wParam, long lParam);
typedef BOOL (WINAPI *SETCAPTUREREADYCALLBACK)(
  NotifyCallBack callbackFunc    // callbackFunc is a function pointer to NotifyCallBack
);
typedef BOOL (WINAPI *REMOVECAPTUREREADYCALLBACK)(
  NotifyCallBack callbackFunc    // callbackFunc is a function pointer to NotifyCallBack
);
typedef BOOL (WINAPI *SETHIGHLIGHTREADYCALLBACK)(
  NotifyCallBack callbackFunc    // callbackFunc is a function pointer to NotifyCallBack
);
typedef BOOL (WINAPI *REMOVEHIGHLIGHTREADYCALLBACK)(
  NotifyCallBack callbackFunc    // callbackFunc is a function pointer to NotifyCallBack
);
typedef BOOL (WINAPI *SETMOUSEMONITORCALLBACK)(
  NotifyCallBack callbackFunc    // callbackFunc is a function pointer to NotifyCallBack
);
typedef BOOL (WINAPI *REMOVEMOUSEMONITORCALLBACK)(
  NotifyCallBack callbackFunc    // callbackFunc is a function pointer to NotifyCallBack
);

extern SETLICENSEID						g_fpSetLicenseID;
extern SETDELAY							g_fpSetDelay;
extern ENABLECURSORCAPTURE				g_fpEnableCursorCapture;
extern ENABLEHOTKEYCAPTURE				g_fpEnableHotkeyCapture;
extern ENABLEHIGHLIGHTCAPTURE			g_fpEnableHighlightCapture;
extern GETSTRING						g_fpGetString;
extern GETSTRING2						g_fpGetString2;
extern GETRECTSTRING					g_fpGetRectString;
extern GETHIGHLIGHTSTRING2				g_fpGetHighlightText2;
extern FREESTRING						g_fpFreeString;
extern SETCAPTUREREADYCALLBACK			g_fpSetCaptureReadyCallback;
extern REMOVECAPTUREREADYCALLBACK		g_fpRemoveCaptureReadyCallback;
extern SETHIGHLIGHTREADYCALLBACK		g_fpSetHighlightReadyCallback;
extern REMOVEHIGHLIGHTREADYCALLBACK		g_fpRemoveHighlightReadyCallback;
extern SETMOUSEMONITORCALLBACK			g_fpSetMouseMonitorCallback;
extern REMOVEMOUSEMONITORCALLBACK		g_fpRemoveMouseMonitorCallback;


BOOL LoadICallLib();
BOOL FreeICallLib();

#endif //__ICALL_MISC_H__    

