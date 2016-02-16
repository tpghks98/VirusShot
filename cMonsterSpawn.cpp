#include "DXUT.h"
#include "cMonsterSpawn.h"
#include "cTimer.h"

cMonsterSpawn::cMonsterSpawn(void)
{
}


cMonsterSpawn::~cMonsterSpawn(void)
{
}


void	cMonsterSpawn::Init()
{
	m_vPos = D3DXVECTOR3( 0.0f, 0.0f, 450.0f );

}
void	cMonsterSpawn::Update()
{
	this->Translation();

}
void	cMonsterSpawn::Render()
{
}
void	cMonsterSpawn::Release()
{
}
void	cMonsterSpawn::OnTimer( cTimer* pTimer )
{
	if( pTimer->nType == TT_SPAWN )
	{
		for( int n = 0; n < m_nMonsterCount; ++n )
		{
			D3DXVECTOR3	vGen	=	this->m_vPos;
			vGen.x += rand() % 500 * 0.01f - 2.5f;


			_GETSINGLE( cObjMgr )->CreateObject( m_nGenTargetType, vGen );
		}
	}
}

void	cMonsterSpawn::SetupGenTimer( float fCool, float fImmediatelyTime )
{
	m_lstChild.push_back( _GETSINGLE( cSystemMgr )->SetTimer( this, fCool , TT_SPAWN, true ) );
	EASY_CAST( cTimer*, m_lstChild.back())->fElapTime = fImmediatelyTime;
}