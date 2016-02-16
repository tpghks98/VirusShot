#pragma once
#include "cscene.h"
class cIntroScene :
	public cScene
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
public:
	cIntroScene(void);
	~cIntroScene(void);
};

