#include "DXUT.h"
#include "cEnemyBullet.h"


cEnemyBullet::cEnemyBullet(void)
{
}


cEnemyBullet::~cEnemyBullet(void)
{
}


void	cEnemyBullet::Init()
{
	cBullet::Init();
	m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "bullet_enemy" );
}