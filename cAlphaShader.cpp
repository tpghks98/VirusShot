#include "DXUT.h"
#include "cAlphaShader.h"
#include "cResourceMgr.h"

cAlphaShader::cAlphaShader(void)
{
}


cAlphaShader::~cAlphaShader(void)
{
}

void	cAlphaShader::Setting( LPDIRECT3DTEXTURE9 pTexture, D3DXMATRIXA16* pWorld )
{
	D3DXMATRIXA16 matProj, matView;

	DXUTGetD3D9Device()->GetTransform( D3DTS_PROJECTION, &matProj );
	DXUTGetD3D9Device()->GetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16	matWorldViewProj = (*pWorld) * matView * matProj;


	m_pEffect->SetFloat( (D3DXHANDLE)"g_fAlpha" , _GETSINGLE( cResourceMgr )->GetAlpha() );

	m_pEffect->SetMatrix( 
		(D3DXHANDLE)"g_mWorldViewProjection", &matWorldViewProj );
	m_pEffect->SetMatrix( 
		(D3DXHANDLE)"g_mWorld", pWorld);

	if( pTexture )
	{
		m_pEffect->SetTexture( (D3DXHANDLE)"g_MeshTexture", pTexture );
	}
}
