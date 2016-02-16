#pragma once
#include "cscene.h"
class cHomeScene :
	public cScene
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

public:
	cHomeScene(void);
	~cHomeScene(void);
};

