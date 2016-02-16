#pragma once
#include "iobj.h"
class cItem :
	public IObj
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

	virtual void	OnCollision( int nTargetType, IObj* pObj = NULL );
public:
	cItem(void);
	~cItem(void);
};

