#include "TestAutoContext.h"
#include "BaseState.h"
#include "Standby.h"
#include "tod_down_abs.h"
#include "tod_wait_down_abs.h"
#include "tod_ff.h"

#include <iostream>

#include "Windows.h"





CTestAutoContext::CTestAutoContext()
{
	m_pState = new CStandby(this);
}


CTestAutoContext::~CTestAutoContext()
{
}

void CTestAutoContext::SetState(eState eState)
{
	CBaseState* pStateTemp = m_pState;

	switch (eState)
	{
	case eSTANDBY:
		m_pState = new CStandby(this);
		break;
	case eTOD_DOWN_ABS:
		m_pState = new CTod_down_abs(this);
		break;
	case eTOD_WAIT_DOWN_ABS:
		m_pState = new CTod_wait_down_abs(this);
		break;
	case eTOD_FF:
		m_pState = new CTod_ff(this);
		break;
	default:
		break;
	}
	string s = "SetState from ";
	s += pStateTemp->GetName().c_str();
	s += " to ";
	s += m_pState->GetName().c_str();

	std::cout << s;
	
	OutputDebugString((LPCWSTR)s.c_str());

	delete pStateTemp;
}
