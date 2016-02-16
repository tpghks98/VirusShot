#include "DXUT.h"
#include "cPlayer.h"
#include "cAseFile.h"
#include "cSystemMgr.h"
#include "cTimer.h"
#include "cTexBuf.h"
#include "cEffect.h"
#include "cGaugeUI.h"
#include "cCamera.h"
#include "cSceneMgr.h"

cPlayer::cPlayer(void)
	:m_IsPlayer( true )
	,m_nHowCanShotBullet( 1 )
	,m_pKey( NULL )
	,m_IsNoMove( false )
	,m_fMaxX( 0.0f )
	,m_fMinX( 0.0f )
	,m_fMulti( 0.0f )
	,m_fKnockBack( 0.0f )
	,m_IsPower( false )
	,m_fPowerTime( 0.0f )
	,m_pHp( NULL )
	,m_pPg( NULL )
	,m_fPG( 0.0f )
{
	m_pKey = "player";
}


cPlayer::~cPlayer(void)
{
	Release();
}


void	cPlayer::Init()
{
	m_IsOnceDir=  true;
	m_fHp = 100.0f;

	m_pPg = (cGaugeUI*) _GETSINGLE( cObjMgr )->CreateObject( OI_GAUGE_UI, D3DXVECTOR3( 200.0f, 716.0f, 0.0f ), "ui_pg_bar" );
	m_pHp = (cGaugeUI*)_GETSINGLE( cObjMgr )->CreateObject( OI_GAUGE_UI, D3DXVECTOR3( 200.0f, 620.0f, 0.0f ), "ui_hp_bar" );
	m_pHp->SetScale( D3DXVECTOR3( 1.0f, -1.0f, 1.0f ) );
	m_pHp->SetDelayTime( 2.0f );
	m_pPg->SetDelayTime( 2.0f );
	m_pHp->SetMaxGauge( m_fHp );
	m_pPg->SetMaxGauge( m_fHp );

	m_fKnockBack	=	0.0f;
	m_fBulletSpeed = 100.0f;

	m_nHowCanShotBullet	=	2;
	m_fMaxX	=	7.5f;
	m_fMinX	=	-7.5f;

	m_vRotation = D3DXVECTOR3( D3DX_PI * 0.5f, 0.0f, 0.0f );
	m_vScale *= 0.5f;
  	m_fMulti = 10.0f;
	m_IsNoMove = true;

	m_vDirection = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_vPos = D3DXVECTOR3( 0.0f, 0.0f, -20.0f );
	m_fShotCoolTime = 0.1f;
	m_fMoveSpeed	=	9.0F;
	m_pResBullet = _GETSINGLE( cResourceMgr )->GetResourceFile( "bullet_pill" );
	m_pResourceFile	=	_GETSINGLE( cResourceMgr )->GetResourceFile( m_pKey );

	this->AddChild( _GETSINGLE( cObjMgr )->CreateObject( OI_SUB_PLAYER, D3DXVECTOR3( -1.8f * 3, 0.0f, 0.0f )) );
	this->AddChild( _GETSINGLE( cObjMgr )->CreateObject( OI_SUB_PLAYER, D3DXVECTOR3( 2.6f * 3, 0.0f, 0.0f )) );

	_GETSINGLE( cSystemMgr )->GetCameara()->SetTarget( &m_vPos );

	m_fRotQuat = 0.0f;
	m_fLRDir = 0.0f;

	m_vQuatRotAxis = D3DXVECTOR3( 0, 0, 1 );
} 

