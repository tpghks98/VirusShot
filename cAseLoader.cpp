#include "DXUT.h"
#include "cAseLoader.h"
#include "cAseFile.h"
#include "cGeomNode.h"


cAseLoader::cAseLoader(void)
	:m_pRootNode( NULL )
	,m_vMin( FLT_MAX, FLT_MAX, FLT_MAX )
	,m_vMax( FLT_MIN, FLT_MIN, FLT_MIN )
{
}


cAseLoader::~cAseLoader(void)
{
}


void	cAseLoader::LoadAse( char* pFileName, cAseFile*	pAseFile )
{
	fopen_s( &m_fp, pFileName, "r" );

	char*	szToken	=	NULL;

	while( szToken = GetToken() )
	{
		if( IsEqual( szToken, "*SCENE" ) )	{	ProcessScene( pAseFile ); }
		else if( IsEqual( szToken, "*MATERIAL_LIST" ) )	{	ProcessMaterialList( pAseFile->m_vecMtlTex );	}
		else if( IsEqual( szToken, "*GEOMOBJECT" ) )	{	ProcessGeomObject( pAseFile->m_vecMtlTex );		}
	}

	fclose( m_fp );

	m_pRootNode->CalcLocalTM( NULL );

	pAseFile->m_pRootNode	=	this->m_pRootNode;
}

void	cAseLoader::ProcessScene( cAseFile* pAseFile )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*SCENE_FIRSTFRAME" ) )
		{
			pAseFile->m_nFirstFrame	=	GetInteger();
		}
		else if( IsEqual( szToken, "*SCENE_LASTFRAME" ) )
		{
			pAseFile->m_nLastFrame	=	GetInteger();
		}
		else if( IsEqual( szToken, "*SCENE_TICKSPERFRAME" ) )
		{
			pAseFile->m_nTicksPerFrame	=	GetInteger();
		}
		else if( IsEqual( szToken, "*SCENE_FRAMESPEED" ) )
		{
			pAseFile->m_nFrameSpeed	=	GetInteger();
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessMaterialList( std::vector<ST_MTL_TEX>&	vecMtlTex )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;
	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;	
		else if( IsEqual( szToken, "*MATERIAL_COUNT" ) )
		{
			vecMtlTex.resize( GetInteger() );
		}
		else if( IsEqual( szToken, "*MATERIAL" ) )
		{
			int	nIdx	=	GetInteger();
			ProcessMaterial( vecMtlTex[ nIdx ] );
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessMaterial( ST_MTL_TEX&	MtlTex )
{
	int nLevel	=	0;
	char*	szToken	=	NULL;
	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MATERIAL_AMBIENT") )
		{
			MtlTex.Mtl.Ambient.r	=	GetFloat();
			MtlTex.Mtl.Ambient.g	=	GetFloat();
			MtlTex.Mtl.Ambient.b	=	GetFloat();
			MtlTex.Mtl.Ambient.a	=	1.0f;
		}
		else if( IsEqual( szToken, "*MATERIAL_DIFFUSE") )
		{
			MtlTex.Mtl.Diffuse.r	=	GetFloat();
			MtlTex.Mtl.Diffuse.g	=	GetFloat();
			MtlTex.Mtl.Diffuse.b	=	GetFloat();
			MtlTex.Mtl.Diffuse.a	=	1.0f;
		}
		else if( IsEqual( szToken, "*MATERIAL_SPECULAR") )
		{
			MtlTex.Mtl.Specular.r	=	GetFloat();
			MtlTex.Mtl.Specular.g	=	GetFloat();
			MtlTex.Mtl.Specular.b	=	GetFloat();
			MtlTex.Mtl.Specular.a	=	1.0f;
		}
		else if( IsEqual( szToken, "*MAP_DIFFUSE" ) )
		{
			ProcessMapDiffuse( MtlTex );
		}
	}while( nLevel > 0 );
}

void		cAseLoader::ProcessMapDiffuse( ST_MTL_TEX& MtlTex )
{
	int	nLevel		=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*BITMAP" ) ) 
		{
			char*	szFileName	=	GetToken();
			D3DXCreateTextureFromFileA( DXUTGetD3D9Device(), szFileName, &MtlTex.pTex );
		}
	}while( nLevel > 0 );
}


