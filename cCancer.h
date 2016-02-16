#pragma once
#include "cmonster.h"
class cCancer :
	public cMonster
{
private:
	_SYNTHESIZE_INHER( bool, m_IsOnceDir, OnceDir );
	_SYNTHESIZE_INHER( cCamera*, m_pCamera, Camera );
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();

	void	CancerShot();
public:
	cCancer(void);
	~cCancer(void);
};

