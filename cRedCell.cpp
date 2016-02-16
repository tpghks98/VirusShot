#include "DXUT.h"
#include "cRedCell.h"
#include "cPlayer.h"


cRedCell::cRedCell(void)
{
}


cRedCell::~cRedCell(void)
{
}


void	cRedCell::Init()
{
	m_vScale *= 0.5f;

	m_fStopTime = 0.0f;
	cMonster::Init();

	m_vRotation.x = D3DX_PI * 0.5f;

	m_vPos.y = 1.26f;
	m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "redcell" );
	m_fOriMoveSpeed	=	40.0f;
	m_fHp			=	500.0f;


}

void	cRedCell::Update()
{
	cMonster::Update();
	if( m_vPos.z < 125.0f )
	{
		if( m_fStopTime < 1.7f )
		{
			m_vScale += D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 0.2f;
			m_fStopTime += _GETSINGLE( cSystemMgr )->GetDeltaTime(); 
			m_fOriMoveSpeed = 0.0f;
		}
		else
		{
			m_vDirection = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
			m_fOriMoveSpeed	=	160.0f;
		}
	}

//	m_vRotation.y += D3DX_PI * _GETSINGLE( cSystemMgr )->GetDeltaTime();
}

void	cRedCell::Render()
{

	_GETSINGLE( cObjMgr )->m_fLighting = 0.5f;
	cMonster::Render();
	_GETSINGLE( cObjMgr )->m_fLighting = 1.0f;
}

void	cRedCell::OnCollision( int nTargetType, IObj* pObj )
{
	cMonster::OnCollision( nTargetType, pObj );
	switch( nTargetType )
	{
	case OI_BULLET:
		if( _GETSINGLE( cObjMgr )->GetCanAcessPlayer() )
		{
			EASY_CAST( cPlayer* , _GETSINGLE( cObjMgr )->m_pPlayer )->PlusPG( 0.5f );
		}
		break;
	}
}