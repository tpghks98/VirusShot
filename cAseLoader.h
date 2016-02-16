#pragma once

#include "value.h"

class cGeomNode;
class cAseFile;
class cAseLoader
{
private:
	char									m_szToken[1024];
	FILE*									m_fp;
	std::map<std::string, cGeomNode*>		m_mapGeomNode;
	cGeomNode*								m_pRootNode;

public:
	void	LoadAse( char* pFileName, cAseFile* pAseFile );

	void	ProcessScene( cAseFile*	pAseFile );
	void	ProcessMaterialList( std::vector<ST_MTL_TEX>&	vecMtlTex );
	void	ProcessMaterial( ST_MTL_TEX&	MtlTex	);
	void	ProcessMapDiffuse( ST_MTL_TEX&	MtlTex	);
	
	void	ProcessGeomObject( std::vector<ST_MTL_TEX>&	vecMtlTex );
	void	ProcessNodeTM( cGeomNode*	pGeomNode );

	void	ProcessMesh( cGeomNode*	pGeomNode );
	void	ProcessMeshVertexList( std::vector<D3DXVECTOR3>& vecV );
	void	ProcessMeshFaceList( std::vector<D3DXVECTOR3>&	vecV, std::vector<ST_PNT_VERTEX>& vecVertices );
	void	ProcessMeshTVertList( std::vector<D3DXVECTOR2>&	vecT );
	void	ProcessMeshTFaceList( std::vector<D3DXVECTOR2>&	vecT, std::vector<ST_PNT_VERTEX>& vecVertices );
	void	ProcessMeshNormal( std::vector<ST_PNT_VERTEX>&	vecVertices );

	void	ProcessTMAnimation( cGeomNode*	pGeomNode );
	void	ProcessControlPosTrack( cGeomNode*	pGeomNode );
	void	ProcessControlRotTrack( cGeomNode*	pGeomNode );

	bool	IsEqual( char* str1, char* str2 )	{	return	strcmp( str1, str2 ) == 0;	}
	bool	IsWhiteSpace( char c )				{	return	c	<	33;					}

	char*	GetToken()
	{
		ZeroMemory( m_szToken, sizeof( m_szToken ) );

		int		nCnt	=	0;
		bool	IsQuote	=	false;
		char	c;

		while( !feof( m_fp ) )
		{
			c	=	(char)fgetc( m_fp );
			if( c == '\"' )
			{
				if( IsQuote )
				{
					break;
				}
				else
				{
					IsQuote	=	true;
					continue;
				}
			}
			if( IsWhiteSpace( c ) && !IsQuote )
			{
				if( nCnt == 0 )
					continue;
				else
					break;
			}

			m_szToken[ nCnt++ ] = c;
		}

		if( nCnt == 0 )
			return	NULL;
		return	m_szToken;
	}

	int		GetInteger()	{	return	atoi( GetToken() );	}
	float	GetFloat()		{	return	atof( GetToken() );	}

public:
	D3DXVECTOR3	m_vMin;
	D3DXVECTOR3	m_vMax;
	
public:
	cAseLoader(void);
	~cAseLoader(void);
};

