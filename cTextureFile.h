#pragma once
#include "cResourceFile.h"
#include "value.h"

class cTextureFile :
	public cResourceFile
{
private:
	std::vector<DXUTTextureNode*>	m_vecTextureNode;
	int								m_MaxIndex;

public:
	virtual	void	Render( IObj* pObj, bool IsAni = false, cBaseShader* pShader = NULL  );	
	void		AddTextureNode( DXUTTextureNode* pTextureNode );
	DXUTTextureNode*	GetTextureNode( float fAniKey );

public:
	cTextureFile(void);
	~cTextureFile(void);
};

