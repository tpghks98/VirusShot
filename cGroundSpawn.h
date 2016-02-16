#pragma once
#include "iobj.h"
class cGroundSpawn :
	public IObj
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();


public:
	cGroundSpawn(void);
	~cGroundSpawn(void);
};

