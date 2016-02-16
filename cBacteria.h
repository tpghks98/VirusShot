#pragma once
#include "cmonster.h"
class cBacteria :
	public cMonster
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
public:
	cBacteria(void);
	~cBacteria(void);
};

