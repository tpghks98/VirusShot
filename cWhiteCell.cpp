#include "DXUT.h"
#include "cWhiteCell.h"


cWhiteCell::cWhiteCell(void)
{
}


cWhiteCell::~cWhiteCell(void)
{
	_GETSINGLE( cObjMgr )->CreateObject( OI_ITEM, m_vPos );
}


void	cWhiteCell::Init()
{
	this->SettingGrow( 0.5f );
	m_vScale *= 0.35f;

	cMonster::Init();

	m_fHp			=	1000.0f;
	m_fOriMoveSpeed	=	20.0f;
	m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "whitecell" );
}

void	cWhiteCell::Render()
{
	m_vRotation.y += D3DX_PI * 0.5f * _GETSINGLE( cSystemMgr )->GetDeltaTime();

	D3DXVECTOR4	vTemp	=	_GETSINGLE( cObjMgr )->m_vLight ;
 	_GETSINGLE ( cResourceMgr )->SetRed( m_fRed );
	cMonster::Render();
	_GETSINGLE( cResourceMgr )->SetRed( 0.0f );
	_GETSINGLE( cObjMgr )->m_vLight =  vTemp;
}