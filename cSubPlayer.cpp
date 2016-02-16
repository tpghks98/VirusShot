#include "DXUT.h"
#include "cSubPlayer.h"


cSubPlayer::cSubPlayer(void)
{
	m_IsPlayer = false;
}


cSubPlayer::~cSubPlayer(void)
{
}

void	cSubPlayer::Init()
{
	m_fBulletSpeed	=	80.0f;
	m_vScale *= 1.0f;
	m_fMulti = 0.0f;
	m_vRotation = D3DXVECTOR3( -D3DX_PI * 0.5f,0.0f , 0.0f );
	m_IsNoMove = true;
	m_vDirection = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	
	m_nHowCanShotBullet	=	2;
	m_fShotCoolTime = 0.1f;
	m_fMoveSpeed	=	9.0F;
	m_fMaxX = 7.5f + m_vPos.x;
	m_fMinX = -7.5f + m_vPos.x;
	m_pResBullet = _GETSINGLE( cResourceMgr )->GetResourceFile( "bullet_pill" );
	m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "sub_player" );
	m_vQuatRotAxis = D3DXVECTOR3( 0, 0, 1 );
}
void	cSubPlayer::Update()
{
	this->KeyInput();
	this->Translation();
}
void	cSubPlayer::Render()
{
	this->ModelRender( true ,_GETSINGLE( cResourceMgr )->GetShader( SI_TOON ), false);	
}
void	cSubPlayer::Release()
{
}