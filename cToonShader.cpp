#include "DXUT.h"
#include "cToonShader.h"
#include "cGeomNode.h"
#include "cObjMgr.h"
#include "cResourceMgr.h"

cToonShader::cToonShader(void)
{
}


cToonShader::~cToonShader(void)
{
}

void	cToonShader::Setting( cGeomNode* pNode )
{
	D3DXMATRIXA16 matProj, matView;

	DXUTGetD3D9Device()->GetTransform( D3DTS_PROJECTION, &matProj );
	DXUTGetD3D9Device()->GetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16	matWorldViewProj = pNode->m_matWorldTM * matView * matProj;

	
	m_pEffect->SetMatrix( 
		(D3DXHANDLE)"g_mWorldViewProjection", &matWorldViewProj );
	m_pEffect->SetMatrix( 
		(D3DXHANDLE)"g_mWorld", &pNode->m_matWorldTM );

	D3DXVECTOR4	v( 1.0f, 0.0f, 1.0f, 0.0f );
	v = _GETSINGLE( cObjMgr )->m_vLight;
	D3DXVec4Normalize( &v, &v );

	m_pEffect->SetVector( (D3DXHANDLE)"g_LightDir", &v );

	D3DXMATRIXA16 matInvWorldView = pNode->m_matWorldTM * matView;

	D3DXMatrixInverse( &matInvWorldView, NULL, &matInvWorldView );
	D3DXMatrixTranspose( &matInvWorldView, &matInvWorldView );
	m_pEffect->SetMatrix( (D3DXHANDLE)"g_mInvWorldView", &matInvWorldView );
	m_pEffect->SetMatrix( (D3DXHANDLE)"g_mProj", &matProj );

	v = D3DXVECTOR4( matView._41, matView._42, matView._43, 0.0f );

	m_pEffect->SetVector( (D3DXHANDLE)"g_vCameraPos", &v );
	m_pEffect->SetBool( (D3DXHANDLE)"g_IsRim" , _GETSINGLE( cObjMgr )->m_IsRim );
	m_pEffect->SetBool( (D3DXHANDLE)"g_IsLine" , _GETSINGLE( cObjMgr )->m_IsLine );
	m_pEffect->SetBool( (D3DXHANDLE)"g_IsEdge" , _GETSINGLE( cObjMgr )->m_IsEdge );
	m_pEffect->SetFloat( (D3DXHANDLE)"g_fRed", _GETSINGLE( cResourceMgr )->GetRed() );
	m_pEffect->SetFloat( (D3DXHANDLE)"g_fLighting", _GETSINGLE( cObjMgr )->m_fLighting );

	if( pNode->m_pTexMtl != NULL )
	{
		m_pEffect->SetTexture( (D3DXHANDLE)"g_MeshTexture", pNode->m_pTexMtl->pTex );
	}
}
void	cToonShader::Setting( LPDIRECT3DTEXTURE9 pTexture, D3DXMATRIXA16* pWorld )
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
	D3DXVECTOR4	v( 1.0f, 0.0f, 1.0f, 0.0f );
	v = _GETSINGLE( cObjMgr )->m_vLight;
	D3DXVec4Normalize( &v, &v );

	m_pEffect->SetVector( (D3DXHANDLE)"g_LightDir", &v );

	D3DXMATRIXA16 matInvWorldView = (*pWorld) * matView;

	D3DXMatrixInverse( &matInvWorldView, NULL, &matInvWorldView );
	D3DXMatrixTranspose( &matInvWorldView, &matInvWorldView );
	m_pEffect->SetMatrix( (D3DXHANDLE)"g_mInvWorldView", &matInvWorldView );
	m_pEffect->SetMatrix( (D3DXHANDLE)"g_mProj", &matProj );

	v = D3DXVECTOR4( matView._41, matView._42, matView._43, 0.0f );

	m_pEffect->SetVector( (D3DXHANDLE)"g_vCameraPos", &v );
	m_pEffect->SetBool( (D3DXHANDLE)"g_IsRim" , _GETSINGLE( cObjMgr )->m_IsRim );
	m_pEffect->SetBool( (D3DXHANDLE)"g_IsLine" , _GETSINGLE( cObjMgr )->m_IsLine );
	m_pEffect->SetBool( (D3DXHANDLE)"g_IsEdge" , _GETSINGLE( cObjMgr )->m_IsEdge );
	m_pEffect->SetFloat( (D3DXHANDLE)"g_fRed", _GETSINGLE( cResourceMgr )->GetRed() );
	m_pEffect->SetFloat( (D3DXHANDLE)"g_fLighting", _GETSINGLE( cObjMgr )->m_fLighting );


	if( pTexture )
	{
		m_pEffect->SetTexture( (D3DXHANDLE)"g_MeshTexture", pTexture );
	}
}

