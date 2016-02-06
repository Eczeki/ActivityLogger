#pragma once
#include "KeyboardLog.h"

class ActivityLog
{
public:
	ActivityLog();
	~ActivityLog();

private:
	HHOOK hhkLowLevelKybd;

};

