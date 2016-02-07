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
	
	/* @TODO: Fix problem with this output string not displaying windowname */
	return  "\nWindowName : " + '"' + windowName + '"' + ",\n" +
			"Keystrokes : " + '"' + keyStrokes + '"' + ",\n" +
			"Time in Application : " + '"' + str.str() + '"' + ",\n" +
			"Screenshots : " + '"' + std::to_string(screenShotsNum) + '"' + ",\n" +
			"Keystrokes Number : " + '"' + std::to_string(keyStrokes.length()) + '"' + "\n}\n";
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

