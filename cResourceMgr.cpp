#include "DXUT.h"
#include "cResourceMgr.h"
#include "cTextureFile.h"
#include "cAseFile.h"
#include "cAseLoader.h"
#include "cToonShader.h"
#include "cImageFile.h"
#include "cAlphaShader.h"
#include "cTexBuf.h"

cResourceMgr::cResourceMgr(void)
	:m_fRed( 0.0f )
	,m_fAlpha( 0.0f )
	,m_fScale( 1.0f )
{
	m_vecShader.resize( SI_MAX );

	std::vector<ST_PNT_VERTEX>	vecVertices;

	vecVertices.resize( 6 );

	vecVertices[1].p	=	D3DXVECTOR3( -0.0f, -0.0f, 0.0f );
	vecVertices[1].t	=	D3DXVECTOR2( 0.0f, 1.0f );
	vecVertices[0].p	=	D3DXVECTOR3( 1.0f, -0.0f, 0.0f );
	vecVertices[0].t	=	D3DXVECTOR2( 1.0f, 1.0f );
	vecVertices[2].p	=	D3DXVECTOR3( -0.0f, 1.0f, 0.0f );
	vecVertices[2].t	=	D3DXVECTOR2( 0.0f, 0.0f );

	vecVertices[4].p	=	D3DXVECTOR3( -0.0f, 1.0f, 0.0f );
	vecVertices[4].t	=	D3DXVECTOR2( 0.0f, 0.0f );
	vecVertices[3].p	=	D3DXVECTOR3( 1.0f, -0.0f, 0.0f );
	vecVertices[3].t	=	D3DXVECTOR2( 1.0f, 1.0f );
	vecVertices[5].p	=	D3DXVECTOR3( 1.0f, 1.0f, 0.0f );
	vecVertices[5].t	=	D3DXVECTOR2( 1.0f, 0.0f );

	for( int n = 0; n < 6; ++n )
	{
		vecVertices[n].n	=	D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	}
	DXUTGetD3D9Device()->CreateVertexBuffer( 6 * sizeof( ST_PNT_VERTEX ),
		0,ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pPlanVB, NULL );

	LPVOID	pVertices;
	m_pPlanVB->Lock( 0, 0, &pVertices, 0 );
	memcpy( pVertices, &vecVertices[0], sizeof( ST_PNT_VERTEX ) * 6 );
	m_pPlanVB->Unlock();



}


cResourceMgr::~cResourceMgr(void)
{

	SAFE_RELEASE( m_pPlanVB );
	for each( auto i in m_mapResource )
	{
		SAFE_DELETE( i.second );
	}

	for each( auto iter in m_vecShader )
	{
		SAFE_DELETE( iter );
	}
}


void	cResourceMgr::AddTexture( char* pKey, LPCWSTR pFileName, int nFrame )
{
	WCHAR	FileName[1024];
	CUSTOM_POINT	Index;
	cTextureFile*	pTexture	=	new	cTextureFile;

	for( int i = 0; i < nFrame; ++i )
	{
		if( i < 10 )
			swprintf_s( FileName, wcslen( pFileName ) + 1, pFileName, i );
		else if( i < 100 )
			swprintf_s( FileName, wcslen( pFileName ) + 2, pFileName, i );
		else
			swprintf_s( FileName, wcslen( pFileName ) + 3, pFileName, i );

		pTexture->AddTextureNode( g_DialogResourceManager.GetTextureNode(  g_DialogResourceManager.AddTexture( FileName ) ) );
	}

	pTexture->SetKey( pKey );
	m_mapResource.insert( std::pair<std::string, cResourceFile*>( pKey, pTexture ) );
}

void	cResourceMgr::AddAseFile( char* pKey, char* pFileName )
{

	cAseFile*	pAseFile	=	new	cAseFile;
	cAseLoader	AseLoader;
	std::string	sName( pKey );

	AseLoader.LoadAse( pFileName, pAseFile );

	D3DXVECTOR3	vMinToMax	=	AseLoader.m_vMin + AseLoader.m_vMax;

	pAseFile->m_vModelCenter	=	vMinToMax / 2.0f;
	pAseFile->m_fModelRadius	
		=	D3DXVec3Length( &( AseLoader.m_vMin -  pAseFile->m_vModelCenter ) );

	pAseFile->SetKey( pKey );

	m_mapResource.insert( std::pair<std::string, cResourceFile*>( sName, pAseFile ) );
}

void	cResourceMgr::AddEffect( char* pFileName, int nSID  )
{
	DWORD dwFlag = 0;

#if _ DEBUG
	dwFlag != D3DXSHADER_DEBUG;
#endif


	LPD3DXEFFECT	pEffect;
	LPD3DXBUFFER	pError;

	D3DXCreateEffectFromFileA( DXUTGetD3D9Device(),
		pFileName, NULL, NULL, dwFlag, NULL, &pEffect, &pError );

	if( !pEffect && pError )
	{
			int nSize = pError->GetBufferSize();
		void* ask = pError->GetBufferPointer();

		if( ask )
		{
			char* str = new char[nSize];
			sprintf( str, (const char*)ask, nSize );

			delete[] str;
		}
		return ;
	}
	
	cBaseShader*	pShader = NULL;

	switch( nSID )
	{
	case SI_TOON:
		pShader = new cToonShader;
		break;
	case SI_ALPHA:
		pShader = new cAlphaShader;
		break;
	default:
		return;
	}

	pShader->SetEffect( pEffect );

	m_vecShader[nSID] = pShader;
}

void	cResourceMgr::AddImage( char* pKey, char* pFileName,int nFrame,  bool IsBillBoard )
{
	cImageFile*	pImageFile	=	new	cImageFile();

	pImageFile->SetBillBoard( IsBillBoard );

	char szBuf[1024];

	for( int n = 0 ; n < nFrame; ++n )
	{	
		LPDIRECT3DTEXTURE9	pTexture;
		if( n < 10 )
			sprintf_s( szBuf, strlen( pFileName ) + 1, pFileName, n );
		else if( n < 100 )
			sprintf_s( szBuf, strlen( pFileName ) + 2, pFileName, n );

		D3DXCreateTextureFromFileA( DXUTGetD3D9Device()
			,szBuf ,  &pTexture );
		pImageFile->AddTexture( pTexture );
	}
	pImageFile->SetKey( pKey );
	m_mapResource.insert( std::pair<std::string, cResourceFile*> ( pKey, pImageFile ) );
}