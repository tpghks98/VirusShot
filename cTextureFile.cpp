#include "DXUT.h"
#include "cTextureFile.h"
#include "IObj.h"

cTextureFile::cTextureFile(void)
	:m_MaxIndex( -1 )
{
}


cTextureFile::~cTextureFile(void)
{
}


void	cTextureFile::Render( IObj* pObj,bool IsAni, cBaseShader* pShader )
{
	if(IsAni )
	{
		float	f = pObj->GetAniKey() + _GETSINGLE( cSystemMgr )->GetDeltaTime();

		pObj->SetAniKey( f );
	}

	int	nIndex	=	pObj->GetAniKey() * 10.0f;
	if( (pObj->GetAniKey()) > m_MaxIndex )
	{
		nIndex	=	m_MaxIndex;
		pObj->OnAnimationEnd();
	}

	if( nIndex < 0 )
	{
		nIndex	=	0;
	}


	
	DXUTTextureNode*	pTextureNode	=	m_vecTextureNode[nIndex];

	RECT	rt;
	SetRect( &rt, 0, 0, pTextureNode->dwWidth *
		_GETSINGLE( cResourceMgr )->GetScale() , pTextureNode->dwHeight );

	D3DXVECTOR3	vCenter;
	vCenter.x	=	pTextureNode->dwWidth	*	0.5f;
	vCenter.y	=	pTextureNode->dwHeight	*	0.5f;
	vCenter.z	=	0.0f;

	g_pSprite9->SetTransform( &pObj->GetWorldMatrix() );
	g_pSprite9->Begin( D3DXSPRITE_ALPHABLEND );
	g_pSprite9->Draw( pTextureNode->pTexture9, &rt, &vCenter, NULL, 
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, _GETSINGLE( cResourceMgr )->GetAlpha()) );
	g_pSprite9->End();
	
	_GETSINGLE( cResourceMgr )->SetAlpha( 1.0f );
	_GETSINGLE( cResourceMgr )->SetScale( 1.0f );

}

void	cTextureFile::AddTextureNode( DXUTTextureNode* pTextureNode )
{
	m_vecTextureNode.push_back( pTextureNode );
	++m_MaxIndex;
}

DXUTTextureNode*	cTextureFile::GetTextureNode( float fAniKey )
{
	int	nIndex	=	fAniKey * 10.0f;
	if( nIndex > m_MaxIndex )
	{
		nIndex	=	m_MaxIndex;
	}

	if( nIndex < 0 )
	{
		nIndex	=	0;
	}
	return m_vecTextureNode[nIndex];
}

