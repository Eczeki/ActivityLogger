#pragma once
#include "KeyboardLog.h"

class ActivityLog
{
private:
	HHOOK hhkLowLevelKybd;
public:
	ActivityLog();
	~ActivityLog();
};

