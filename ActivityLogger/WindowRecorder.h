#pragma once
#include <thread>
#include <string>
#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>
#include <map>
#include "WindowData.h"
#include <Windows.h>

/*
 * This class implements a thread that is constantly running to record
 * the name of the current active window.
 *
 */

class WindowRecorder
{
public:
	WindowRecorder();
	~WindowRecorder();
	std::string getWindowName();
	void recordKeystroke(char keystroke);
	double getTime();
	void outputWindowName();
	bool windowChange();
	void start();
	void stop();

private:
	const int screenInterval = 60;			/* The interval at which screenshots are taken */
	bool stopped;							/* To tell the thread when to stop*/
	bool newWindow;							/* To signal when there is a change of window */
	std::thread *recorder;					/* The window name recording thread itself */
	std::string windowName;					/* Records the name of the current active window */
	std::string pastWindowName;				/* To compare and determine if the window has been changed*/
	time_t timeStart;						/* To record how much time the user has been using an application */
	double timeInSeconds;					/* Time spent in each application */
	std::map<std::string, int> programMap;	/* Stores the tracked programs names*/	
	WindowData data;						/* To store the data ant print it in an orderly fashion */
	double screenshotTime;					/* Will tell when is the proper time to take a screenshot */


	void trackedPrograms();
	void takeScreenshot(std::string name);
	std::wstring WindowRecorder::stringToWstring(const std::string &s);
	PBITMAPINFO CreateBitmapInfoStruct(HWND hwnd, HBITMAP hBmp);
	void CreateBMPFile(HWND hwnd, LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);	

};

