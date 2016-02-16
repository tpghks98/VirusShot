#pragma once
#include "cbullet.h"
class cEnemyBullet :
	public cBullet
{
public:
	virtual void Init();
public:
	cEnemyBullet(void);
	~cEnemyBullet(void);
};

