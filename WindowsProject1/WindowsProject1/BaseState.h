#ifndef _BASE_STATE_H
#define _BASE_STATE_H

#include <string>

using std::string;

class CTestAutoContext;

class CBaseState 
{
public:
	CBaseState(CTestAutoContext* pContext, string strName);
	~CBaseState();

	string GetName();

private:
	CTestAutoContext* m_pContext;
	string m_strName;
};

#endif

