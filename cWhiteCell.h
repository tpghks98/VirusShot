#pragma once
#include "cmonster.h"
class cWhiteCell :
	public cMonster
{
public:
	virtual	void	Init();
	virtual void	Render();
public:
	cWhiteCell(void);
	~cWhiteCell(void);
};

