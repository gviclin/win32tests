#ifndef _STANDBY_H
#define _STANDBY_H

#include "BaseState.h"

class CStandby :	public CBaseState
{
public:
	CStandby(CTestAutoContext* pContext);
	~CStandby();
};

#endif

