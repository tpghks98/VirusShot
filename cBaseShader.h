#pragma once

#include "value.h"
class cGeomNode;
class cBaseShader
{
protected:
	_SYNTHESIZE_INHER( LPD3DXEFFECT, m_pEffect, Effect );

public:
	virtual void	Setting( cGeomNode* pNode ) {}
	virtual void	Setting(  LPDIRECT3DTEXTURE9 pTexture, D3DXMATRIXA16* pWorld  ) {}
	
public:
	cBaseShader(void);
	virtual ~cBaseShader(void);
};

