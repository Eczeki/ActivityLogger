#include "WindowRecorder.h"


WindowRecorder::WindowRecorder()
{
	stopped = false;
	newWindow = false;
	pastWindowName = "";
	timeStart = time(0);
	timeInSeconds = 0.0;
}

WindowRecorder::~WindowRecorder()
{
	delete recorder;
}

void WindowRecorder::start()
{
	/* start thread */
	recorder = new std::thread(&WindowRecorder::outputWindowName, this);
}

void WindowRecorder::stop()
{
	stopped = true;
}

/* Returns true if there's a change of window */
bool WindowRecorder::windowChange()
{
	bool tmp = newWindow;	
	newWindow = false;	
	return tmp;
}

void WindowRecorder::outputWindowName()
{
	char name[300];
	HWND currentWindowHWND;
	std::ofstream out;
	bool start = false;
	while (!stopped)
	{		
		currentWindowHWND = GetForegroundWindow();
		GetWindowTextA(currentWindowHWND, name, 300);		
		windowName = std::string(name);
		timeInSeconds = difftime(time(0), timeStart);

		if (pastWindowName != windowName)
		{
			newWindow = true;
			pastWindowName = windowName;	
			out.open("log.txt", std::ofstream::app);
			if (!start)
			{
				out << "WINDOW: " << pastWindowName << std::endl;
				start = true;
			}
			else
			{
				out << std::endl << "Minutes spent in the application: " << (timeInSeconds / 60) << std::endl;
				out << "WINDOW: " << pastWindowName << std::endl;
			}
			out.close();
		}
	}
}

std::string WindowRecorder::getWindowName()
{
	return windowName;
}

double WindowRecorder::getTime()
{
	return timeInSeconds;
}