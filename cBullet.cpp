#include "DXUT.h"
#include "cBullet.h"
#include "cObjMgr.h"

cBullet::cBullet(void)
{
}


cBullet::~cBullet(void)
{
}


void	cBullet::Init()
{
	if( m_pResourceFile->GetKey() == "virus" )
	{
		m_vScale	*=	0.1f;
	}
//	m_vRotation.z = D3DX_PI;
	if( m_pResourceFile->GetKey() == "bullet_pill" )
	{
		m_vRotation.x = D3DX_PI * 0.5f;
	}
	m_vScale *= 0.3f;
	m_fMoveSpeed = 100.0f;
}
void	cBullet::Update()
{ 
	if( m_pResourceFile->GetKey() == "virus" )
	{
		m_vRotation.y += 0.25f * D3DX_PI * _GETSINGLE( cSystemMgr )->GetDeltaTime();

	}
	if( m_vPos.z > 200.0f || m_vPos.z < -50.0f )
	{
		DestroyObject();
	}
	DirectionMove();
	DirectionRotation();
	Translation();
}
void	cBullet::Render()
{
	D3DXVECTOR4	vTemp	=	_GETSINGLE( cObjMgr )->m_vLight ;
	_GETSINGLE( cObjMgr )->m_vLight = D3DXVECTOR4( -0.5f, 1.0f, -1.3f, 0.0f );
	this->ModelRender( false, _GETSINGLE( cResourceMgr )->GetShader( SI_TOON ) , true );
	_GETSINGLE( cObjMgr )->m_vLight = vTemp;
}
void	cBullet::Release()
{
}

void	cBullet::OnCollision( int nTargetType, IObj* pObj )
{
	this->DestroyObject();
	_GETSINGLE( cObjMgr )->CreateObject( OI_EFFECT, this->m_vPos,
		"hit_effect" );
	_GETSINGLE( cSystemMgr )->CameraShake( 0.05 + rand() % 1000 * 0.000002f );
}
