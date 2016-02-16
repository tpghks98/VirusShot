#include "DXUT.h"
#include "cEffect.h"
#include "cObjMgr.h"

cEffect::cEffect(void)
	:m_pTargetObject( NULL )
	,m_nEndCount( 1 )
	,m_fAlpha( 1.0f )
{
}


cEffect::~cEffect(void)
{
}

void	cEffect::Init()
{
	m_vPos.z += rand() % 20000 * 0.0001f;
	m_vScale *= 5.0f;

	if( m_pResourceFile->GetKey() == "bomb_effect" )
	{
		m_vScale *= 3.5f;
	}
	else if( m_pResourceFile->GetKey() == "power_effect" )
	{
		m_fAlpha	=	1.0f;
		if( _GETSINGLE( cObjMgr )->GetCanAcessPlayer() )
		{
			m_pTargetObject = _GETSINGLE( cObjMgr )->m_pPlayer;
		}
		m_vPos.z += 35.0f;
		m_vPos.y -= 2.0f;
		m_vRotation.x = D3DX_PI * 0.5f;
		m_vScale.y *= 24.0f;
		m_vScale *= 6.0f;
	}
	else if( m_pResourceFile->GetKey() == "wind_effect" )
	{
		m_vRotation.x = D3DX_PI * 0.5f;
		m_vScale.y *= 40.0f;
	}
	m_vPos.x -= m_vScale.x * 0.5f;
	m_vPos.y -= m_vScale.y * 0.5f;

}
void	cEffect::Update()
{
	if( m_pTargetObject != NULL && _GETSINGLE( cObjMgr )->GetCanAcessPlayer() )
	{
		m_vPos = m_pTargetObject->GetPos() + D3DXVECTOR3( -15.0f, -6.0f, 20.0f );
//		m_vRotation = m_pTargetObject->GetRotation();
	}
	this->Translation();
	if( m_pResourceFile->GetKey() == "power_effect" )
	{
		m_vPos.z = FLT_MAX;
	}
}
void	cEffect::Render()
{
	
	_GETSINGLE( cResourceMgr )->SetAlpha( m_fAlpha );
	_GETSINGLE( cObjMgr )->m_IsRim= false;
	DXUTGetD3D9Device()->SetRenderState( D3DRS_ZENABLE , false );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	this->ModelRender( true, _GETSINGLE( cResourceMgr )->GetShader( SI_TOON )  );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_ZENABLE , true );
	_GETSINGLE( cResourceMgr )->SetAlpha( 1.0f );
	_GETSINGLE( cObjMgr )->m_IsRim	= true;

}
void	cEffect::Release()
{
}

void	cEffect::OnAnimationEnd()
{
	m_fAniKey = 0.0f;
	if( m_nEndCount == INT_MAX )
	{
		return;
	}
	--m_nEndCount;
	if( m_nEndCount <= 0 )
	{
		DestroyObject();
	}
}