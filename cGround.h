#pragma once
#include "iobj.h"
class cGround :
	public IObj
{
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

private:
	void	ScrollMove();
public:
	cGround(void);
	~cGround(void);
};

