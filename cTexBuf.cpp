#include "DXUT.h"
#include "cTexBuf.h"


cTexBuf::cTexBuf(void)
{
}


cTexBuf::~cTexBuf(void)
{
	Release();
}


void	cTexBuf::Create( int nWidthSize, int nHeightSize )
{
	m_nWidth	=	nWidthSize;
	m_nHeight	=	nHeightSize;

	
	D3DXCreateTexture( DXUTGetD3D9Device()
		, m_nWidth
		, m_nHeight
		, 1
		, D3DUSAGE_RENDERTARGET
		, D3DFMT_A8R8G8B8
		, D3DPOOL_DEFAULT
		, &m_pTexture );

	m_pTexture->GetSurfaceLevel( 0, &m_pRenderTarget );

	DXUTGetD3D9Device()->GetRenderTarget( 0, &m_pOriRenderTarget );
	DXUTGetD3D9Device()->GetDepthStencilSurface( &m_pOriDepthSurface );

	D3DSURFACE_DESC dsc;
	m_pOriDepthSurface->GetDesc( &dsc );

	DXUTGetD3D9Device()->CreateDepthStencilSurface(
		  m_nWidth
		, m_nHeight
		, dsc.Format
		, D3DMULTISAMPLE_NONE
		, 0
		, true
		, &m_pDepthSurface
		, NULL );
}

void cTexBuf::Release()
{
	SAFE_RELEASE( m_pTexture );
	SAFE_RELEASE( m_pDepthSurface );
	SAFE_RELEASE( m_pRenderTarget );
	SAFE_RELEASE( m_pOriDepthSurface );
	SAFE_RELEASE( m_pOriRenderTarget );
}

void	cTexBuf::BeginScene()
{
	DXUTGetD3D9Device()->SetRenderTarget( 0, m_pRenderTarget );
	DXUTGetD3D9Device()->SetDepthStencilSurface( m_pDepthSurface );
}

void	cTexBuf::EndScene()
{
	DXUTGetD3D9Device()->SetRenderTarget( 0, m_pOriRenderTarget );
	DXUTGetD3D9Device()->SetDepthStencilSurface( m_pOriDepthSurface );	
}

LPDIRECT3DTEXTURE9	cTexBuf::GetTexture()
{
	return m_pTexture;
}