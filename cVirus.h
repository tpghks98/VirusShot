#pragma once
#include "cMonster.h"
class cVirus :
	public cMonster
{
private:
	int	m_nCount;

public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();

private:
	void	VirusShot();
public:
	cVirus(void);
	~cVirus(void);
};

