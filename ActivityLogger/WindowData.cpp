#include "WindowData.h"


WindowData::WindowData()
{
	screenShotsNum = 0;
	timeSpentInWindow = 0.0f;
	windowName = "";
	keyStrokes = "";
}

/* Returns a string representation of the data */
std::string WindowData::toString()
{
	/* Convert timeSpentInWindow to string */
	std::ostringstream str;
	std::string time;
	str << timeSpentInWindow;
	std::string end = ",\n";
	
	return  "{\nWindowName : " + windowName + end +
			"Keystrokes : " + keyStrokes + end +
			"Time in Application : " + str.str() + end +
			"Screenshots : " + std::to_string(screenShotsNum) + end +
			"Keystrokes Number : " + std::to_string(keyStrokes.length()) + "\n}\n";
}

/* Increases the time spent in window */
void WindowData::increaseTimeSpentInWindow(double time)
{
	timeSpentInWindow += time;
}

/* Increases the screenshot counter */
void WindowData::incrementScreenshotNum()
{
	screenShotsNum++;
}

/* Sets the window name */
void WindowData::setWindowName(std::string window)
{
	windowName = window;
}

/* Records a keystroke */
void WindowData::addKeystroke(char keystroke)
{
	keyStrokes += keystroke;
}

/* Returns all records to their original state */
void WindowData::resetAll()
{
	screenShotsNum = 0;
	timeSpentInWindow = 0.0f;
	windowName = "";
	keyStrokes = "";
}

