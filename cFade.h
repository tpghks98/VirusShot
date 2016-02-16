#pragma once
#include "cui.h"
class cFade :
	public cUI
{
private:
	_SYNTHESIZE_REF_INHER( float, m_fAlpha, Alpha );
public:
	virtual	void	Init();
	virtual	void	Render();
	virtual	void	Release();
public:
	cFade(void);
	~cFade(void);
};