void	cPlayer::Update()
{	
	if( m_fHp <= 0.0f || m_fPG >= 100.0f )
	{
	//	_GETSINGLE( cSceneMgr )->ChangeScene( SI_HOME );
	}


	if( _GETSINGLE( cSystemMgr )->GetKeyState( 'A' ) == KS_ONCE )
	{
		if( !m_IsPower )
		{
		//	_GETSINGLE( cObjMgr )->OnPlayerPower();
			m_IsPower = true;
			for( int n = 0; n < 4; ++n )
			{
				EASY_CAST( cEffect*, _GETSINGLE( cObjMgr )->CreateObject( OI_EFFECT, m_vPos, "power_effect" ) ) ->SetEndCount( 3 );
				auto pObj = EASY_CAST( cEffect*, _GETSINGLE( cObjMgr )->CreateObject( OI_EFFECT, m_vPos, "power_effect" ) );
				pObj->SetEndCount( 3 );
				pObj->SetRotation(  D3DXVECTOR3( D3DX_PI * 0.5f, D3DX_PI * 0.5f * n ,D3DX_PI * 0.5f * n) );
			}
			this->AddChild( _GETSINGLE( cSystemMgr )->SetTimer( this, 2.0f, TT_POWER, false ) );

		}
	}
	if( m_IsPower )
	{
		m_fPowerTime += _GETSINGLE( cSystemMgr )->GetDeltaTime();
		_GETSINGLE( cSystemMgr )->CameraShake( 0.2f );

		if( m_fPowerTime > 0.05f )
		{
			m_fPowerTime = 0.0f;
			_GETSINGLE( cObjMgr )->AllMonsterAttacked();
		}
	}


	if( m_fPG > 0.0f )
	{
		m_fPG -= _GETSINGLE( cSystemMgr )->GetDeltaTime() * 0.25f;
	}
	m_pHp->TransmitGauge( m_fHp );
	m_pPg->TransmitGauge( m_fPG );
	this->KeyInput();
	this->Translation();

}

void	cPlayer::Render()
{
	DXUTGetD3D9Device()->SetRenderState( D3DRS_ALPHABLENDENABLE, true );

	_GETSINGLE ( cResourceMgr )->SetRed( m_fRed );
	this->ModelRender( true ,_GETSINGLE( cResourceMgr )->GetShader( SI_TOON ), false);
	 _GETSINGLE ( cResourceMgr )->SetRed( 0.0f); 
	DXUTGetD3D9Device()->SetRenderState( D3DRS_ALPHABLENDENABLE, false );

}


void	cPlayer::KeyInput()
{
	if( m_IsPlayer )
	{
		Move();
		Rotation();
	}

	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_SPACE ) == KS_DOWN )
	{
 		if( m_IsCanShot )                                                                                                                      
		{
			float fMinus =  10.0f * _GETSINGLE( cSystemMgr )->GetDeltaTime();
			m_vPos.z -= fMinus;
			m_fKnockBack += fMinus;
			if( m_fMulti > 0.0f )
			{
				m_fMulti -= 2.0f;
				Shot( OI_MONSTER, 15);
			}
			else
			{
				float fTempX = m_matWorld._41;
				m_matWorld._41 -= 0.3f;
				Shot( OI_MONSTER, 1, true);
				if( m_nHowCanShotBullet >= 2 )
				{
					m_matWorld._41  += 0.6f;
					Shot( OI_MONSTER, 1, false);
				}

				m_matWorld._41  = fTempX;
			}
		}
	}
	KnockBack();
}

void	cPlayer::KnockBack()
{
	if( m_fKnockBack > 0.0f )
	{
		float fMinus = 3.0f * _GETSINGLE( cSystemMgr )->GetDeltaTime();

		m_fKnockBack -= fMinus;
		if( m_fKnockBack < 0.0f )
		{
			fMinus += m_fKnockBack;
			m_fKnockBack = 0.0f;
		}
		m_vPos.z += fMinus;
	}
}
void	cPlayer::Release()
{
	_GETSINGLE( cSystemMgr )->GetCameara()->SetTarget( NULL );
}

