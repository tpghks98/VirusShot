#pragma once
#include "iobj.h"
class cSmooth :
	public cBaseObject
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
public:
	bool	IsOn;
	float*	pTarget;
	float	fStart;
	float	fEnd;
	float	fElap;
	float	fSpeed;
public:
	cSmooth(void);
	~cSmooth(void);
};