void		cAseLoader::ProcessGeomObject( std::vector<ST_MTL_TEX>&	vecMtlTex )
{
	int		nLevel	=	0;
	char*	szToken	=	NULL;

	std::string	szName;
	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*NODE_NAME" ) )
		{
			szName	=	GetToken();
			m_mapGeomNode[ szName ]	=	new	cGeomNode;

			if( szName.substr( 0, 3 ) == "Bip" )
			{
				m_mapGeomNode[ szName ]->m_IsRender = false;
			}
			if( m_pRootNode == NULL )
				m_pRootNode	=	m_mapGeomNode[ szName ];
		}
		else if( IsEqual( szToken, "*NODE_PARENT" ) )
		{
			char*	szParentName	=	GetToken();
			m_mapGeomNode[ szParentName ]->AddChild( m_mapGeomNode[ szName ] );
		}
		else if( IsEqual( szToken, "*NODE_TM" ) )
		{
			ProcessNodeTM( m_mapGeomNode[ szName ] );
		}
		else if( IsEqual( szToken, "*MESH" ) )
		{
			ProcessMesh( m_mapGeomNode[ szName ] );
		}
		else if( IsEqual( szToken, "*MATERIAL_REF" ) )
		{
			m_mapGeomNode[ szName ]->m_pTexMtl	=	&vecMtlTex[ GetInteger() ];
		}
		else if( IsEqual( szToken, "*TM_ANIMATION" ) )
		{
			ProcessTMAnimation( m_mapGeomNode[ szName ] );
		}
	}while( nLevel > 0 );
}

void		cAseLoader::ProcessNodeTM( cGeomNode* pGeomNode )
{
	int		nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*TM_ROW0" ) )
		{
			pGeomNode->m_matWorldTM._11	=	GetFloat();
			pGeomNode->m_matWorldTM._13	=	GetFloat();
			pGeomNode->m_matWorldTM._12	=	GetFloat();
			pGeomNode->m_matWorldTM._14	=	0.0f;
		}
		else if( IsEqual( szToken, "*TM_ROW1" ) )
		{
			pGeomNode->m_matWorldTM._31	=	GetFloat();
			pGeomNode->m_matWorldTM._33	=	GetFloat();
			pGeomNode->m_matWorldTM._32	=	GetFloat();
			pGeomNode->m_matWorldTM._34	=	0.0f;
		}
		else if( IsEqual( szToken, "*TM_ROW2" ) )
		{
			pGeomNode->m_matWorldTM._21	=	GetFloat();
			pGeomNode->m_matWorldTM._23	=	GetFloat();
			pGeomNode->m_matWorldTM._22	=	GetFloat();
			pGeomNode->m_matWorldTM._24	=	0.0f;
		}
		else if( IsEqual( szToken, "*TM_ROW3" ) )
		{
			pGeomNode->m_matWorldTM._41	=	GetFloat();
			pGeomNode->m_matWorldTM._43	=	GetFloat();
			pGeomNode->m_matWorldTM._42	=	GetFloat();
			pGeomNode->m_matWorldTM._44	=	1.0f;
		}
	}while( nLevel > 0 );
}


void		cAseLoader::ProcessMesh( cGeomNode* pGeomNode )
{
	std::vector<ST_PNT_VERTEX>	vecVertices;

	std::vector<D3DXVECTOR2>	vecT;
	std::vector<D3DXVECTOR3>	vecV;

	int nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MESH_NUMVERTEX" ) )
		{
			vecV.resize( GetInteger() );
		}
		else if( IsEqual( szToken, "*MESH_NUMFACES" ) )
		{
			vecVertices.resize( GetInteger() * 3 );
		}
		else if( IsEqual( szToken, "*MESH_VERTEX_LIST" ))
		{
			ProcessMeshVertexList( vecV );
		}
		else if( IsEqual( szToken, "*MESH_FACE_LIST" ) )
		{
			ProcessMeshFaceList( vecV, vecVertices );
		}
		else if( IsEqual( szToken, "*MESH_NUMTVERTEX" ) )
		{
			vecT.resize( GetInteger() );
		}
		else if( IsEqual( szToken, "*MESH_TVERTLIST" ) )
		{
			ProcessMeshTVertList( vecT );
		}
		else if( IsEqual( szToken, "*MESH_TFACELIST" ) )
		{
			ProcessMeshTFaceList( vecT, vecVertices );
		}
		else if( IsEqual( szToken, "*MESH_NORMALS" ) )
		{
			ProcessMeshNormal( vecVertices );
		}

	}while( nLevel > 0 );

	D3DXVECTOR3	vMin,	vMax;

	D3DXComputeBoundingBox( &vecVertices[0].p, vecVertices.size(), sizeof( ST_PNT_VERTEX )
		, &vMin, &vMax );
	vMin *= 0.6f;
	vMax *= 0.6f;

	D3DXVec3Minimize( &m_vMin, &vMin, &m_vMin );
	D3DXVec3Maximize( &m_vMax, &vMax, &m_vMax );


	D3DXMATRIXA16	matInvWorld;
	D3DXMatrixInverse( &matInvWorld, 0, &pGeomNode->m_matWorldTM );

	for( auto i = 0;i < vecVertices.size(); ++i )
	{
		D3DXVec3TransformCoord( &vecVertices[i].p, &vecVertices[i].p, &matInvWorld );
	}

	DXUTGetD3D9Device()->CreateVertexBuffer( sizeof( ST_PNT_VERTEX ) * vecVertices.size(), 0, ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &pGeomNode->m_pVB, NULL );

	LPVOID	pVertices;
	pGeomNode->m_pVB->Lock( 0, 0, &pVertices, 0 );

	memcpy( pVertices, &vecVertices[0], sizeof( ST_PNT_VERTEX ) * vecVertices.size()  );

	pGeomNode->m_pVB->Unlock();

	pGeomNode->m_nNumTri	=	vecVertices.size() / 3;

}

