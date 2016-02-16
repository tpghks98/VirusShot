#include "DXUT.h"
#include "cItem.h"
#include "cObjMgr.h"


cItem::cItem(void)
{
}


cItem::~cItem(void)
{
}


void	cItem::Init()
{
	m_vPos.y += 0.5f;
	m_vScale *= 0.35f;
	m_fMoveSpeed	=	15.0f;
	switch( rand() % 4 )
	{
	case 0:
		m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "item_hp_heal" );
		break;
	case 1:
		m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "item_bullet" );
		break;
	case 2:
		m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "item_pg_heal" );
		break;
	case 3:
		m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( "item_guard" );
		break;
	}
}
void	cItem::Update()
{
	m_vPos.z -= m_fMoveSpeed * _GETSINGLE( cSystemMgr )->GetDeltaTime();
	this->Translation(); 
}
void	cItem::Render()
{
	D3DXVECTOR4	vTemp	=	_GETSINGLE( cObjMgr )->m_vLight ;
	D3DXVECTOR3 v	=	D3DXVECTOR3( -0.5f, 1.0f, -1.3f  );
	_GETSINGLE( cObjMgr )->m_vLight = D3DXVECTOR4( v, 0.0f );

	this->ModelRender( false, _GETSINGLE( cResourceMgr )->GetShader(SI_TOON) );
	_GETSINGLE( cObjMgr )->m_vLight =  vTemp;

}
void	cItem::Release()
{
}   

void	cItem::OnCollision( int nTargetType, IObj* pObj )
{
	if( nTargetType == OI_PLAYER )
	{
		DestroyObject();
	}
}
