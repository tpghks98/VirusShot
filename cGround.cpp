#include "DXUT.h"
#include "cGround.h"
#include "cResourceMgr.h"
#include "cObjMgr.h"

cGround::cGround(void)
{
}


cGround::~cGround(void)
{
}


void	cGround::Init()
{
	m_vScale.x *= 1.0f;
	m_vScale.y *= 1.0f;
	m_vDirection = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	m_fMoveSpeed	=	500.0F;
	const char* pKey = "ground";

	
	if( m_pResourceFile == NULL )
	{
		m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( pKey );
	}
}
void	cGround::Update()
{
	ScrollMove();
	this->Translation();
}
void	cGround::Render()
{
	_GETSINGLE( cObjMgr )->m_IsLine = false;
	_GETSINGLE( cObjMgr )->m_IsRim 
		= false;

	cBaseShader* pShader = NULL;
	if( m_pResourceFile->GetKey() == "ground" )
	{
		 pShader =
			 _GETSINGLE( cResourceMgr )->GetShader( SI_TOON );
	}

	this->ModelRender( false, pShader);
	_GETSINGLE( cObjMgr )->m_IsRim = true;
	_GETSINGLE( cObjMgr )->m_IsLine = true;

}
void	cGround::Release()
{
}

void	cGround::ScrollMove()
{
	m_vPos += m_vDirection * m_fMoveSpeed * _GETSINGLE( cSystemMgr )->GetDeltaTime();
	if( m_vPos.z < -320.0f )
	{
		m_vPos.z = 4200.0f + ( m_vPos.z + 320 );
	}
}