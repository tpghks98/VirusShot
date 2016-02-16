#include "DXUT.h"
#include "cButton.h"
#include "cTextureFile.h"
#include "cSceneMgr.h"

cButton::cButton(void)
	:m_IsVirusPatten( false )
	,m_fPattenTime( 0.0f )
	,m_vStart( g_vZero )
	,m_vEnd( g_vZero )
{
}


cButton::~cButton(void)
{
}


void	cButton::Init()
{
	
}
void	cButton::Update()
{
	if( m_IsVirusPatten )
	{
		VirusPatten();
	}

	POINT	pt	=	_GETSINGLE( cSystemMgr )->GetClientMouse();
	int nHeight = EASY_CAST( cTextureFile*, m_pResourceFile )->GetTextureNode( m_fAniKey )
		->dwHeight * 0.5f;
	int nWidth = EASY_CAST( cTextureFile*, m_pResourceFile )->GetTextureNode( m_fAniKey )
		->dwWidth * 0.5f;

	RECT	rt;
	SetRect( &rt
		, m_vPos.x - nWidth
		, m_vPos.y - nHeight
		, m_vPos.x + nWidth
		, m_vPos.y + nHeight );

	m_fAniKey = 0.0f;
	if( PtInRect( &rt, pt ) )
	{
		m_fAniKey = 0.1f;
		if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_LBUTTON ) == KS_DOWN )
		{
			m_fAniKey = 0.2f;
		}
		else if( _GETSINGLE( cSystemMgr )->GetKeyState( VK_LBUTTON ) == KS_UP )
		{
			_GETSINGLE( cSceneMgr )->ClickButton( m_pResourceFile->GetKey() );
		}
	}
	this->Translation();
}
void	cButton::Render()
{
	m_pResourceFile->Render( this );
}
void	cButton::Release()
{
}

void	cButton::VirusPatten()
{
	if( !m_IsAniDelete )
	{
		m_fPattenTime += _GETSINGLE( cSystemMgr )->GetDeltaTime();

		if( m_fPattenTime > 1.0f )
		{
			m_fPattenTime = 1.0f;
		}
	}
	else
	{
		m_fPattenTime -= _GETSINGLE( cSystemMgr )->GetDeltaTime();
		if( m_fPattenTime < 0.0f )
		{
			m_fPattenTime = 0.0f;
			m_IsDelete = true;
		}
	}

	D3DXVec3Lerp( &m_vPos, &m_vStart, &m_vEnd, m_fPattenTime );
}
