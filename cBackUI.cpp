#include "DXUT.h"
#include "cBackUI.h"
#include "cObjMgr.h"

cBackUI::cBackUI(void)
	:m_fScale( 0.0f )
{
}


cBackUI::~cBackUI(void)
{
}

void	cBackUI::Init()
{
	m_fScalingSpeed = 0.25f;
	m_IsOnceUpdating = false;
	m_fStartScale = 2.0f;
	m_fEndScale = 1.0f;
}
void	cBackUI::Update()
{
	if( m_IsAniDelete )
	{
		m_fScale -= (m_fScale + 1.5f)
			* _GETSINGLE( cSystemMgr )->GetDeltaTime();
		if( m_fScale <= 0.0f )
		{
			m_IsDelete = true;
		}
	}
	if( !m_IsOnceUpdating )
	{
		m_IsOnceUpdating = true;
		_GETSINGLE( cSystemMgr )->SetSmooth( &m_fScale, m_fStartScale, m_fEndScale, m_fScalingSpeed );
	}
	m_vScale = D3DXVECTOR3( m_fScale, m_fScale, 1.0f );
	this->Translation();
}
void	cBackUI::Render()
{
	m_pResourceFile->Render( this );
}
void	cBackUI::Release()
{
}