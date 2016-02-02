#pragma once
#include <thread>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <map>
#include <Windows.h>

/*
 * This class implements a thread that is constantly running to record
 * the name of the current active window.
 *
 */

typedef struct
{
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t  biPlanes;
	uint16_t  biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} DIB;

typedef struct
{
	uint16_t type;
	uint32_t bfSize;
	uint32_t reserved;
	uint32_t offset;
} HEADER;

typedef struct
{
	HEADER header;
	DIB dib;
} BMP;

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
	std::map<std::string, bool> programMap;	/* Stores the tracked programs names*/

	void trackedPrograms();
	void takeScreenshot(std::string name);	
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

