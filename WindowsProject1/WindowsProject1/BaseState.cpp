#include "BaseState.h"


CBaseState::CBaseState(CTestAutoContext* pContext, string strName)
{
	m_pContext = pContext;
	m_strName = strName;
}


CBaseState::~CBaseState()
{
}

string CBaseState::GetName()
{
	return m_strName;
}
