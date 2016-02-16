#pragma once
#include "iobj.h"
class cScene :
	public IObj
{
public:
	virtual	void	Init()		PURE;
	virtual	void	Update()	PURE;
	virtual	void	Render()	PURE;
	virtual	void	Release()	PURE;

public:
	cScene(void);
	virtual ~cScene(void);
};