void	cAseLoader::ProcessMeshVertexList( std::vector<D3DXVECTOR3>& vecV )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MESH_VERTEX" ) )
		{
			int	nIdx	=	GetInteger();
			vecV[ nIdx ].x	=	GetFloat();
			vecV[ nIdx ].z	=	GetFloat();
			vecV[ nIdx ].y	=	GetFloat();
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessMeshFaceList( std::vector<D3DXVECTOR3>&	vecV, std::vector<ST_PNT_VERTEX>&	vecVertices )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MESH_FACE" ) )
		{
			int	nFaceIdx	=	GetInteger();
			GetToken();
			vecVertices[ nFaceIdx * 3 + 0 ].p	=	vecV[ GetInteger() ];
			GetToken();
			vecVertices[ nFaceIdx * 3 + 2 ].p	=	vecV[ GetInteger() ];
			GetToken();
			vecVertices[ nFaceIdx * 3 + 1 ].p	=	vecV[ GetInteger() ];
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessMeshTVertList( std::vector<D3DXVECTOR2>& vecT )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MESH_TVERT" ) )
		{
			int	nIdx	=	GetInteger();
			vecT[ nIdx ].x	=	GetFloat();
			vecT[ nIdx ].y	=	1.0f - GetFloat();
		}
	}while( nLevel > 0 );
}


void	cAseLoader::ProcessMeshTFaceList( std::vector<D3DXVECTOR2>&	vecT, std::vector<ST_PNT_VERTEX>&	vecVertices )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MESH_TFACE" ) )
		{
			int	nFaceIdx	=	GetInteger();
			vecVertices[ nFaceIdx * 3 + 0 ].t	=	vecT[ GetInteger() ];
			vecVertices[ nFaceIdx * 3 + 2 ].t	=	vecT[ GetInteger() ];
			vecVertices[ nFaceIdx * 3 + 1 ].t	=	vecT[ GetInteger() ];
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessMeshNormal( std::vector<ST_PNT_VERTEX>&	vecVertices )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	int	nFaceIdx	=	0;
	int	nCnt		=	0;
	int	nIdx[3]		=	{	0	,	2	,	1	};

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*MESH_VERTEXNORMAL" ) )
		{
			GetInteger();
			D3DXVECTOR3	n;
			n.x	=	GetFloat();
			n.z	=	GetFloat();
			n.y	=	GetFloat();

			vecVertices[ 3 * nFaceIdx + nIdx[ nCnt++ ] ].n	=	n;
		}
		else if( IsEqual( szToken, "*MESH_FACENORMAL" ) )
		{
			nFaceIdx	=	GetInteger();
			nCnt		=	0;
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessTMAnimation( cGeomNode*	pGeomNode )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*CONTROL_POS_TRACK" ) )
		{
			ProcessControlPosTrack( pGeomNode );
		}
		else if( IsEqual( szToken, "*CONTROL_ROT_TRACK" ) )
		{
			ProcessControlRotTrack( pGeomNode );
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessControlPosTrack( cGeomNode* pGeomNode )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*CONTROL_POS_SAMPLE" ) )
		{
			ST_POS_TRACK	pt;
			pt.nKey	=	GetInteger();
			pt.v.x	=	GetFloat();
			pt.v.z	=	GetFloat();
			pt.v.y	=	GetFloat();

			pGeomNode->m_vecPosTrack.push_back( pt );
		}
	}while( nLevel > 0 );
}

void	cAseLoader::ProcessControlRotTrack( cGeomNode* pGeomNode )
{
	int	nLevel	=	0;
	char*	szToken	=	NULL;

	do{
		szToken	=	GetToken();
		if( IsEqual( szToken, "{" ) ) ++nLevel;
		else if( IsEqual( szToken, "}" ) ) --nLevel;
		else if( IsEqual( szToken, "*CONTROL_ROT_SAMPLE" ) )
		{
			ST_ROT_TRACK	rt;
			rt.nKey	=	GetInteger();
			rt.q.x	=	GetFloat();
			rt.q.z	=	GetFloat();
			rt.q.y	=	GetFloat();
			rt.q.w	=	GetFloat();

			rt.q.x	=	sin( rt.q.w / 2.0f )	*	rt.q.x;
			rt.q.y	=	sin( rt.q.w / 2.0f )	*	rt.q.y;
			rt.q.z	=	sin( rt.q.w / 2.0f )	*	rt.q.z;
			rt.q.w	=	cos( rt.q.w / 2.0f );
			
			if( !pGeomNode->m_vecRotTrack.empty() )
			{
				rt.q	=	pGeomNode->m_vecRotTrack.back().q * rt.q ;
			}
			pGeomNode->m_vecRotTrack.push_back( rt );
		}
	}while( nLevel > 0 );
}