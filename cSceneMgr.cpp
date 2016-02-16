#include "DXUT.h"
#include "cSceneMgr.h"
#include "cPlayScene.h"
#include "cHomeScene.h"
#include "cObjMgr.h"
#include "cFade.h"
#include "cButton.h"

cSceneMgr::cSceneMgr(void)
	:m_pScene( NULL )
	,m_fFade( 1.0f )
	,m_fFadePlus( 0.0f )
	,m_IsFade( false )
	,m_nSceneID( 0 )
	,m_pFade( NULL )
	,m_pUIName( NULL )
{
}


cSceneMgr::~cSceneMgr(void)
{
}

void	cSceneMgr::Init()
{
	m_pFade	=	(cFade*)_GETSINGLE( cObjMgr )->CreateObject( OI_FADE, 
		D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0.0f ), "ui_black_background" );

	m_fFadePlus = 1.0f;
	ChangeScene( SI_HOME );
}

void	cSceneMgr::Update()
{
	if( m_IsFade )
	{
		m_fFade += m_fFadePlus * _GETSINGLE( cSystemMgr )->GetDeltaTime();
		if( m_fFade < 0.0f )
		{
			m_IsFade = false;
			m_fFade	=	0.0f;
		}
		else if( m_fFade > 1.0f )
		{
			AssignScene();
			m_fFadePlus = -1.0f;
			m_fFade = 1.0f;
		}
	}
	m_pFade->SetAlpha( m_fFade );
	if( m_pUIName != NULL )
	{
		_GETSINGLE( cObjMgr )->UIChange( m_pUIName );
		m_pUIName = NULL;

	}
}

void	cSceneMgr::Render()
{
}


void	cSceneMgr::ChangeScene( int nID )
{
	if( !m_IsFade )
	{
		m_fFadePlus = 1.0f;
		m_nSceneID = nID;
		m_IsFade	=	true;
	}
}

void	cSceneMgr::AssignScene()
{
	SAFE_DELETE( m_pScene );
	_GETSINGLE( cObjMgr )->AllDestroyObject();
	m_pFade	=	(cFade*)_GETSINGLE( cObjMgr )->CreateObject( OI_FADE, 
		D3DXVECTOR3( g_nWinSizeX * 0.5f, g_nWinSizeY * 0.5f, 0.0f ), "ui_black_background" );
	switch( m_nSceneID )
	{
	case SI_HOME:
		m_pScene	=	new cHomeScene();
		break;
	case SI_PLAY:
		m_pScene	=	new	cPlayScene();
		break;
	}
	m_pScene->Init();

}

void	cSceneMgr::ClickButton( char* pName )
{
	if( pName == "button_start" )
	{
		ChangeScene( SI_PLAY );
	}
	else if( pName == "button_howto" )
	{
		m_pUIName = pName;
	}
	else if( pName == "button_about" )
	{
		m_pUIName = pName;
	}
	else if( pName == "button_main" )
	{
		m_pUIName = pName;
	}
}

void	cSceneMgr::ChangeUI()
{
	m_pScene->Init();
	m_pUIName = NULL;
}

void	cSceneMgr::CreateVirusButton(  D3DXVECTOR3 vPos, char* pKey )
{
	cButton* pButton =
	static_cast<cButton*>( _GETSINGLE( cObjMgr )->CreateObject( OI_BUTTON, 
			vPos, pKey ) );
	pButton->SetVirusPatten( true );
	pButton->SetStartPos( vPos + D3DXVECTOR3( 1500 - vPos.x, 0, 0 ) );
	pButton->SetEndPos( vPos );
}