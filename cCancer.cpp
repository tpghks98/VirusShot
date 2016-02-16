#include "DXUT.h"
#include "cCancer.h"
#include "cCamera.h"
#include "cBackUI.h"

cCancer::cCancer(void)
	:m_IsOnceDir( true )
{
}


cCancer::~cCancer(void)
{
	_GETSINGLE( cObjMgr )->CreateBackUiTime( 0.0f, 1.0f, 5.0f, 
		D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0 ), "ui_gameclear" );
	_GETSINGLE( cObjMgr )->SetGameClear( true );
}


void	cCancer::Init()
{
	_GETSINGLE( cObjMgr )->CreateBackUiTime( 0.0f, 1.0f, 5.0f, 
		D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0 ), "ui_boss" );

	m_pResBullet	=	_GETSINGLE( cResourceMgr )->GetResourceFile( "bullet_pill" );

	m_IsOnceDir = true;
	m_pCamera = _GETSINGLE( cSystemMgr )->CreateCamera();
	m_pCamera->SetTarget( &m_vPos );
	m_pCamera->SetEye(  D3DXVECTOR3( 0.0f, 20.0f, 100.0f) );

	m_vScale *= 0.8f;

	cMonster::Init();
	m_IsCanPull=  false;

	m_fHp = 5000.0f;

	char* pKey = "cancer";
	switch( _GETSINGLE( cObjMgr )->GetSellectStage() )
	{
	case 1:
		pKey = "cancer";
		break;
	case 2:
		pKey = "two_cancer";
		m_fHp *= 2.0f;
		m_vPos.x -= 18.0f;
		break;

	}
	m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( pKey );
	this->AddChild( (cBaseObject*)
			_GETSINGLE( cSystemMgr )->SetTimer( this, 1.0f, TT_SHOT ) );

}

void	cCancer::Update()
{
	if( m_IsOnceDir )
	{
		if( m_vPos.z > 200.0f )
		{
			m_vPos.z += -1.0f * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 100.0f;
		}
		else if( m_vPos.z <= 200.0f )
		{
			CancerShot();
			if( m_pCamera != NULL )
			{
				m_pCamera->SetDelete( true );
				m_pCamera = NULL;
			}
		}
	}
	this->CheckSurvive();
	this->Translation();
}
void	cCancer::CancerShot()
{
	if( m_IsCanShot  )                                                                                                                      
		{
			D3DXVECTOR3	vPos	=	m_vPos;
			m_IsGrow	=	true;
			switch ( rand() % 3 )
			{
			case 0:
				m_fShotRot	=	0.5f;
				m_fShotCoolTime	=	0.2f;
				m_vPos.x -= 0.3f;
				Shot( OI_PLAYER, 2, true, D3DXVECTOR3( 3, 3, 3 ));
				m_vPos.x += 0.6f;
				Shot( OI_PLAYER, 2, false, D3DXVECTOR3( 3, 3, 3 ));
				m_vPos = vPos;
				break;
			case 1:
				m_fShotRot = 1.0f;
				m_fShotCoolTime = 2.0f;
				Shot( OI_PLAYER, 20, true , D3DXVECTOR3( 3, 3, 3 ));
				break;
			case 2:
				m_fShotCoolTime	=	0.4f;
				m_fShotRot	=	0.3f;
				Shot( OI_PLAYER, 8, true , D3DXVECTOR3( 3, 3, 3 ));
				break;
				
			}
		}
}

void	cCancer::Render()
{
	_GETSINGLE( cObjMgr )->m_fLighting  = 0.6f;
	cMonster::Render();
	_GETSINGLE( cObjMgr )->m_fLighting  = 1.0f;
}