#include "DXUT.h"
#include "cVirus.h"


cVirus::cVirus(void)
	:m_nCount( 0 ) 
{
}


cVirus::~cVirus(void)
{
}


void	cVirus::Init()
{
	m_vScale *= 0.4f;

	cMonster::Init();

	m_fOriMoveSpeed	=	10.0f;
	m_fHp	=	500.0f;
	m_fBulletSpeed = 25.0f;
	m_pResourceFile	=	_GETSINGLE( cResourceMgr )->GetResourceFile( "virus" );
	m_pResBullet	=	_GETSINGLE( cResourceMgr )->GetResourceFile( "bullet_pill" );
	m_vOriScale	=	m_vScale;

	m_IsCanShot = false;
	this->AddChild( (cBaseObject*)
			_GETSINGLE( cSystemMgr )->SetTimer( this, 1.0f, TT_SHOT ) );
}

void	cVirus::Update()
{
	m_vRotation.y += 0.25f * D3DX_PI * _GETSINGLE( cSystemMgr )->GetDeltaTime();
	cMonster::Update();
	m_IsGrow	=	false;
	if( m_vPos.z < 125.0f && m_vPos.z > 10.0f  )
	{
		m_vDirection.z = -1.0f;
		VirusShot();
		m_vDirection.z = 0.0f;
	}
	else
	{
		m_vDirection.z = -1.0f;
	}

}
void	cVirus::VirusShot()
{
	if( m_IsCanShot  )                                                                                                                      
		{
			D3DXVECTOR3	vPos	=	m_vPos;
			m_IsGrow	=	true;
			switch ( rand() % 3 )
			{
			case 0:
				m_fShotRot	=	0.5f;
				m_fShotCoolTime	=	0.3f;
				m_vPos.x -= 0.3f;
				Shot( OI_PLAYER, 1, true);
				m_vPos.x += 0.6f;
				Shot( OI_PLAYER, 1, false);
				m_vPos = vPos;
				break;
			case 1:
				m_fShotRot = 1.0f;
				m_fShotCoolTime = 4.0f;
				Shot( OI_PLAYER, 20, true );
				break;
			case 2:
				m_fShotCoolTime	=	0.6f;
				m_fShotRot	=	0.3f;
				Shot( OI_PLAYER, 4, true );
				break;
				
			}
		}
}

void	cVirus::Render()
{
	_GETSINGLE( cObjMgr )->m_fLighting = 0.75f;
	cMonster::Render();
	_GETSINGLE( cObjMgr )->m_fLighting = 1.0f;

}