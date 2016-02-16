#include "DXUT.h"
#include "cMonster.h"
#include "cObjMgr.h"
#include "cTimer.h"

cMonster::cMonster(void)
	:m_fMinZ( 0.0f )
	,m_IsCanPull( true )
	,m_fGrowTime( 0.0f )
	,m_IsOnGrow(  false )
{
}



cMonster::~cMonster(void)
{
	_GETSINGLE( cObjMgr )->CreateObject( OI_EFFECT, this->m_vPos,
		"bomb_effect"  );
}


void	cMonster::Init()
{
	m_fMinZ = rand() % 400 * 0.1f + 30.0f ;
	m_fOriMoveSpeed	=	10.0f;
	m_fBulletSpeed = 30.0f;
	m_fHp	=	50.0f;
	m_f	=	0.0f;
	m_vDirection = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	this->Translation();
	m_vOriScale = m_vScale;
}
void	cMonster::Update()
{
	if( m_vPos.z > 125.0f )
	{
		m_fMoveSpeed	=	m_vPos.z * 3.0f ;
	}
	else
	{
		m_fMoveSpeed = m_fOriMoveSpeed;
	}

	if( m_f > 0.0f )
	{
		m_f	-=	_GETSINGLE( cSystemMgr )->GetDeltaTime();
		m_vPos.x	+=	( rand() % 1000 * 0.01f - 5.0f ) * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 0.5f;
		m_vPos.z	+=	40.0f * _GETSINGLE( cSystemMgr )->GetDeltaTime();
	}



	this->Grow();
	this->SideMove();
	this->CheckSurvive();
	this->DirectionMove();
	this->Translation();
}
void	cMonster::Render()
{
	D3DXVECTOR4	vTemp	=	_GETSINGLE( cObjMgr )->m_vLight ;
	D3DXMATRIXA16	matRot;

	D3DXMatrixRotationYawPitchRoll( &matRot, m_vRotation.y, m_vRotation.x, m_vRotation.z );
	D3DXVECTOR3 v	=	D3DXVECTOR3( -0.5f, 1.0f, -1.3f  );
//	D3DXVec3TransformCoord( &v, &v, &matRot );
	_GETSINGLE( cObjMgr )->m_vLight = D3DXVECTOR4( v, 0.0f );

 	_GETSINGLE ( cResourceMgr )->SetRed( m_fRed );
	this->ModelRender( true, _GETSINGLE( cResourceMgr )->GetShader( SI_TOON ) );
	_GETSINGLE( cResourceMgr )->SetRed( 0.0f );
	_GETSINGLE( cObjMgr )->m_vLight =  vTemp;
	
}
void	cMonster::Release()
{
}

void	cMonster::OnCollision( int nTargetType, IObj* pObj )
{
	switch( nTargetType )
	{
	case OI_BULLET:
		m_fHp	-=	10.0f;
		m_f	+=	0.02f;
		this->RedOn();
		break;
	case OI_MONSTER:
		if( m_IsCanPull )
		{
			D3DXVECTOR3	vDist	=	m_vPos - pObj->GetPos();
			D3DXVec3Normalize( &vDist, &vDist );
			vDist *= 5.0f;

			vDist.y	=	0.0f;
			vDist.z	=	0.0f;
			m_vPos += vDist * _GETSINGLE( cSystemMgr )->GetDeltaTime();
		}
		break;
	}
}

void	cMonster::CheckSurvive()
{
	if( m_fHp < 0.0f || m_vPos.z < -50.0f )
	{
		m_fHp	=	0.0f;
		this->DestroyObject();
		
	}
}

void	cMonster::SideMove()
{
	const float fMinX = -8.0f;
	const float fMaxX = 6.0f;

	if( m_vPos.x < fMinX )
	{
		m_vDirection.x = 1.0f + ( fMinX - m_vPos.x + 0.5f ) * 0.1f;
	} 
	else if( m_vPos.x > fMaxX )
	{
		m_vDirection.x = -1.0f + ( fMaxX - m_vPos.x - 0.5f ) * 0.1f;
	}
	else
	{
		m_vDirection.x = 0.0f;
	}
}

void	cMonster::Grow()
{
	if( m_IsOnGrow )
	{
		if( m_IsGrow )
		{
			m_fGrowTime += _GETSINGLE( cSystemMgr )->GetDeltaTime();
			m_vScale += D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) * _GETSINGLE( cSystemMgr )->GetDeltaTime();
			if( m_fGrowTime > 0.1f )
			{
				m_fGrowTime	=	0.0f;
				m_IsGrow = false;
			}
		}
		else
		{
			m_vScale +=  ( m_vOriScale - m_vScale ) * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 2.0f;
		}
	}
}

void	cMonster::OnTimer( cTimer* pTimer )
{
	cCharacter::OnTimer( pTimer );

	switch( pTimer->nType )
	{
	case TT_GROW:
		m_IsGrow = true;
		break;
	}
}


void	cMonster::SettingGrow( float fTime )
{
	if( !m_IsOnGrow  )
	{
		m_IsOnGrow = true;
		this->AddChild( _GETSINGLE( cSystemMgr )->SetTimer( this, fTime, TT_GROW, true ) );
	}
}