void	cPlayer::Rotation()
{

	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_LEFT ) == KS_DOWN)
	{
		m_fLRDir  = 1.0f;
	}
	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_RIGHT ) == KS_DOWN )
	{
		m_fLRDir  = -1.0f;
	}
	m_fRotQuat += m_fLRDir *  D3DX_PI * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 1.5f;


	D3DXQuaternionRotationAxis(  &m_quatLookAt, &m_vQuatRotAxis, m_fRotQuat );
}
void	cPlayer::Move()
{
	D3DXVECTOR3	vPlus	=	g_vZero;
	D3DXVECTOR3 vAt = _GETSINGLE( cSystemMgr )->GetCamera_At();

	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_LEFT ) == KS_DOWN )
	{
		m_IsNoMove = false;
		vPlus.x -= m_fMoveSpeed;
	}
	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_RIGHT ) == KS_DOWN )
	{
		m_IsNoMove = false;
		vPlus.x += m_fMoveSpeed;
	}
	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_UP) == KS_DOWN )
	{
		vPlus.z += m_fMoveSpeed * 2.0f;
	}
	if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_DOWN ) == KS_DOWN )
	{
		vPlus.z -= m_fMoveSpeed * 2.0f;
	}

	D3DXVECTOR3	vTemp	= m_vPos + vPlus * _GETSINGLE( cSystemMgr )->GetDeltaTime();

	if( vTemp.z < 5.0f )
	{	
		vPlus.z = 0.0f;
	//	vPlus.x = 0.0f;
	}
	if( vTemp.x < m_fMinX || vTemp.x > m_fMaxX )
	{
		vPlus.x = 0.0f;
	}
	if( m_IsOnceDir )
	{
		m_vPos.z += _GETSINGLE( cSystemMgr )->GetDeltaTime() * 16.0f;
		if( m_vPos.z > 12.0f )
		{
			m_IsOnceDir = false;
		}
	}

	m_vPos += vPlus * _GETSINGLE( cSystemMgr )->GetDeltaTime();
	vAt += vPlus * _GETSINGLE( cSystemMgr )->GetDeltaTime() * 0.05f;
	_GETSINGLE( cSystemMgr )->SetCamera_At( vAt );



	if( !m_IsNoMove && vPlus == g_vZero )
	{
		if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_LEFT ) ==KS_NONE &&
			_GETSINGLE( cSystemMgr )->GetKeyState( VK_RIGHT ) ==KS_NONE  )
		{
		m_IsNoMove = true;
//		_GETSINGLE( cSystemMgr )->SetSmooth( &m_vRotation.z, m_vRotation.z, D3DX_PI * 0.0f );			
	}
}
}

void	cPlayer::OnTimer( cTimer* pTimer )
{
	cCharacter::OnTimer( pTimer );

	switch( pTimer->nType )
	{
	case TT_MULTI:
		m_fMulti += 10.0f;
		break;
	case TT_POWER:
		m_IsPower	=	false;
		break;
	}

}

void	cPlayer::OnCollision( int nTargetType, IObj* pObj )
{
	switch( nTargetType )
	{
	case OI_MONSTER:
		if( m_fRed <= 0.1f )
		{
			AttackedDamagae( 10 );
		} 
		this->RedOn();
		_GETSINGLE( cSystemMgr )->CameraShake( 3.0f );

		break;
	case OI_ENEMYBULLET:
		this->RedOn();
		_GETSINGLE( cSystemMgr )->CameraShake( 3.0f );
		AttackedDamagae( 10 );
		break;
	case OI_ITEM:
		PickUpItem( pObj->GetResourceFile()->GetKey() );
		break;
	}
}

void	cPlayer::AttackedDamagae( int nDamage )
{
	if( m_IsGuard )
	{
		m_IsGuard = false;
	}
	else
	{
		m_fHp -= nDamage;
	}
}

void	cPlayer::PickUpItem( char* pName )
{
	if( pName == "item_hp_heal" )
	{
		m_fHp += 20.0f;
		if( m_fHp > 100.0f )
		{
			m_fHp = 100.0f;
		}
	}
	else if( pName == "item_pg_heal" )
	{
		m_fPG -= 40.0f;
		if( m_fPG < 0.0f )
		{
			m_fPG = 0.0f;
		}
	}
	else if( pName == "item_guard" )
	{
		m_IsGuard = true;
	}
	else if( pName == "item_bullet" )
	{
		m_fMulti += 100.0f;
	}
}


void	cPlayer::PlusPG( float fPG )
{
	m_fPG += fPG;
	if( m_fPG > 100.0f )
	{
		m_fPG = 100.0f;
	}
}