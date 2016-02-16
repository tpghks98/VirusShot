#pragma once
#include "cResourceFile.h"
#include "value.h"

class cGeomNode;
class cAseFile
	:public	cResourceFile
{
public:
	int				m_nFirstFrame;
	int				m_nLastFrame;
	int				m_nTicksPerFrame;
	int				m_nFrameSpeed;

	cGeomNode*		m_pRootNode;

	std::vector<ST_MTL_TEX>	m_vecMtlTex;
	
	D3DXVECTOR3		m_vModelCenter;
	float			m_fModelRadius;

public:
	virtual	void	Render( IObj* pObj, bool IsAni = false, cBaseShader* pShader = NULL );	

public:
	cAseFile(void);
	~cAseFile(void);
};

