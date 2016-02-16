#include "DXUT.h"
#include "cAseFile.h"
#include "cGeomNode.h"
#include "cBaseShader.h"
#include "IObj.h"

cAseFile::cAseFile(void)
{
}


cAseFile::~cAseFile(void)
{
	for each( auto MtlTex in m_vecMtlTex )
	{
		SAFE_RELEASE( MtlTex.pTex );
	}
	SAFE_DELETE( m_pRootNode );
}


void	cAseFile::Render( IObj* pObj,bool IsAni , cBaseShader* pShader  )
{
	float f  = pObj->GetAniKey();
	if(  IsAni )
	{

		f	+=	m_nFrameSpeed * 0.005f * m_nTicksPerFrame  * _GETSINGLE( cSystemMgr )->GetDeltaTime() ;
		pObj->SetAniKey( f );
	}
		if( f< m_nFirstFrame  )
		{
			f	=	m_nFirstFrame;
			pObj->SetAniKey( f );
		}
		else if( f > m_nLastFrame )
		{
			f = m_nLastFrame;
			pObj->OnAnimationEnd();
		}
		DWORD	dwTime	=	f	* m_nTicksPerFrame;


		m_pRootNode->Update( dwTime, pObj->GetMatrixPointer());
		m_pRootNode->Render( pShader );
}