#pragma once

#include "value.h"

class cResourceFile;
class cBaseShader;
class cResourceMgr
{
private:

	std::map<std::string, cResourceFile*>	m_mapResource;
	std::vector<cBaseShader*>	m_vecShader;
	_SYNTHESIZE_REF_INHER( float, m_fRed, Red );
	_SYNTHESIZE_REF_INHER( float, m_fAlpha, Alpha );
	_SYNTHESIZE_REF_INHER( float, m_fScale, Scale );
	_SYNTHESIZE_INHER( LPDIRECT3DVERTEXBUFFER9, m_pPlanVB, PlanVB );;
public:
	void	AddEffect(  char* pFileName, int nSID );
	void	AddTexture( char* pKey, LPCWSTR pFileName, int nFrame = 1 ); 
	void	AddAseFile( char* pKey, char* pFileName );
	void	AddImage( char* pKey, char* pFileName, int nFrame = 1, bool IsBillBoard = false );
	
	cResourceFile*	GetResourceFile( std::string sKey )			{	return	m_mapResource.find( sKey )->second;	}
	cBaseShader*	GetShader( int nID )	{ return m_vecShader[nID]; }
	
public:
	_SINGLETON( cResourceMgr );
};

