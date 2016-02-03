#pragma once
#include <thread>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <Windows.h>

#ifdef UNICODE
#define UNI true
#else
#define UNI FALSE
#endif

/*
 * This class implements a thread that is constantly running to record
 * the name of the current active window.
 *
 */

class WindowRecorder
{
private:
	bool stopped;				/* To tell the thread when to stop*/
	bool newWindow;				/* To signal when there is a change of window */
	std::thread *recorder;		/* The window name recording thread itself */
	std::string windowName;		/* Records the name of the current active window */
	std::string pastWindowName;	/* To compare and determine if the window has been changed*/
	time_t timeStart;			/* To record how much time the user has been using an application */
	double timeInSeconds;		/* Time spent in each application */
	std::map<std::string, int> programMap;	/* Stores the tracked programs names*/

	void trackedPrograms();
	void takeScreenshot(std::string name);
	std::wstring WindowRecorder::stringToWstring(const std::string &s);
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);

public:
	WindowRecorder();
	~WindowRecorder();
	std::string getWindowName();
	double getTime();	
	void outputWindowName();	
	bool windowChange();	
	void start();
	void stop();
};

