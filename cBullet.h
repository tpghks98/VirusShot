#pragma once

#include "iobj.h"
class cBullet :
	public IObj
{

public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
	virtual void	OnCollision(int, IObj* pObj = NULL);
public:
	cBullet(void);
	~cBullet(void);
};

