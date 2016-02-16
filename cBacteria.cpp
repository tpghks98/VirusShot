#include "DXUT.h"
#include "cBacteria.h"


cBacteria::cBacteria(void)
{
}


cBacteria::~cBacteria(void)
{
}

void	cBacteria::Init()
{
	
	this->SettingGrow( 0.9f );
	m_vScale *= 0.5f;

	cMonster::Init();
//	m_vRotation.z = D3DX_PI * 0.5f;
	m_fHp	=	200.0f;

	char* pKey = "bacteria";
	switch( _GETSINGLE( cObjMgr )->GetSellectStage() )
	{
	case 1:
		pKey = "bacteria";
		break;
	case 2:
		if( rand() % 4 )
		{
			pKey = "virus_stage2";
			m_vRotation.z = D3DX_PI;
			m_vPos.y = -10.0f;
		}
		break;
	}
	m_pResourceFile = _GETSINGLE( cResourceMgr )->GetResourceFile( pKey );
}
void	cBacteria::Update()
{
	if( m_vDirection == g_vZero )
	{
		int a = 10;
	}
	cMonster::Update();
	this->DirectionRotation();
	if( m_vDirection == g_vZero )
	{
		int a = 10;
	}
}
void	cBacteria::Render()
{

	cMonster::Render();

}