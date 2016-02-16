#pragma once
#include "iobj.h"
class cTimer :
	public cBaseObject
{
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual	void	Render();
	virtual	void	Release();

public:

	short	nType;
	IObj*	pOwner;
	bool	IsOn;
	bool	IsRepeat;
	float	fCoolTime;
	float	fElapTime;

	void Setting( float fCoolTime );

public:
	cTimer(void);
	~cTimer(void);
};