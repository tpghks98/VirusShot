#pragma once
#include "cmonster.h"
class cRedCell :
	public cMonster
{
private:
	float	m_fStopTime;
public:
	virtual	void	Init();
	virtual	void	Update();
	virtual void	Render();

	virtual	void	OnCollision( int nTargetType, IObj* pObj );
public:
	cRedCell(void);
	~cRedCell(void);
};

