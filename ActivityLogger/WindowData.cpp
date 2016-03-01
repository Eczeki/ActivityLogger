#include "WindowData.h"


WindowData::WindowData()
{
	screenShotsNum = 0;
	timeSpentInWindow = 0.0f;	
	pastWindowName = windowName = "";
	keyStrokes = "";	
}

/* Returns a string representation of the data */
std::string WindowData::toString()
{
	/* Convert timeSpentInWindow to string */
	std::ostringstream str, str_t;
	int keystrokeSize = keyStrokes.length();
	str << timeSpentInWindow;

	if (keyStrokes.length() != 0) {
		str_t << (double)keystrokeSize / timeSpentInWindow;
	}
	else {
		str_t << 0.0f;
	}

	std::string end = ",\n";
	
	return  "{\nWindowName : " + pastWindowName + end +
			"Keystrokes : " + keyStrokes + end +
			"Time in Application : " + str.str() + end +
			"Screenshots : " + std::to_string(screenShotsNum) + end +
			"Typing speed : " + str_t.str() + " per minute" + end +
			"Keystrokes Number : " + std::to_string(keystrokeSize) + "\n}\n";
}

std::string WindowData::toStringHTML()
{
	/* Convert timeSpentInWindow to string */
	std::ostringstream str, str_t;
	int keystrokeSize = keyStrokes.length();
	str << timeSpentInWindow;

	if (keyStrokes.length() != 0) {
		str_t << (double)keystrokeSize / timeSpentInWindow;
	}
	else {
		str_t << 0.0f;
	}
   
	std::string end = "%0A";

	return  "{%0AWindowName&" + pastWindowName + end +
			"Keystrokes&" + keyStrokes + end +
			"TimeinApplication&" + str.str() + end +
			"Screenshots&" + std::to_string(screenShotsNum) + end +
			"TypingSpeed&" + str_t.str() + " per minute" + end +
			"KeystrokesNumber&" + std::to_string(keystrokeSize) + "%0A}%0A";
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
	pastWindowName = windowName;	
	screenShotsNum = 0;
	timeSpentInWindow = 0.0f;	
	windowName = "";	
	keyStrokes = "";
}

