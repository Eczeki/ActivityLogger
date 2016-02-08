#pragma once
#include <string>
#include <sstream>

/*
 * A class to record data related to the window that the user is currently using.
 * It returns a string representation of itself to be stored in a file.
 *
 */

class WindowData
{
public:
	WindowData();	
	std::string toString();			
	void incrementScreenshotNum();
	void addKeystroke(char keystroke);
	void setWindowName(std::string window);
	void increaseTimeSpentInWindow(double time);
	void resetAll();

private:
	int screenShotsNum;				/* Holds the number of screenshots taken by the user */
	double timeSpentInWindow;		/* Holds the time the user has spent in the given application */
	std::string windowName;			/* Holds the name of the window that the user is accesing */
	std::string keyStrokes;			/* Holds the keystrokes that the user has pressed so far */					
};

