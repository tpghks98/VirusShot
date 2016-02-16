#include "DXUT.h"
#include "cImageFile.h"
#include "cResourceMgr.h"
#include "cAlphaShader.h"
#include "IObj.h"

cImageFile::cImageFile(void)
	:m_IsBillBoard( false ),
	m_nMax( - 1 )
{
}


cImageFile::~cImageFile(void)
{
	for each( auto iter in m_vecTexture )
	{
		SAFE_RELEASE( iter );
	}
	m_vecTexture.clear();
}

void	cImageFile::AddTexture( LPDIRECT3DTEXTURE9	pTexture )
{
		++m_nMax;
		m_vecTexture.push_back( pTexture );
}

void	cImageFile::Render( IObj* pObj, bool IsAni,
		cBaseShader* pShader )
{
	if( IsAni )
	{
		float f = pObj->GetAniKey();
		f += _GETSINGLE( cSystemMgr )->GetDeltaTime();
		pObj->SetAniKey( f );
	}

	int nIndex = pObj->GetAniKey() * 10;

	if( nIndex > m_nMax )
	{
		nIndex = m_nMax;
		pObj->OnAnimationEnd();
	}

	if( nIndex < 0 )
	{
		nIndex =	0;
	}


	D3DXMATRIXA16	matWorld	=	pObj->GetWorldMatrix();

	LPDIRECT3DTEXTURE9	pTexture	=	m_vecTexture[nIndex];
	if( m_IsBillBoard )
	{
		D3DXMATRIXA16	matView;
		DXUTGetD3D9Device()->GetTransform( D3DTS_VIEW, &matView );

		memcpy( &matView._41, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), sizeof( D3DXVECTOR3 ) );
		                                                 
		D3DXMatrixTranspose( &matView, &matView );
		memcpy( &matView._41, &matWorld._41, sizeof( D3DXVECTOR3 ) );

		D3DXMATRIXA16	matScale;
		D3DXMatrixScaling( &matScale, pObj->GetScale().x, pObj->GetScale().y, 1.0f );

		matWorld	=	matScale * matView;
	}

	if( pShader != NULL )
	{
		if( pTexture )
		{
			 pShader->Setting( pTexture, &matWorld );
		}
		
		auto	pEffect	=	pShader->GetEffect();
		UINT	nPass	=	0;
		pEffect->Begin( &nPass, 0 );
		{
			for( int n =0; n< nPass; ++n )
			{
				pEffect->BeginPass( n );
				{
					this->DrawTexture( &matWorld, pTexture );
				}
				pEffect->EndPass();
			}
		}
		pEffect->End();
		
	}
	else
	{
		this->DrawTexture(  &matWorld, pTexture );
	}
}


void	cImageFile::DrawTexture( D3DXMATRIXA16* pWorld, LPDIRECT3DTEXTURE9 pTexture )
{
	DXUTGetD3D9Device()->SetRenderState( D3DRS_LIGHTING, false );
	DXUTGetD3D9Device()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	DXUTGetD3D9Device()->SetFVF( ST_PNT_VERTEX::FVF );
	DXUTGetD3D9Device()->
		SetStreamSource( 0, _GETSINGLE( cResourceMgr )->GetPlanVB(), 0,
		sizeof( ST_PNT_VERTEX ) );
	DXUTGetD3D9Device()->SetTransform( D3DTS_WORLD, pWorld );
	DXUTGetD3D9Device()->SetTexture( 0, pTexture );
	DXUTGetD3D9Device()->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

}