#pragma once
#include "cscene.h"
class cPlayScene :
	public cScene
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();
public:
	cPlayScene(void);
	~cPlayScene(void);
};

