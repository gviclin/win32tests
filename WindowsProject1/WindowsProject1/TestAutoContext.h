#ifndef _TEST_AUTO_CONTEXT_H
#define _TEST_AUTO_CONTEXT_H

class CBaseState;


enum eState {
	eSTANDBY,
	eTOD_DOWN_ABS,
	eTOD_WAIT_DOWN_ABS,
	eTOD_FF
};

class CTestAutoContext
{	
public:
	CTestAutoContext();
	~CTestAutoContext();

	void SetState(eState eState);


private:
	CBaseState* m_pState;
};

#endif