#include "DXUT.h"
#include "cPostMgr.h"
#include "cTexBuf.h"
#include "cSystemMgr.h"

cPostMgr::cPostMgr(void)
	:m_pBlurBuffer( NULL )
{

}


cPostMgr::~cPostMgr(void)
{
	SAFE_DELETE( m_pBlurBuffer );
}


void	cPostMgr::Initialize()
{
	m_fBlurClearTime	=	0.0f;
	if( m_pBlurBuffer == NULL )
	{
		m_pBlurBuffer = new cTexBuf();
		m_pBlurBuffer->Create( g_nWinSizeX, g_nWinSizeY );
	}
}
void	cPostMgr::Update()
{
	m_fBlurClearTime	+=	DXUTGetElapsedTime();

}

void	cPostMgr::Render()
{
	BlurRender();
	this->BeginBulr();

	DXUTGetD3D9Device()->Clear( 0L, NULL
	,   D3DCLEAR_ZBUFFER
	, D3DCOLOR_ARGB( 256, 0, 0, 0 ), 1.0f, 0L );
	if( m_fBlurClearTime > 0.15f )
	{
		m_fBlurClearTime	= 0.0f	;
		DXUTGetD3D9Device()->Clear( 0L, NULL
		,  D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_ARGB( 256, 45, 50, 170 ), 1.0f, 0L );
	}
	this->EndBlur();
}
void	cPostMgr::BeginBulr()
{
	m_pBlurBuffer->BeginScene();;
}
void	cPostMgr::EndBlur()
{
	m_pBlurBuffer->EndScene();
}


void	cPostMgr::BlurRender()
{
	if( g_pSprite9 != NULL )
	{
		RECT	rt;
		SetRect( &rt, 0, 0, g_nWinSizeX, g_nWinSizeY );
		D3DXMATRIXA16	matWorld;
		D3DXMatrixIdentity( &matWorld );
		g_pSprite9->SetTransform( &matWorld );
		g_pSprite9->Begin( D3DXSPRITE_ALPHABLEND );
		g_pSprite9->Draw( m_pBlurBuffer->GetTexture(), &rt, NULL, NULL, D3DXCOLOR( 1, 1, 1, 0.1f ) );
		g_pSprite9->End();
	}
}